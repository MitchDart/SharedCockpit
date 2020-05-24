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
#include "rxcpp/rx.hpp"
#include "network_state_enums.h"


/**
 * Oneliner description of class.
 *
 * Paragraph explaining how the class is used and what its purpose is in more detail.
 */
 //Class
#include "steam/steamnetworkingsockets.h"
#include <string>
#include <map>

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
  NetworkController();
  ~NetworkController();

protected:
private:
<<<<<<< HEAD
    rxcpp::subjects::subject<ConnectionState> connectionState;

=======
    HSteamNetConnection* m_hConnection;
    ISteamNetworkingSockets* m_pInterface;
    // FIXME: example properties
	std::map< HSteamNetConnection, Client_t> m_mapClients;
	HSteamListenSocket m_hListenSock;
	HSteamNetPollGroup m_hPollGroup;
    // FIXME:: needs to be evaluated
>>>>>>> 33fbf51a936e3df60102e61ba5611cbaf5cc7a23

    //This will be called by the subclass Server constructor but never called by client.. Duh
    //This will be blocking
    void initServer();

    //Connect to server at IP address
    //This will be called by the client
    //We need some mechanism for handling exceptions
    //This will be blocking
    void connectToServer(std::string address);


    void PollConnectionStateChanges() { m_pInterface->RunCallbacks(this); }

    //Set by either client or server and will be IServerCallbacks or IClientCallbacks
    virtual void setNetworkControllerCallbacks(INetworkControllerCallbacks* callbacks) = 0;

    INetworkControllerCallbacks* callback;

    void OnSteamNetConnectionStatusChanged( SteamNetConnectionStatusChangedCallback_t* pInfo) override;

    bool isServer = true;
};