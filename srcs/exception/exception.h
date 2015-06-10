#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <exception>
#include <string>

namespace flang {

class Exception : public std::exception {
 public:
  Exception(int lineno);
  ~Exception() override {}

  const char* what() const noexcept override;

  int getLineNum() { return lineno_; }
  void setLineNum(int lineno) { lineno_ = lineno;  }

 protected:
  std::string message_;
  int lineno_;
};

class Warning : public Exception {
 public:
  Warning(int lineno);
  ~Warning() override {}
};

class Error : public Exception {
 public:
  Error(int lineno);
  ~Error() override {}
};

}

#endif
