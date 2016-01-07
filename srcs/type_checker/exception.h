#ifndef TYPE_CHECKER_ERROR_H
#define TYPE_CHECKER_ERROR_H

#include "exception/exception.h"

namespace flang {

class ExpNode;
class BreakNode;
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

class RedefineSymbolError : public FrontEndError {
 public:
  RedefineSymbolError(
      Symbol* existing_symbol, Symbol* redefined_symbol, const location& loc);
};

class DataTypeNotEqualError : public FrontEndError {
 public:
  DataTypeNotEqualError(
      const DataType& type1, const DataType& type2, const location& loc);
};

class DataTypeNotPrintableError : public FrontEndError {
 public:
  DataTypeNotPrintableError(const DataType& data_type, const location& loc);
};

class NotAssignableError : public FrontEndError {
 public:
  NotAssignableError(const ExpNode& left, const ExpNode& right, const location& loc);
};

class IncorrectTypeError : public FrontEndError {
 public:
  IncorrectTypeError(
      const DataType& correct, const DataType& incorrect, const location& loc);
};

class BreakError : public FrontEndError {
 public:
  BreakError(const BreakNode& node, const location& loc);
};

}  // namespace flang

#endif
