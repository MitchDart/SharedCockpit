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

class Server : Peer {
public:
	/**
	* Constructor will be responsible for initializating the server and begin listenening for connections.
	**/
	Server();

	/*
	* Destroy connections and wrap up sever
	*/
	~Server();

	/*
	* Set callback delegate for connection events.
	*/
	void setServerCallbacks(IServerCallbacks* callbacks);

	/*
	* Disconnect client
	*/
	void disconnectClient();
protected:
private:
	IServerCallbacks* callbacks;
};

class IServerCallbacks : protected INetworkControllerCallbacks {
public:
	virtual void onClientConntected(std::string ipAddress) = 0;
protected:
	void onClientConnected(uint32 client) override {
		//store client as member
		//do calls to get ip address
		onClientConnected("ip address");
	};
	void onConnectedToServer() override { }
};