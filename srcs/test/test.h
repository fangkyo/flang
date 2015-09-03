#include <log4cxx/logger.h>
#include <gtest/gtest.h>

namespace flang {

class Test : public ::testing::Test {
 protected:
  static void SetUpTestCase();
  static log4cxx::LoggerPtr logger_;
};

}
