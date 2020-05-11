#include "chat_server_interface.h"

bool ChatServerInterface::registerClient(string name) {
  if (this->messageQueue.count(name) > 0) {
    (this->messageQueue[name]).push_back("Someone tried to be you");
    return false;
  } else {
    (this->messageQueue[name])
        .push_back("Welcome " + name + " this is pretty cool");
    for (std::map<string, vector<string>>::iterator iter = messageQueue.begin();
         iter != messageQueue.end(); ++iter) {
      if (name != iter->first) {
        this->messageQueue[name].push_back(iter->first + " is also in this chat");
        iter->second.push_back("A wild " + name + " just arrived");
      }
    }
    return true;
  }
}

vector<string> ChatServerInterface::getMessages(string name) {
  if (this->messageQueue.count(name) < 0) {
    return vector<string>();
  } else {
    return this->messageQueue[name];
  }
}

bool ChatServerInterface::sendMessage(string to, string message) {
  if (this->messageQueue.count(to) < 0) {
    return false;
  } else {
    for (std::map<string, vector<string>>::iterator iter = messageQueue.begin();
         iter != messageQueue.end(); ++iter) {
      if (to != iter->first) {
        iter->second.push_back(to + " --> " + message);
      } else {
        iter->second.push_back("<-- Sent.");
      }
    }

    return true;
  }
}

ChatServerInterface::ChatServerInterface(rxcpp::schedulers::run_loop* rlp) {
  this->runLoop = rlp;

  /*
  auto mainThread = observe_on_run_loop(*(this->runLoop));
  auto workThread = observe_on_new_thread();

  auto o1 = observable<>::interval(seconds(2));
  auto o2 = observable<>::interval(seconds(3));

  auto values = o1.map([](int i) { return char('A' + i); })
                    .combine_latest(o2)
                    .subscribe_on(workThread);

  values.take(10)
      .observe_on(workThread)
      .subscribe(
          [=](tuple<char, int> v) { 
              (this->valOfChar) = get<0>(v); 
              (this->value) = get<1>(v); 
          },
          []() { cout << endl << "Completed" << endl; });
  */
}


