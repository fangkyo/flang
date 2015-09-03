#ifndef EXCEPTION_EXCEPTION_H_
#define EXCEPTION_EXCEPTION_H_

#include <cstdint>
#include <exception>
#include <string>

#include <boost/format.hpp>

namespace flang {

/**
 * @brief Base exception class of flang compiler.
 */
class Exception {
 public:
  Exception(const std::string& filename, uint32_t lineno);
  virtual ~Exception() {}

  const std::string& getMessage() const;
  virtual void setMessage(const std::string& message);

  uint32_t getLineno() { return lineno_; }
  void setLineno(uint32_t lineno) { lineno_ = lineno;  }
  enum Type {
    WARNING,
    ERROR
  };
  virtual Exception::Type getType() const = 0;

 protected:
  virtual const char* getName() const = 0;

 private:
  static boost::format format_;
  std::string message_;
  const std::string& filename_;
  uint32_t lineno_;
};

/**
 * @brief Base warning class of flang compiler.
 */
class Warning : public Exception {
 public:
  Warning(const std::string& filename, uint32_t lineno);
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
  Error(const std::string& filename, uint32_t lineno);
  ~Error() override {}
  Exception::Type getType() const override {
    return Exception::ERROR;
  }
 protected:
  const char* getName() const override { return "Error"; };
};

}

#endif

