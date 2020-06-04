#include "network_controller/network_controller.h"

#include <steam/isteamnetworkingutils.h>

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
#include <exception>

NetworkController::NetworkController() {
    //Initialize members
    this->connectionState = new rxcpp::subjects::subject<ConnectionState>();

    //Utility setup
    SteamNetworkingUtils()->SetDebugOutputFunction(k_ESteamNetworkingSocketsDebugOutputType_Msg, log);

    //Construct GNS
    SteamDatagramErrMsg errorMessage;
    if (!GameNetworkingSockets_Init(nullptr, errorMessage))
         throw std::runtime_error(("GameNetworkingSockets_Init failed.  %s", errorMessage));
}

NetworkController::~NetworkController() {
    //Close all current connections and cleanup
    GameNetworkingSockets_Kill();
    delete this->connectionState;
}

void NetworkController::log(ESteamNetworkingSocketsDebugOutputType debugOutputType, const char* message) {
    //TODO: Show logs in a window with the logtype.
    std::cout << message << std::endl;
}

void NetworkController::initServer() {
    //Retrieve correct pointer from GNS
    steamNetworkingSockets = SteamNetworkingSockets();

    SteamNetworkingIPAddr serverLocalAddr;
    serverLocalAddr.Clear();
    serverLocalAddr.m_port = PORT;
    steamListenSocket = steamNetworkingSockets->CreateListenSocketIP(serverLocalAddr, 0, nullptr);
    if (steamListenSocket == k_HSteamListenSocket_Invalid) {
        throw std::runtime_error("Unable to listen on port 27027");
    }
}

void NetworkController::connectToServer(std::string address) {}

void NetworkController::setNetworkControllerCallbacks(INetworkControllerCallbacks* callbacks) {
    this->callback = callbacks;
}

