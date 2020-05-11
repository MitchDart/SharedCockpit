#include "rx.hpp"
#include <map>

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


class ChatServerInterface {
 public:
  ChatServerInterface(schedulers::run_loop* rlp);

  bool registerClient(string name);
  bool sendMessage(string to, string message);
  vector<string> getMessages(string name);

 private:
  schedulers::run_loop* runLoop;
  std::map<string, vector<string>> messageQueue;
};