#include <string>

#include "exception/exception.h"

namespace flang {

Exception::Exception(const std::string& filename, uint32_t lineno) :
    filename_(filename), lineno_(lineno) {
}

// static
boost::format Exception::format_("%s(%s:%u): %s");

const std::string& Exception::getMessage() const {
  return message_;
}

void Exception::setMessage(const std::string& message) {
  message_ = boost::str(format_ % getName() % filename_ % lineno_ % message);
}

Warning::Warning(const std::string& filename, uint32_t lineno) :
    Exception(filename, lineno) {
}

Error::Error(const std::string& filename, uint32_t lineno) :
    Exception(filename, lineno) {
}

}  // namespace flang
