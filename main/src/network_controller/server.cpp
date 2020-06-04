
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
 * this program is distributed in the hope that it will be useful,
 * but without any warranty; without even the implied warranty of
 * merchantability or fitness for a particular purpose. see the
 * gnu general public license for more details.
 */

#include "network_controller/server.h"
#include <memory>

Server::Server(Environment* environment) : NetworkController() {
    // A call was made to this-> environment but the environment was not set
    this->environment = environment;

	this->serverWindow = std::make_unique<ServerWindow>(ServerWindow());
    // set observer -- for some reason imgui calls the destructor right after creation
    this->serverWindow->setNetworkStateObserver(this->connectionState->get_observable());

    // post initial value
    this->connectionState->get_subscriber().on_next(ConnectionState::NOT_CONNECTED);

    // set server click listeners
    this->serverWindow->setOnStartClick([]() {
        std::cout << "Starting the server" << std::endl;
    });

    // hand over window to be drawn
    std::cout << "Handing over server window" << std::endl;
    this->environment->createWindow(this->serverWindow.get());
}

void Server::disconnectClient() {}

void Server::setServerCallbacks(std::shared_ptr<IServerCallbacks> callbacks) {
    this->setNetworkControllerCallbacks(callbacks.get());
}


void Server::sendMessage(void* message) {
    
}

void* Server::retrieveMessage() {
    return 0;
}

Server::~Server() {
    // because of smart pointers the server window will be destroyed when the Server scope is destroyed
    // delete this->serverWindow;
    std::cout << "Killing server" << std::endl;
}
