#ifndef TYPE_CHECKER_ERROR_H
#define TYPE_CHECKER_ERROR_H

#include "exception/exception.h"

namespace flang {

class ExpNode;
class BreakNode;
class Symbol;
class FunctionSymbol;
class DataType;

class IncompatibleOpError : public FrontEndError {
 public:
  IncompatibleOpError(
      const std::string& op,
      DataType* type1,
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
      const DataType& expected_type, const DataType& actual_type,
      const location& loc);
};

class BreakError : public FrontEndError {
 public:
  BreakError(const BreakNode& node, const location& loc);
};

class UndeclaredIdentifierError : public FrontEndError {
 public:
  UndeclaredIdentifierError(const std::string& identifier, const location& loc);
};

class NoSuchFieldError : public FrontEndError {
 public:
  NoSuchFieldError(
      const std::string& class_name, const std::string& field_name,
      const location& loc);
};

class NoSuchMemberFunctionError : public FrontEndError {
 public:
  NoSuchMemberFunctionError(
      const std::string& class_name, const std::string& func_name,
      const location& loc);
};

// @brief Throw this exception when the found symbol is not the one expected.
// For example: we expected a variable symbol but found a function.
//class InproperSymbolError : public FrontEndError {
 //public:
  //InproperSymbolError(
      //const std::string& expected_symbol, const std::string& actual_symbol, const location& loc);
//};

}  // namespace flang

#endif
