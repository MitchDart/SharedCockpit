
#include "rx.hpp"
#include <map>
#include "imgui.h"
#include "chat/chat_client.hpp"
#include "chat/connection_manager.h"
#include "environment.h"

#pragma once
#include "chat/chat_window.h"
#include <functional>

using namespace std;
using namespace std::chrono;

class ChatViewModel {
 public:
  ChatViewModel(Environment* environment, std::string name,  ConnectionManager* connectionManager);
  ~ChatViewModel();

 private:
  Environment* environment;
  ChatClient* chatClient;
  ChatWindow* chatWindow;
  ConnectionManager* connectionManager;

};