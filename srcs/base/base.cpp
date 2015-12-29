#include "base/base.h"

#include "third_party/backward-cpp/backward.hpp"

namespace flang {

void initProgram() {
  static backward::SignalHandling sh;
}


}  // namespace flang
