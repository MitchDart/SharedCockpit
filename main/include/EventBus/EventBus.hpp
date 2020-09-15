#include <rx.hpp>
#include <memory>
#include <map>
#include <algorithm>

#pragma once

using namespace std;

// EVENT
// This is not part of the general solution
struct EVENT_INFO {
	int id;
	string description;
	EVENT_INFO() { id = -1; description = "INITIAL"; };
	EVENT_INFO(int pid, string pdescription) { id = pid; description = pdescription; };
	void Print() {
		cout << "id" << id << " : ";
		cout << "description" << description << endl;
	}
};

// one day I will use the type defined capturing tmplate definition for statically typed lambdas, one day
//   my issue is how to define the in type
template<typename ObjectType, typename ReturnType, typename ... Arguments>
struct lambda_expression {
	ObjectType _object;
	ReturnType(ObjectType::* _funuction)(Arguments...)const;

	lambda_expression(const ObjectType& object) : _object(object), _function(&decltype(_object)::operator()) {}

	ReturnType operator() (Arguments ... args) const {
		return (_object.*_fuunction)(args...);
	}
};

// This is not part of the general solution

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
	std::function<void(T value)> processClosure;
	string name;

public:
	Consumer(string pname, const std::function<void(T)> &&onEventClosure) {
		name = pname; 
		processClosure = onEventClosure;
	}

	bool Connect(EventBus<T> *eventBus) {
		if (subscription.is_subscribed()) {
			subscription.unsubscribe();
		}

		// create a new subscription
		subscription = rxcpp::composite_subscription();
		auto subscriber = rxcpp::make_subscriber<T>(
			subscription,
			processClosure,
			[]() { printf("On Completed\n"); }
		);

		eventBus->GetObservable().subscribe(subscriber);
		return true;
	}

	~Consumer() { 
		Disconnect(); 
	}

	bool Disconnect() {
		if (subscription.is_subscribed()) {
			subscription.unsubscribe();
			return true; 
		}
		return false;
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



template <class T>
class ActiveObject {
  rxcpp::subjects::subject<T> subj;

 protected:
  ActiveObject() {
    subj.get_observable().subscribe([=](T s) {
      cout << "exec: " << s << endl;
      Execute(s);
    });
  };
  virtual void Execute(T s){};

 public:
  void FireAndForget(T item) {
    cout << "fire: " << item << endl;
    subj.get_subscriber().on_next(item);
  }
  rxcpp::observable<T> GetObservable() { return subj.get_observable(); }
  virtual ~ActiveObject() {}
};
