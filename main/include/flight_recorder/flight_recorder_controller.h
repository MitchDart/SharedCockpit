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

#include "environment.h"
#include "flight_recorder/flight_recorder_window.h"
#include <vector>
#include <string>
#include "dataref.h"

/**
 * Flight recorder responsibile for recording and replaying flight recordings
 *
 * Uses environment to record specific DataRefs into a csv file for later replaying.
 * When enabled, it creates a recorder window where the user is able to specify datarefs
 * and begin recording. 
 */
class FlightRecorderController {
    private:
        rxcpp::composite_subscription recordingSubscription;
        bool isRecording = false;
        std::ofstream* csvFile;

        Environment* environment;
        FlightRecorderWindow* window;
        std::vector<DataRef*> dataRefs;

        void startRecording();
        void stopRecording();
        void clearDataRefs();
        void addDataRefToRecord(std::string ref);
    protected:
    public:
        FlightRecorderController(Environment* environment);
        ~FlightRecorderController();
        void enableFlightRecorderWindow();
        void disableFlightRecorderWindow();
};