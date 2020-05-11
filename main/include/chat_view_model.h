#include "rx.hpp"
#include <map>
#include "chat_server_interface.h"
#include "imgui.h"

#pragma once

using namespace std;
using namespace std::chrono;

namespace Rx {
   using namespace rxcpp;
   using namespace rxcpp::sources;
   using namespace rxcpp::operators;
   using namespace rxcpp::util;
}  // namespace Rx

using namespace Rx;


class ChatViewModel {
 public:
  ChatViewModel(schedulers::run_loop* rlp, ChatServerInterface* chatServer);
  ~ChatViewModel();
  int getMessageCount();
  vector<string> getMessagesFrom(string user);
  bool setName(string name);
  string getName();
  char textInput[128];

 private:
  ChatServerInterface* chatServer;
  schedulers::run_loop* runLoop;
  int unreadMessages = 0;
  string userName;

  std::map<string, vector<string>> messages;
};