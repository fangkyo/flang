#include <string>

#include "exception/exception.h"

namespace flang {

Exception::Exception(const location& loc) :
    location_(loc) {
}

// static
boost::format Exception::format_("%s(%s:%u:%u): %s");

const std::string& Exception::getMessage() const {
  return message_;
}

void Exception::setMessage(const std::string& message) {
  message_ = boost::str(
      format_ % getName() % location_.begin.filename->c_str() %
      location_.begin.line % location_.begin.column % message);
}

Warning::Warning(const location& loc) :
    Exception(loc) {
}

Error::Error(const location& loc) :
    Exception(loc) {
}

}  // namespace flang
