
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

Server::Server(Environment* environment) : NetworkController() {
    this->serverWindow = new ServerWindow(this->connectionState->get_observable());
    this->environment->createWindow(this->serverWindow);
}

void Server::disconnectClient() {}

void Server::setServerCallbacks(IServerCallbacks* callbacks) {
    this->setNetworkControllerCallbacks(callbacks);
}


void Server::sendMessage(void* message) {
    
}

void* Server::retrieveMessage() {
    return 0;
}

Server::~Server() {
    delete this->serverWindow;
}
