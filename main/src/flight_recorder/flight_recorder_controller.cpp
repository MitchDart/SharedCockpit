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

#pragma once

#include "flight_recorder/flight_recorder_controller.h"
#include <fstream>
#include "rx.hpp"
#include "utils.h"
#include <iostream>
#include <functional>


FlightRecorderController::FlightRecorderController(Environment* environment) {
	this->environment = environment;
	this->window = new FlightRecorderWindow(&this->dataRefs);
}

void FlightRecorderController::enableFlightRecorderWindow() {
	
	//Setup recording window to show recording
	this->environment->createWindow(this->window);

	this->window->setOnAddRefListener([&](std::string ref) {
		this->addDataRefToRecord(ref);
	});

	this->window->setOnClearListener([&]() {
		this->clearDataRefs();
	});

	std::ofstream* csvFile = new std::ofstream();
	csvFile->open("recording.csv");

	//Create a dataref1
	const auto dataRef1 = new DataRef("data_ref_1", DATA_REF_FLOAT);
	//environment->subscribeToDataRef(dataRef1);

	//Create a dataref2
	const auto dataRef2 = new DataRef("data_ref_2", DATA_REF_FLOAT);
	//environment->subscribeToDataRef(dataRef2);

	std::vector<rxcpp::observable<DataRefValue>> sources{
		dataRef1->toObservable(),
		dataRef2->toObservable()
	};

	*csvFile << dataRef1->getRef() << "," << dataRef2->getRef() << std::endl;

	auto workThread = rxcpp::observe_on_new_thread();

	Utils::zip_v(sources)
		.observe_on(workThread)
		.subscribe([csvFile](std::shared_ptr<std::vector<DataRefValue>> value) {
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
			}, [csvFile]() {
				(*csvFile).close();
				delete csvFile;
			});
}

void FlightRecorderController::disableFlightRecorderWindow() {

}

void FlightRecorderController::addDataRefToRecord(std::string ref) {
	auto dataRef = this->environment->buildDataRef(ref);
	dataRefs.push_back(dataRef);
}

void FlightRecorderController::clearDataRefs() {
	for (auto dataRef : this->dataRefs) {
		delete dataRef;
	}
	this->dataRefs.clear();
}

FlightRecorderController::~FlightRecorderController() {
	this->clearDataRefs();
}