#include <iostream>
#include <fstream>
#include <string>
#include <tclap/CmdLine.h>
#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>

#include "flang_parser.h"
#include "flang_scanner.h"
#include "syntax_tree/syntax_tree.h"

int main(int argc, char* argv[]){
  TCLAP::CmdLine cmd("Command description message", ' ', "0.9");
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
  log4cxx::PropertyConfigurator::configure(log_config_arg.getValue());

  log4cxx::LoggerPtr logger = log4cxx::Logger::getLogger("flang");
  LOG4CXX_INFO(logger, "start to parse program and build abstract syntax tree");
  flang::SyntaxTree syntax_tree;
  std::ifstream file_stream(filename);
  flang::FlangScanner scanner(&file_stream);
  flang::FlangParser parser(scanner, &syntax_tree);
  parser.parse();

  LOG4CXX_INFO(logger, "abstract syntax tree built completed");
  LOG4CXX_INFO(logger, "start to do type check");

  // TypeCheckVisitor typeCsfheckVisitor;
  // program->accept(typeCheckVisitor);
  // typeCheckVisitor.printError();

  LOG4CXX_INFO(logger, "type check completed");
  return EXIT_SUCCESS;
}
