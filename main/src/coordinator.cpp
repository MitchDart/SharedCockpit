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

//Include windows here so they dont bother other includes.
#include "first_window.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>
#include "dataref.h"
#include "network_controller/server.h"

Coordinator::Coordinator(Environment* environment) {
    this->environment = environment;
}

void Coordinator::onStart() {
    //Create first window
    const auto firstWindow = new FirstWindow("My first window", 200,200, 200,200);
    this->environment->createWindow(firstWindow);

    this->flightRecorderController = new FlightRecorderController(this->environment);
    this->flightRecorderController->enableFlightRecorderWindow();

    Server* server = new Server(this->environment);

    //ConnectionManager* cm = new ConnectionManager();
    //this->chatViewModel = new ChatViewModel(environment, "chat 1", cm);
    //this->chatViewModel2 = new ChatViewModel(environment, "chat 2", cm);

}

void Coordinator::onStop() {
    this->flightRecorderController->disableFlightRecorderWindow();
    delete this->flightRecorderController;
}