void NetworkController::OnSteamNetConnectionStatusChanged(SteamNetConnectionStatusChangedCallback_t* pInfo) {
  if (isServer) {
    char temp[1024];

    // What's the state of the connection?
    switch (pInfo->m_info.m_eState) {
      case k_ESteamNetworkingConnectionState_None:
        // NOTE: We will get callbacks here when we destroy connections.  You
        // can ignore these.
        break;

      case k_ESteamNetworkingConnectionState_ClosedByPeer:
      case k_ESteamNetworkingConnectionState_ProblemDetectedLocally: {
        // Ignore if they were not previously connected.  (If they disconnected
        // before we accepted the connection.)
        if (pInfo->m_eOldState == k_ESteamNetworkingConnectionState_Connected) {
          // Locate the client.  Note that it should have been found, because
          // this is the only codepath where we remove clients (except on
          // shutdown), and connection change callbacks are dispatched in queue
          // order.
          auto itClient = m_mapClients.find(pInfo->m_hConn);
          assert(itClient != m_mapClients.end());

          // Select appropriate log messages
          const char* pszDebugLogAction;
          if (pInfo->m_info.m_eState ==
              k_ESteamNetworkingConnectionState_ProblemDetectedLocally) {
            pszDebugLogAction = "problem detected locally";
            sprintf(temp, "Alas, %s hath fallen into shadow.  (%s)",
                    itClient->second.m_sNick.c_str(),
                    pInfo->m_info.m_szEndDebug);
          } else {
            // Note that here we could check the reason code to see if
            // it was a "usual" connection or an "unusual" one.
            pszDebugLogAction = "closed by peer";
            sprintf(temp, "%s hath departed", itClient->second.m_sNick.c_str());
          }

          // Spew something to our own log.  Note that because we put their nick
          // as the connection description, it will show up, along with their
          // transport-specific data (e.g. their IP address)
          /* todo log messages
--------------------------------------------------------------------------------------------------------------
                      Printf("Connection %s %s, reason %d: %s\n",
                              pInfo->m_info.m_szConnectionDescription,
                              pszDebugLogAction,
                              pInfo->m_info.m_eEndReason,
                              pInfo->m_info.m_szEndDebug
                      );
                      */

          m_mapClients.erase(itClient);

          // Send a message so everybody else knows what happened
          // SendStringToAllClients(temp);
        } else {
          assert(pInfo->m_eOldState ==
                 k_ESteamNetworkingConnectionState_Connecting);
        }

        // Clean up the connection.  This is important!
        // The connection is "closed" in the network sense, but
        // it has not been destroyed.  We must close it on our end, too
        // to finish up.  The reason information do not matter in this case,
        // and we cannot linger because it's already closed on the other end,
        // so we just pass 0's.
        steamNetworkingSockets->CloseConnection(pInfo->m_hConn, 0, nullptr, false);
        break;
      }

      case k_ESteamNetworkingConnectionState_Connecting: {
        // This must be a new connection
        assert(m_mapClients.find(pInfo->m_hConn) == m_mapClients.end());

        /*
        todo: log messages
        ---------
        Printf("Connection request from %s",
        pInfo->m_info.m_szConnectionDescription);

        */
        // A client is attempting to connect
        // Try to accept the connection.
        if (steamNetworkingSockets->AcceptConnection(pInfo->m_hConn) != k_EResultOK) {
          // This could fail.  If the remote host tried to connect, but then
          // disconnected, the connection may already be half closed.  Just
          // destroy whatever we have on our side.
          steamNetworkingSockets->CloseConnection(pInfo->m_hConn, 0, nullptr, false);
          /*
          todo: log messages
          ---------
                  Printf("Can't accept connection.  (It was already closed?)");
                  */
          break;
        }

        // Assign the poll group
        if (!steamNetworkingSockets->SetConnectionPollGroup(pInfo->m_hConn,
                                                  m_hPollGroup)) {
          steamNetworkingSockets->CloseConnection(pInfo->m_hConn, 0, nullptr, false);
          /*
          todo: log messages
          ---------
                  Printf("Failed to set poll group?");
                  */
          break;
        }

        // Generate a random nick.  A random temporary nick
        // is really dumb and not how you would write a real chat server.
        // You would want them to have some sort of signon message,
        // and you would keep their client in a state of limbo (connected,
        // but not logged on) until them.  I'm trying to keep this example
        // code really simple.
        char nick[64];
        sprintf(nick, "BraveWarrior%d", 10000 + (rand() % 100000));

        // Send them a welcome message
        sprintf(temp,
                "Welcome, stranger.  Thou art known to us for now as '%s'; "
                "upon thine command '/nick' we shall know thee otherwise.",
                nick);
        /*
        todo: log messages
        ---------
        SendStringToClient(pInfo->m_hConn, temp);
        */

        // Also send them a list of everybody who is already connected
        if (m_mapClients.empty()) {
          /*
          todo: log messages
          ---------
                  SendStringToClient(pInfo->m_hConn, "Thou art utterly alone.");
                  */
        } else {
          sprintf(temp, "%d companions greet you:", (int)m_mapClients.size());
          //for (auto& c : m_mapClients) {
            /*
            todo: log messages
            ---------
                            SendStringToClient(pInfo->m_hConn,
            c.second.m_sNick.c_str());
                            */
            //continue;
          //}
        }

        // Let everybody else know who they are for now
        sprintf(temp,
                "Hark!  A stranger hath joined this merry host.  For now we "
                "shall call them '%s'",
                nick);

        /*
        todo: log messages
        ---------
        SendStringToAllClients(temp, pInfo->m_hConn);
        */

        // Add them to the client list, using std::map wacky syntax
        m_mapClients[pInfo->m_hConn];
        /*
        todo: log messages
        ---------
        SetClientNick(pInfo->m_hConn, nick);
        */
        break;
      }

      case k_ESteamNetworkingConnectionState_Connected:
        // We will get a callback immediately after accepting the connection.
        // Since we are the server, we can ignore this, it's not news to us.
        break;

        //------------------ Client
        //-----------------------------------------------

      default:
        // Silences -Wswitch
        break;
    }

  } else {
  /*
    assert(pInfo->m_hConn == m_hConnection ||
           m_hConnection == k_HSteamNetConnection_Invalid);
           */

    // What's the state of the connection?
    switch (pInfo->m_info.m_eState) {
      case k_ESteamNetworkingConnectionState_None:
        // NOTE: We will get callbacks here when we destroy connections.  You
        // can ignore these.
        break;

      case k_ESteamNetworkingConnectionState_ClosedByPeer:
      case k_ESteamNetworkingConnectionState_ProblemDetectedLocally: {
        //g_bQuit = true;

        // Print an appropriate message
        if (pInfo->m_eOldState ==
            k_ESteamNetworkingConnectionState_Connecting) {
          // Note: we could distinguish between a timeout, a rejected
          // connection, or some other transport problem.
            /* 
            todo:: log client
            ---------
          Printf(
              "We sought the remote host, yet our efforts were met with "
              "defeat.  (%s)",
              pInfo->m_info.m_szEndDebug);
              */
        } else if (pInfo->m_info.m_eState ==
                   k_ESteamNetworkingConnectionState_ProblemDetectedLocally) {
            /* 
            todo:: log client
            ---------
          Printf(
              "Alas, troubles beset us; we have lost contact with the host.  "
              "(%s)",
              pInfo->m_info.m_szEndDebug);
              */
        } else {
          // NOTE: We could check the reason code for a normal disconnection
            /* 
            todo:: log client
            ---------
          Printf("The host hath bidden us farewell.  (%s)",
                 pInfo->m_info.m_szEndDebug);
                 */
        }

        // Clean up the connection.  This is important!
        // The connection is "closed" in the network sense, but
        // it has not been destroyed.  We must close it on our end, too
        // to finish up.  The reason information do not matter in this case,
        // and we cannot linger because it's already closed on the other end,
        // so we just pass 0's.
        steamNetworkingSockets->CloseConnection(pInfo->m_hConn, 0, nullptr, false);
        //m_hConnection = k_HSteamNetConnection_Invalid;
        break;
      }

      case k_ESteamNetworkingConnectionState_Connecting:
        // We will get this callback when we start connecting.
        // We can ignore this.
        break;

      case k_ESteamNetworkingConnectionState_Connected:
            /* 
            todo:: log client
            ---------
        Printf("Connected to server OK");
        */
        break;

      default:
        // Silences -Wswitch
        break;
    }
  }
}
