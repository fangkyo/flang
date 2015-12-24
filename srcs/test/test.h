#include <log4cxx/logger.h>
#include <gtest/gtest.h>

namespace flang {

#define LOG_INFO(stmt) LOG4CXX_INFO(logger_, stmt)
#define LOG_ERROR(stmt) LOG4CXX_ERROR(logger_, stmt)
#define LOG_FATAL(stmt) LOG4CXX_FATAL(logger_, stmt)
#define LOG_DEBUG(stmt) LOG4CXX_DEBUG(logger_, stmt)
#define LOG_WARN(stmt) LOG4CXX_WARN(logger_, stmt)
#define LOG_TRACE(stmt) LOG4CXX_TRACE(logger_, stmt)

class Test : public ::testing::Test {
 protected:
  static void SetUpTestCase();
  static log4cxx::LoggerPtr logger_;
};

}
