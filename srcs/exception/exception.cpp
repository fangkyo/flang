#include "exception/exception.h"

namespace flang {

Exception::Exception(int lineno) : lineno_(lineno) {
}

const char* Exception::what() const noexcept {
  return message_.c_str();
}

Warning::Warning(int lineno) : Exception(lineno) {
}

Error::Error(int lineno) : Exception(lineno) {
}

}  // namespace flang
