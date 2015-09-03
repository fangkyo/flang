#ifndef TYPE_CHECKER_ERROR_H
#define TYPE_CHECKER_ERROR_H

#include "exception/exception.h"
#include "syntax_tree/syntax_tree.h"
#include "symbol_table/symbol_info.h"

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
      const DataType& type1, const DataType& type2, int lineno);
};

class DataTypeNotPrintableError : public Error {
 public:
  DataTypeNotPrintableError(const DataType& data_type, int lineno);
};

class NotAssignableError : public Error {
 public:
  NotAssignableError(const ExpNode& left, const ExpNode& right, int lineno);
};

class IncorrectTypeError : public Error {
 public:
  IncorrectTypeError(
      const DataType& correct, const DataType& incorrect, int lineno);
};

class BreakError : public Error {
 public:
  BreakError(const BreakNode& node);
};

}  // namespace flang

#endif
