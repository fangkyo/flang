#include <iostream>
#include <fstream>
#include <string>
#include <tclap/CmdLine.h>
#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>

#include "flang_parser.h"
#include "flang_scanner.h"
#include "syntax_checker.h"

int main(int argc, char* argv[]){
  TCLAP::CmdLine cmd("Command description message", ' ', "0.9");
  TCLAP::ValueArg<std::string> file_arg(
      "f","file","Source file to compile.",true,"homer","string");
  cmd.add(file_arg);
  cmd.parse(argc, argv);
  std::string filename = file_arg.getValue();

  log4cxx::PropertyConfigurator::configure("log4cxx.properties");
  log4cxx::LoggerPtr logger = log4cxx::Logger::getLogger("flang");
  LOG4CXX_INFO(logger, "start to parse program and build abstract syntax tree");
  SyntaxTree* program = NULL;
  std::ifstream file_stream(filename);
  flang::FlangScanner scanner(&file_stream);
  flang::FlangParser parser(scanner, program);
  parser.parse();

  if( NULL == program ) {
    LOG4CXX_INFO(logger, "program is null" );
    return 0;
  }

  LOG4CXX_INFO(logger, "abstract syntax tree built completed");
  LOG4CXX_INFO(logger, "start to do type check");

  // TypeCheckVisitor typeCsfheckVisitor;
  // program->accept(typeCheckVisitor);
  // typeCheckVisitor.printError();

  LOG4CXX_INFO(logger, "type check completed");
  program = NULL;

  flang::AssignNode
  return 0;
}
