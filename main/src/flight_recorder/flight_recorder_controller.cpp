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
#include <chrono>


FlightRecorderController::FlightRecorderController(Environment* environment) {
	this->environment = environment;
	this->window = new FlightRecorderWindow(&this->dataRefs, &this->isRecording);
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

	this->window->setOnRecordListener([&]() {
		this->startRecording();
	});

	this->window->setOnStopRecordListener([&]() {
		this->stopRecording();
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

void FlightRecorderController::startRecording() {
	if (this->isRecording == true)
		return;

	//Open recording file for editing
	this->csvFile = new std::ofstream();
	csvFile->open("recording.csv");

	//Create a new thread
	auto workThread = rxcpp::observe_on_new_thread();

	//Setup time
	auto startTime = std::chrono::steady_clock::now();
	*csvFile << "delta_t";

	//Copy dataRefs to readonly while we record
	std::vector<rxcpp::observable<DataRefValue>> dataRefObservables;
	for (auto& dataRef : this->dataRefs) {
		*csvFile << ',';

		dataRefObservables.push_back(dataRef->toObservable());

		//Subscribe
		environment->subscribeToDataRef(dataRef);

		//CSV Headers
		*csvFile << dataRef->getRef();
	}

	*csvFile << std::endl;

	this->recordingSubscription = Utils::zip_v(dataRefObservables)
		.observe_on(workThread)
		.subscribe([&, startTime](std::shared_ptr<std::vector<DataRefValue>> value) {
			//print delta_t
			auto current = std::chrono::steady_clock::now();
			auto elapsed_millis = std::chrono::duration_cast<std::chrono::milliseconds>(current - startTime);
			*csvFile << elapsed_millis.count();

			for (auto& v : *value) {
				*csvFile << ',';

				switch (v.type) {
				case DataRefType::DATA_REF_FLOAT: {
					*csvFile << v.floatData;
					break;
				}
				case DataRefType::DATA_REF_DOUBLE: {
					*csvFile << v.doubleData;
					break;
				}
				}
			}
			*csvFile << std::endl;
		}, [&]() {
			stopRecording();
		});

	this->isRecording = true;
}

void FlightRecorderController::stopRecording() {
	if (this->isRecording == false)
		return;

	this->recordingSubscription.unsubscribe();

	//Unsubscribe to dataRefs
	for (auto dataRef : this->dataRefs) {
		environment->unSubscribeToDataRef(dataRef);
	}

	(*csvFile).close();
	delete csvFile;

	this->isRecording = false;
}

FlightRecorderController::~FlightRecorderController() {
	if (this->isRecording == true)
		stopRecording();

	this->clearDataRefs();
}
