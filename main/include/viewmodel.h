
#include "rx.hpp"

#ifndef VIEWMODEL_H
#define VIEWMODEL_H

namespace ViewModel {
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
}  // namespace ViewModel

#endif  // !VIEWMODEL_H
