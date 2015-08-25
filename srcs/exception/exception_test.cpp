#include <gtest/gtest.h>

#include "exception/exception.h"

namespace flang {

TEST(ExceptionTest, testMessage) {
  std::string filename = "a.cpp";
  Warning warning(filename, 33);
  warning.setMessage("hello");
  EXPECT_EQ("Warning(a.cpp:33): hello", warning.getMessage());

  Error error(filename, 42);
  error.setMessage("world");
  EXPECT_EQ("Error(a.cpp:42): world", error.getMessage());
}

}
