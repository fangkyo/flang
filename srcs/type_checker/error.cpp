#include "boost/format.hpp"

#include "base/check.h"
#include "exception/error.h"
#include "symbol_table/symbol_info.h"

namespace flang {

RedefineSymbolError::RedefineSymbolError(
    SymbolInfo* existing_symbol, SymbolInfo* redefined_symbol, int lineno) :
    Error(lineno),
    existing_symbol_(existing_symbol),
    redefined_symbol_(redefined_symbol) {
  CHECK(existing_symbol);
  CHECK(redefined_symbol);
  message_ = boost::str(
      boost::format("Symbol %s has been defined.")
      % existing_symbol_->getName());
}


DataTypeNotEqualError::DataTypeNotEqualError(
    const std::string& type1, const std::string& type2, int lineno)
    : Error(lineno) {
  message_ = boost::str(boost::format(
      "Type '%s' is not equals to type '%s'") % type1 % type2);
}

DataTypeNotPrintableError::DataTypeNotPrintableError(
    const DataType& data_type, int lineno) : Error(lineno) {
  message_ = boost::str(
      boost::format("Type '%s' is not printable.") % data_type.getName());
}


NotAssignableError::NotAssignableError(
    const ExpNode& left, const ExpNode& right, int lineno) : Error(lineno) {
  message_ = boost::str(boost::format("Can't assign '%s' to '%s'")
                        % left.getType()->getName()
                        % right.getType()->getName());
}
}  // namespace flang

