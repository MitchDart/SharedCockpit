/*
* SharedCockpit
* See LICENSE file at the top of the source tree.
*
* This product includes software developed by the
* SharedCockpit Project (https://github.com/MitchDart/SharedCockpit/).
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*/

#include "coordinator.h"
#include "viewmodel.h"

//Include windows here so they dont bother other includes.
#include "first_window.h"
#include "recording_window.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>
#include "dataref.h"


Coordinator::Coordinator(Environment* environment) {
    this->environment = environment;
    this->viewModel = new ViewModel(environment->rlp);
}

void Coordinator::onStart() {
    //Create first window
    const auto firstWindow = new FirstWindow("My first window", 200,200, 200,200, this->viewModel);
    this->environment->createWindow(firstWindow);

	this->startRecording();
}

void Coordinator::onStop() {

}

template <typename T>
rxcpp::observable<std::shared_ptr<std::vector<T>>> zip_v(const std::vector<rxcpp::observable<T>>& observables) {
	// map the first observable to convert values to a single-element vector
	auto it = observables.cbegin();
	rxcpp::observable<std::shared_ptr<std::vector<T>>> acc = it->map([](T t) {
		return std::make_shared<std::vector<T>>(std::initializer_list<T>{ t });
		});

	// fold each observable into accumulator by zipping, and pushing back value
	while (++it != observables.cend()) {
		acc = acc.zip([](std::shared_ptr<std::vector<T>> acc, T next) {
			acc->push_back(next);
			return acc;
			}, *it);
	}
	return acc;
}

void Coordinator::startRecording() {

	//Setup recording window to show recording
	const auto recordingWindow = new RecordingWindow();
    this->environment->createWindow(recordingWindow);

	ofstream* csvFile = new ofstream();
  	csvFile->open ("recording.csv");

	//Create a dataref1
	const auto dataRef1 = new DataRef("data_ref_1",DATA_REF_FLOAT);
	environment->subscribeToDataRef(dataRef1);

	//Create a dataref2
	const auto dataRef2 = new DataRef("data_ref_2", DATA_REF_FLOAT);
	environment->subscribeToDataRef(dataRef2);

	std::vector<rxcpp::observable<DataRefValue>> sources {
		dataRef1->toObservable(),
		dataRef2->toObservable()
	};

	*csvFile << dataRef1->getRef() << "," << dataRef2->getRef() << std::endl;

	auto workThread = observe_on_new_thread();

	zip_v(sources)
		.observe_on(workThread)
		.subscribe([recordingWindow, csvFile](std::shared_ptr<std::vector<DataRefValue>> value) {
			for (int i = 0; i < (*value).size(); i++) {
				auto& v = (*value)[i];

				switch (v.type) {
				case DataRefType::DATA_REF_FLOAT: {
					*csvFile << v.floatData;
					break;
				}
				}

				if (i != (*value).size() - 1) {
					*csvFile << ',';
				}
			}
			*csvFile << std::endl;
		}, [recordingWindow, csvFile]() {
			(*csvFile).close();
			delete csvFile;
		});
}

void Coordinator::stopRecording() {

}
