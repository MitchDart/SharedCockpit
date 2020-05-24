#include "network_controller/client.h"

Client::Client() {}

void* Client::pollMessage() { return new void*; }

void Client::sendMessage(void* message) {}

Client::~Client() {}
