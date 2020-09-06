#include <rx.hpp>
#include <memory>
#include <map>
#include <algorithm>

using namespace std;

// EVENT
struct EVENT_INFO {
	int id;
	string description;
	EVENT_INFO() { id = 0; description = "BASE"; };
	EVENT_INFO(int pid, string pdescription) { id = pid; description = pdescription; };
	void Print() {
		cout << "id" << id << " : ";
		cout << "description" << description << endl;
	}
};

template <class T>
void ProcessEvent(T event) { event.Print(); }

template <class T>
class EventBus;

template <class T>
class Producer {
	string name;
public:
	Producer(string pname) { name = pname; }
	bool Emmit(T event, EventBus<T>* eventBus) {
		eventBus->EmmitEvent(event);
		return false;
	}
};

template <class T>
class Consumer {
	rxcpp::composite_subscription subscription;
public:
	string name;
	Consumer(string pname) { name = pname; }
	bool Connect(EventBus<T> *eventBus) {
		if (subscription.is_subscribed()) {
			subscription.unsubscribe();
		}
		// create a new subscription

		subscription = rxcpp::composite_subscription();
		auto subscriber = rxcpp::make_subscriber<T>(
			subscription,
			[=](T value) {
				cout << "some event on consumer: " << name << endl;
				ProcessEvent<T>(value);
			},
			[]() { printf("On Completed\n"); }
		);
		eventBus->GetObservable().subscribe(subscriber);
		return true;
	}
	~Consumer() { 
		cout << "this is unacceptable" << name << endl;
		Disconnect(); 
	}
	bool Disconnect() {
		cout << this << endl;
		if (subscription.is_subscribed()) {
			subscription.unsubscribe();
			return true; 
		}
		return true;
	}
};

template <class T>
class EventBus {
private:
	string name;
	rxcpp::subjects::behavior<T>* replaySubject;
public:
	EventBus<T>() { replaySubject = new rxcpp::subjects::behavior<T>(T()); }
	~EventBus() { delete replaySubject; }

	bool AddConsumer(Consumer<T>& consumer) { 
		consumer.Connect(this); 
		return true; 
	}
	bool EmmitEvent(T& event) {
		replaySubject->get_subscriber().on_next(event);
		return true;
	}

	string get_name() { return name; }
	rxcpp::observable<T> GetObservable() { return replaySubject->get_observable(); }
};








