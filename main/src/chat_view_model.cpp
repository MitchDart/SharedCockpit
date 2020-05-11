#include "chat_view_model.h"

ChatViewModel::ChatViewModel(
    rxcpp::schedulers::run_loop* rlp, ChatServerInterface* chatServer):
    textInput("") 
{
  this->runLoop = rlp;
  this->chatServer = chatServer;

  auto mainThread = observe_on_run_loop(*(this->runLoop));
  auto workThread = observe_on_new_thread();

  observable<string> userInputObserver =
      observable<>::create<string>([&](subscriber<string> out) {
      });
  
  auto observer = userInputObserver.subscribe_on(workThread).observe_on(workThread).as_dynamic().publish();
  observer.subscribe_on(mainThread).subscribe(
      [=](string const& s) { 
          chatServer->sendMessage(this->getName(), s);
      });
  
  observer.connect_forever().subscribe();
}

vector<string> ChatViewModel::getMessagesFrom(string user) {
  return this->chatServer->getMessages(user);
}

int ChatViewModel::getMessageCount() { return this->messages.size(); }

string ChatViewModel::getName() { return this->userName; }


bool ChatViewModel::setName(string name) {
  this->userName = name;
  return this->chatServer->registerClient(name);
}
