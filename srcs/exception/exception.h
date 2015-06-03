#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <exception>
#include <string>

namespace flang {

class Exception : public std::exception {
 public:
  Exception(const std::string& msg, int lineno = INVALID_LINENO) :
    message_(msg), lineno_(lineno) {}
  Exception() {}
  ~Exception() override {}

  const char* what() const noexcept override { return message_.c_str(); }

  int getLineNum() { return lineno_; }
  void setLineNum(int lineno) { lineno_ = lineno;  }

  static const int INVALID_LINENO = -1;

 protected:
  std::string message_;
  int lineno_;
};

class Warning : public Exception {
 public:
  Warning(const std::string& msg) : Exception(msg) {}
  ~Warning() override {}
};

class Error : public Exception {
 public:
  Error() {}
  ~Error() override {}
};

}

#endif
