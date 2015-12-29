#include <log4cxx/basicconfigurator.h>
#include <log4cxx/consoleappender.h>
#include <log4cxx/patternlayout.h>

#include "base/base.h"
#include "test/test.h"

namespace flang {

// static
log4cxx::LoggerPtr Test::logger_(log4cxx::Logger::getLogger("flang.test"));

// static
void Test::SetUpTestCase() {
  log4cxx::PatternLayoutPtr layout(
      new log4cxx::PatternLayout("%d{HH:mm:ss} %-5p [%l] %m%n"));
  log4cxx::ConsoleAppenderPtr appender(new log4cxx::ConsoleAppender(layout));
  log4cxx::BasicConfigurator::configure(appender);
  flang::initProgram();
}

}
