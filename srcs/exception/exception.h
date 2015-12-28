#ifndef EXCEPTION_EXCEPTION_H_
#define EXCEPTION_EXCEPTION_H_

#include <cstdint>
#include <exception>
#include <string>

#include <boost/format.hpp>

#include "front_end/location.hh"

namespace flang {

/**
 * @brief Base exception class of flang compiler.
 */
class Exception {
 public:
  Exception(const location& loc);
  virtual ~Exception() {}

  const std::string& getMessage() const;
  virtual void setMessage(const std::string& message);

  enum Type {
    WARNING,
    ERROR,
    EXCEPTION,
  };
  virtual Exception::Type getType() const { return EXCEPTION; }

  const location& getLocation() const { return location_; }
  void setLocation(const location& loc) { location_ = loc; }

 protected:
  virtual const char* getName() const { return ""; }

  std::string message_;
  location location_;
};

/**
 * @brief Base warning class of flang compiler.
 */
class Warning : public Exception {
 public:
  Warning(const location& loc);
  ~Warning() override {}
  Exception::Type getType() const override {
    return Exception::WARNING;
  }
 protected:
  const char* getName() const override { return "Warning"; };
};

/**
 * @brief Base error class of flang compiler.
 */
class Error : public Exception {
 public:
  Error(const location& loc);
  ~Error() override {}
  Exception::Type getType() const override {
    return Exception::ERROR;
  }
 protected:
  const char* getName() const override { return "Error"; };
};

class FrontEndError : public Error {
 public:
  FrontEndError(const std::string& msg, const location& loc);
};

} // namespace flang

#endif

