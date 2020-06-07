
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

Server::Server(Environment* environment) : NetworkController(environment) {
    this->serverWindow = new ServerWindow(this->connectionState->get_observable());
    this->environment->createWindow(this->serverWindow);

    //Initialize server connection state
    this->connectionState->get_subscriber().on_next(ConnectionState::NOT_CONNECTED);

    //Connect window listeners
    this->serverWindow->setOnStartClick([&]() {
        //Start the server
        this->initServer();
    });

    this->environment->createWindow(this->serverWindow);
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
    this->environment->logger->AddLog("[info] Shutting down server");
}
