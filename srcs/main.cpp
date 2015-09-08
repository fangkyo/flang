#include <iostream>
#include <fstream>
#include <string>

#include <log4cxx/basicconfigurator.h>
#include <log4cxx/consoleappender.h>
#include <log4cxx/logger.h>
#include <log4cxx/patternlayout.h>
#include <log4cxx/propertyconfigurator.h>
#include <tclap/CmdLine.h>

#include "flang_parser.h"
#include "flang_scanner.h"
#include "syntax_tree/syntax_tree.h"

int main(int argc, char* argv[]){
  TCLAP::CmdLine cmd("Flang compiler.", ' ', "1.0");
  TCLAP::ValueArg<std::string> file_arg(
      "f","src_file","Source file.",true,"","string");
  TCLAP::ValueArg<std::string> log_config_arg(
      "l", "log_config", "Log4cxx configuration file.",
      false, "log4cxx.properties", "string");
  cmd.add(file_arg);
  cmd.add(log_config_arg);
  cmd.parse(argc, argv);
  std::string filename = file_arg.getValue();

  // Configure log4cxx
  if (log_config_arg.isSet()) {
    log4cxx::PropertyConfigurator::configure(log_config_arg.getValue());
  } else {
    log4cxx::PatternLayoutPtr layout(
        new log4cxx::PatternLayout("%d{HH:mm:ss} %-5p [%l] %m%n"));
    log4cxx::ConsoleAppenderPtr appender(new log4cxx::ConsoleAppender(layout));
    log4cxx::BasicConfigurator::configure(appender);
  }

  log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("flang"));
  LOG4CXX_INFO(logger, "start to parse program and build abstract syntax tree");
/*   flang::SyntaxTree syntax_tree; */
  // std::ifstream file_stream(filename);
  // flang::FlangScanner scanner(&file_stream);
  // flang::FlangParser parser(scanner, &syntax_tree, &filename);
  // try {
    // parser.parse();
  // } catch (flang::Exception* e) {
    // LOG4CXX_ERROR(logger, e->getMessage());
  /* } */

  // LOG4CXX_INFO(logger, "abstract syntax tree built completed");
  // LOG4CXX_INFO(logger, "start to do type check");
  // LOG4CXX_INFO(logger, "type check completed");
  return EXIT_SUCCESS;
}
