#include "chat_view_model.h"

template <typename T>
struct IntervalRepeater {
  using CallableCopyable = T;

 private:
  weak_ptr<IntervalRepeater<CallableCopyable>> holder;
  std::thread theThread;

  IntervalRepeater(unsigned int interval, CallableCopyable callable)
      : callable(callable), interval(interval) {}

  void thread() {
    weak_ptr<IntervalRepeater<CallableCopyable>> holder = this->holder;
    theThread = std::thread([holder]() {
      // Try to strongify the pointer, to make it survive this loop iteration,
      //    and ensure that this pointer is valid, if not valid, end the loop.
      while (shared_ptr<IntervalRepeater<CallableCopyable>> ptr =
                 holder.lock()) {
        auto x =
            chrono::steady_clock::now() + chrono::milliseconds(ptr->interval);
        ptr->callable();
        this_thread::sleep_until(x);
      }
    });
  }

 public:
  const CallableCopyable callable;
  const unsigned int interval;

  static shared_ptr<IntervalRepeater<T>> createIntervalRepeater(
      unsigned int interval, CallableCopyable callable) {
    std::shared_ptr<IntervalRepeater<CallableCopyable>> ret =
        shared_ptr<IntervalRepeater<CallableCopyable>>(
            new IntervalRepeater<CallableCopyable>(interval, callable));
    ret->holder = ret;
    ret->thread();

    return ret;
  }

  ~IntervalRepeater() {
    // Detach the thread before it is released.
    theThread.detach();
  }
};

ChatViewModel::ChatViewModel(Environment* environment, std::string name,
                             ConnectionManager* connectionManager) {
  this->connectionManager = connectionManager;
  this->environment = environment;
  // The connection manager have got everything needed to make a chat client
  // todo:: make it so that I can get network events from more than ons connection... or rethink how I send messages 
  // --- the issue is that the newest observer of network state overrides the old one and the steam networking sockets
  // --- class is a static class, so its a bit of a hassle
  this->chatClient = new ChatClient(this->connectionManager);

  // --- The basic chat class is self contained, needs work on managing dropping the connection
  // --- atm a thread spawns and detatches itself in the constructor, this is the polling of the server for messages.
  // --- currently no error handeling will stop it from polling -- possible runtime errors might be a real hurdle atm

  this->chatWindow = new ChatWindow(
      name, 500, 400, 400, 100,
      // link the action of send up with the chat service
      [=](std::string message) { 
          this->chatClient->SendMessage(message); 
      });

  // handle messages from the chat server -- passing them down to the view
  // todo:: implement the active object pattern with more details at this moment its just 
  // a proxy with a passthrough and a logger
  this->chatClient->GetObservable()
      .subscribe_on(rxcpp::observe_on_run_loop(*(environment->rlp)))
      .subscribe(
          [=](string value) { 
              (chatWindow->messages).push_back(value); 
          });

  // create a window in the active
  this->environment->createWindow(this->chatWindow);
}

