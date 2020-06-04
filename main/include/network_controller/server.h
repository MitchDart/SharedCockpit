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

#pragma once
#include "peer.h"
#include <string>
#include <memory>
#include "steam/steamnetworkingsockets.h"
#include "network_controller.h"
#include "server_window.h"
#include "environment.h"

class IServerCallbacks : public INetworkControllerCallbacks {
public:
	virtual void onClientConntected(std::string ipAddress) = 0;
protected:
	void onClientConnected(uint32 client) override {
		//store client as member
		//do calls to get ip address
		onClientConnected(1987312);
	};
	void onConnectedToServer() override { }
};

class Server : public NetworkController, Peer {
public:
	/**
	* Constructor will be responsible for initializating the server and begin listenening for connections.
	**/
	Server(Environment* environment);

	/*
	* Destroy connections and wrap up sever
	*/
	~Server();

	/*
	* Set callback delegate for connection events.
	*/
	void setServerCallbacks(std::shared_ptr<IServerCallbacks> callbacks);

	/*
	* Disconnect client
	*/
	void disconnectClient();

	void sendMessage(void* message) override;
	void* retrieveMessage() override;
protected:
private:
 //Pointer to server window
 std::unique_ptr<IServerCallbacks> callbacks;
 std::shared_ptr<ServerWindow> serverWindow;
 Environment* environment;
};