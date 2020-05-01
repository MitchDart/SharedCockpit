
#include "rx.hpp"

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


class ViewModel {
 public:
  ViewModel(rxcpp::schedulers::run_loop* rlp);
  ~ViewModel();
  int getValue();
  char getChar();

 private:
  rxcpp::schedulers::run_loop* runLoop;
  int value = 0;
  char valOfChar = '^';
};