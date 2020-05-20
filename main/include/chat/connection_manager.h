#include "steam/steamnetworkingsockets.h"
#include <assert.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <algorithm>
#include <string>
#include <random>
#include <chrono>
#include <thread>
#include <mutex>
#include <queue>
#include <map>
#include <cctype>

#pragma once

class ConnectionManager {
 private:
  const uint16 DEFAULT_SERVER_PORT = 27020;

 public:
  static void InitSteamDatagramConnectionSockets() {
    SteamDatagramErrMsg errMsg;
    if (!GameNetworkingSockets_Init(nullptr, errMsg)) 
        std::cout << "FATAL INIT";
  }
  ISteamNetworkingSockets* steamSockets;
  SteamNetworkingIPAddr steamServerConnection;

  ConnectionManager() {
    // Select instance to use.  For now we'll always use the default.
    steamServerConnection.Clear();
    steamServerConnection.ParseString("127.0.0.1:27020");
    steamServerConnection.m_port = DEFAULT_SERVER_PORT;
    InitSteamDatagramConnectionSockets();
    steamSockets = SteamNetworkingSockets();
    // Start connecting
    char szAddr[SteamNetworkingIPAddr::k_cchMaxString];
    steamServerConnection.ToString(szAddr, sizeof(szAddr), true);
  };
};