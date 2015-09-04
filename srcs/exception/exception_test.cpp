#include <gtest/gtest.h>

#include "exception/exception.h"

namespace flang {

TEST(ExceptionTest, testMessage) {
  std::string filename = "a.cpp";
  location loc(&filename, 3, 2);
  Warning warning(loc);
  warning.setMessage("hello");
  EXPECT_EQ("Warning(a.cpp:3:2): hello", warning.getMessage());

  Error error(loc);
  error.setMessage("world");
  EXPECT_EQ("Error(a.cpp:3:2): world", error.getMessage());
}

}
