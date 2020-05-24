#include "network_controller/client.h"

Client::Client(){
};

void* Client::pollMessage() { 
    /*

    FIXME-- pass the connection from the newtork manager to the actual client

    ISteamNetworkingMessage *pIncomingMsg = nullptr;
    int numMsgs = m_pInterface.ReceiveMessagesOnConnection(m_hConnection,
                                                            &pIncomingMsg, 1);
    if (numMsgs < 0) {
        // FIXME:: Error handling
    } else if (numMsgs != 0) {
      // Just echo anything we get from the server
      //const void* results = pIncomingMsg->getData();
      pIncomingMsg->Release();
        //return results;
    }
    */
    return new void*; 
}

void Client::sendMessage(void* message) {
    //if (strcmp(message.c_str(), "/quit") == 0) {
    /*
    FIXME:: Logging
    -------
      FireAndForget("Disconnecting from chat server");
    */

      // Close the connection gracefully.
      // We use linger mode to ask for any remaining reliable data
      // to be flushed out.  But remember this is an application
      // protocol on UDP.  See ShutdownSteamDatagramConnectionSockets
    /*
       m_pInterface->CloseConnection(m_hConnection, 0, "Goodbye", true);
    */
    //}

    // Anything else, just send it to the server and let them parse it
      /*
      // FIXME:: 
      --- decide if void* is the best way to send messages
      --- This is important as we need to sent an array and length so some struct with a length
      --- might not be a bad idea

    m_pInterface->SendMessageToConnection(
        m_hConnection, message.c_str(), (uint32)message.length(),
        k_nSteamNetworkingSend_Reliable, nullptr);
        */
}

Client::~Client() {}
