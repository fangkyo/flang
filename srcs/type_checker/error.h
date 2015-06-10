#ifndef ERROR_H
#define ERROR_H

#include "exception/exception.h"
#include "syntax_tree/exp_node.h"

namespace flang {

class SymbolInfo;
class DataType;

class RedefineSymbolError : public Error {
 public:
  RedefineSymbolError(
      SymbolInfo* existing_symbol, SymbolInfo* redefined_symbol, int lineno);

 private:
  SymbolInfo* existing_symbol_;
  SymbolInfo* redefined_symbol_;
};

class DataTypeNotEqualError : public Error {
 public:
  DataTypeNotEqualError(
      const std::string& type1, const std::string& type2, int lineno);
};

class DataTypeNotPrintableError : public Error {
 public:
  DataTypeNotPrintableError(const DataType& data_type, int lineno);
};

class NotAssignableError : public Error {
 public:
  NotAssignableError(const ExpNode& left, const ExpNode& right, int lineno);
};

}  // namespace flang

#endif
