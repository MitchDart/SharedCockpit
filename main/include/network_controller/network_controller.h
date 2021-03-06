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
#include "rx.hpp"
#include "network_state_enums.h"
#include "include\environment.h"


/**
 * Oneliner description of class.
 *
 * Paragraph explaining how the class is used and what its purpose is in more detail.
 */
 //Class
#include "steam/steamnetworkingsockets.h"
#include "steam/steamnetworkingtypes.h"
#include <string>
#include <map>
#include <memory>

class INetworkControllerCallbacks {
public:
protected:
    //FOR SERVERS
    virtual void onClientConnected(uint32 client) = 0;

    //FOR CLIENTS
    virtual void onConnectedToServer() = 0;
private:
};

// FIXME:: remove example code
// Only for plumbing sake for server
struct Client_t
{
	std::string m_sNick;
};

class NetworkController : private ISteamNetworkingSocketsCallbacks {

public:
    NetworkController(Environment* environment);
    ~NetworkController();

protected:
    Environment* environment;
    rxcpp::subjects::subject<ConnectionState>* connectionState;

    //Set by either client or server and will be IServerCallbacks or IClientCallbacks
    void setNetworkControllerCallbacks(INetworkControllerCallbacks* callbacks);

    //This will be called by the subclass Server constructor but never called by client.. Duh
    //This will be blocking
    void initServer();

    //Connect to server at IP address
    //This will be called by the client
    //We need some mechanism for handling exceptions
    //This will be blocking
    void connectToServer(std::string address);
private:

    ISteamNetworkingSockets* steamNetworkingSockets;
    // FIXME: example properties
	std::map< HSteamNetConnection, Client_t> m_mapClients;
	HSteamNetPollGroup m_hPollGroup;
    // FIXME:: needs to be evaluated

    void PollConnectionStateChanges() { steamNetworkingSockets->RunCallbacks(this); }

    void OnSteamNetConnectionStatusChanged( SteamNetConnectionStatusChangedCallback_t* pInfo) override;

    bool isServer = true;

    //Server stuff for now
    const uint16 PORT = 27027;
    HSteamListenSocket steamListenSocket;

    // taking ownership of our networking interface and connection
    std::unique_ptr<HSteamNetConnection> m_hConnection;

    // we are not going to take ownership of the pointer
    INetworkControllerCallbacks* callback;

    static void log(ESteamNetworkingSocketsDebugOutputType debugOutputType, const char* message);
};
