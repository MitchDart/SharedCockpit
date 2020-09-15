
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
  ChatViewModel(std::string name, EventBus<CHAT_EVENT> *chatEventBus);
  ~ChatViewModel();
  ChatWindow* chatWindow;

 private:
  ChatClient* chatClient;
  Consumer<CHAT_EVENT> chatConsumer;

  std::function<void(CHAT_EVENT)> handleChat;

};