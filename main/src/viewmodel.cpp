#include "viewmodel.h"

ViewModel::ViewModel(rxcpp::schedulers::run_loop* rlp) {
  this->runLoop = rlp;
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
}

int ViewModel::ViewModel::getValue() { return value; }
char ViewModel::ViewModel::getChar() { return valOfChar; }
