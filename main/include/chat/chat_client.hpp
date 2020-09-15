#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <cctype>
#include <chrono>
#include <map>
#include <mutex>
#include <queue>
#include <random>
#include <string>
#include <thread>

#pragma once

#include "chat/connection_manager.h"
#include "steam/steamnetworkingsockets.h"
#include "EventBus/EventBus.hpp"


using namespace std;
using namespace std::chrono;

struct CHAT_EVENT {
    std::string message;
    CHAT_EVENT() {
        message = "";
    };
    CHAT_EVENT(std::string pmessage) {
        message = pmessage;
    };
};


class ChatClient : private ISteamNetworkingSocketsCallbacks {
 public:
  ChatClient(ConnectionManager *connectionManager, EventBus<CHAT_EVENT> *pchatEventBus): producerOne("Chat Client") {
    m_hConnection = connectionManager->steamSockets->ConnectByIPAddress(
        connectionManager->steamServerConnection, 0, nullptr);
    m_pInterface = connectionManager->steamSockets;
    chatEventBus = pchatEventBus;

    if (m_hConnection == k_HSteamNetConnection_Invalid) {
        producerOne.Emmit(CHAT_EVENT("Failed to create connection"), chatEventBus);
    }

    // Using a pretty nifty task of abstraction
    std::thread([&]() {
      for (;;) {
        this->Run();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
      }
    }).detach();
  }

  void Run() {
    PollIncomingMessages();
    PollConnectionStateChanges();
  }

  void SendMessage(string message) {
    if (strcmp(message.c_str(), "/quit") == 0) {
      quit = true;
      producerOne.Emmit(CHAT_EVENT("Disconnecting from chat server"), chatEventBus);

      // Close the connection gracefully.
      // We use linger mode to ask for any remaining reliable data
      // to be flushed out.  But remember this is an application
      // protocol on UDP.  See ShutdownSteamDatagramConnectionSockets
      m_pInterface->CloseConnection(m_hConnection, 0, "Goodbye", true);
    }

    // Anything else, just send it to the server and let them parse it
    m_pInterface->SendMessageToConnection(
        m_hConnection, message.c_str(), (uint32)message.length(),
        k_nSteamNetworkingSend_Reliable, nullptr);
  }

 private:
  //-- Dispatcher Object
  HSteamNetConnection m_hConnection;
  ISteamNetworkingSockets *m_pInterface;
  Producer<CHAT_EVENT> producerOne;
  EventBus<CHAT_EVENT> *chatEventBus;

  bool quit = false;

  void PollIncomingMessages() {
    ISteamNetworkingMessage *pIncomingMsg = nullptr;
    int numMsgs = m_pInterface->ReceiveMessagesOnConnection(m_hConnection,
                                                            &pIncomingMsg, 1);
    if (numMsgs < 0) {
      producerOne.Emmit(CHAT_EVENT("Error checking for messages"), this->chatEventBus);
    } else if (numMsgs != 0) {
      // Just echo anything we get from the server
      producerOne.Emmit(CHAT_EVENT(string(string((char *)(pIncomingMsg->GetData()),
                                  pIncomingMsg->GetSize())) +
                    "\n"), this->chatEventBus);
      // We don't need this anymore.
      pIncomingMsg->Release();
    }
  }

  void PollConnectionStateChanges() { m_pInterface->RunCallbacks(this); }

  virtual void OnSteamNetConnectionStatusChanged(
      SteamNetConnectionStatusChangedCallback_t *pInfo) override {
    cout << "---" << pInfo->m_hConn << "--" << m_hConnection << endl;
    if (pInfo->m_hConn != m_hConnection ||
        m_hConnection == k_HSteamNetConnection_Invalid) {
      cout << "err" << pInfo->m_hConn << "--" << m_hConnection << endl;
      return;
    }

    // What's the state of the connection?
    switch (pInfo->m_info.m_eState) {
      case k_ESteamNetworkingConnectionState_None:
        // NOTE: We will get callbacks here when we destroy connections.  You
        // can ignore these.
        break;

      case k_ESteamNetworkingConnectionState_ClosedByPeer:
      case k_ESteamNetworkingConnectionState_ProblemDetectedLocally: {
        quit = true;

        // Print an appropriate message
        if (pInfo->m_eOldState ==
            k_ESteamNetworkingConnectionState_Connecting) {
          // Note: we could distinguish between a timeout, a rejected
          // connection, or some other transport problem.
           
        producerOne.Emmit(CHAT_EVENT( "We sought the remote host, yet our efforts were met with " "defeat. " +
              *(pInfo->m_info.m_szEndDebug)), this->chatEventBus);
        } else if (pInfo->m_info.m_eState ==
                   k_ESteamNetworkingConnectionState_ProblemDetectedLocally) {
          producerOne.Emmit(CHAT_EVENT("Alas, troubles beset us; we have lost contact with the host. " +
              *(pInfo->m_info.m_szEndDebug)), this->chatEventBus);
        } else {
          // NOTE: We could check the reason code for a normal disconnection

            producerOne.Emmit(CHAT_EVENT("The host hath bidden us farewell. " +
                        *(pInfo->m_info.m_szEndDebug)), this->chatEventBus);
        }

        // Clean up the connection.  This is important!
        // The connection is "closed" in the network sense, but
        // it has not been destroyed.  We must close it on our end, too
        // to finish up.  The reason information do not matter in this case,
        // and we cannot linger because it's already closed on the other end,
        // so we just pass 0's.
        m_pInterface->CloseConnection(pInfo->m_hConn, 0, nullptr, false);
        m_hConnection = k_HSteamNetConnection_Invalid;
        break;
      }

      case k_ESteamNetworkingConnectionState_Connecting:
        // We will get this callback when we start connecting.
        // We can ignore this.
        break;

      case k_ESteamNetworkingConnectionState_Connected:
        producerOne.Emmit(CHAT_EVENT("Connected to server OK"), this->chatEventBus);
        break;

      default:
        // Silences -Wswitch
        break;
    }
  }
};
