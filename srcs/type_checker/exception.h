#ifndef TYPE_CHECKER_ERROR_H
#define TYPE_CHECKER_ERROR_H

#include "location.hh"

#include "exception/exception.h"
#include "syntax_tree/syntax_tree.h"
#include "symbol_table/symbol.h"

namespace flang {

class Symbol;
class DataType;

class IncompatibleOpError : public Error {
 public:
  IncompatibleOpError(
      const std::string& op, DataType* type1,
      DataType* type2, const location& loc);
  IncompatibleOpError(
      const std::string& op, DataType* type, const location& loc);
};

class RedefineSymbolError : public Error {
 public:
  RedefineSymbolError(
      SymbolInfo* existing_symbol, SymbolInfo* redefined_symbol, int lineno);

 private:
  Symbol* existing_symbol_;
  Symbol* redefined_symbol_;
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
