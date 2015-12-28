#include <string>

#include "base/check.h"
#include "exception/exception.h"

namespace flang {

Exception::Exception(const location& loc) :
    location_(loc) {
  CHECK(location_.begin.filename);
}

const std::string& Exception::getMessage() const {
  return message_;
}

void Exception::setMessage(const std::string& message) {
  boost::format fmt("%1%(%2%:%3%:%4%): %5%");
  message_ = boost::str(
      fmt % getName() % *(location_.begin.filename) %
      location_.begin.line % location_.begin.column % message);
}

Warning::Warning(const location& loc) :
    Exception(loc) {
}

Error::Error(const location& loc) :
    Exception(loc) {
}

FrontEndError::FrontEndError(const std::string& msg, const location& loc) :
    Error(loc) {
  setMessage(msg);
}

}  // namespace flang
