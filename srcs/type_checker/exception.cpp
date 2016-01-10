#include <boost/format.hpp>

#include "base/check.h"
#include "type_checker/exception.h"
#include "symbol_table/symbol.h"
#include "syntax_tree/ast_node_all.h"

namespace flang {

IncompatibleOpError::IncompatibleOpError(
    const std::string& op, DataType* type, const location& loc) : FrontEndError(loc) {
  boost::format format("Need \"%1%\" for type \"%2%\".");
  format % op % type->getName();
  setMessage(format.str());
}

IncompatibleOpError::IncompatibleOpError(
    const std::string& op, DataType* type1,
    DataType* type2, const location& loc) : FrontEndError(loc) {
  boost::format format(
      "Can't use \"%1%\" between type \"%2%\" and type \"%3%\".");
  format % op % type1->getName() % type2->getName();
  setMessage(format.str());
}

RedefineSymbolError::RedefineSymbolError(
    Symbol* existing_symbol, Symbol* redefined_symbol, const location& loc) :
    FrontEndError(loc) {
  CHECK(existing_symbol);
  CHECK(redefined_symbol);
  message_ = boost::str(
      boost::format("Symbol %s has been defined before %s")
      % existing_symbol->getName() % redefined_symbol->getName());
}


DataTypeNotEqualError::DataTypeNotEqualError(
    const DataType& type1, const DataType& type2, const location& loc)
    : FrontEndError(loc) {
  message_ = boost::str(boost::format(
      "Type '%s' is not equals to type '%s'")
      % type1.getName() % type2.getName());
}

DataTypeNotPrintableError::DataTypeNotPrintableError(
    const DataType& data_type, const location& loc) : FrontEndError(loc) {
  message_ = boost::str(
      boost::format("Type '%s' is not printable.") % data_type.getName());
}

NotAssignableError::NotAssignableError(
    const ExpNode& left, const ExpNode& right, const location& loc) : FrontEndError(loc) {
  //message_ = boost::str(boost::format("Can't assign '%s' to '%s'")
                        //% left.getType()->getName()
                        //% right.getType()->getName());
}

IncorrectTypeError::IncorrectTypeError(
    const DataType& expected_type,
    const DataType& actual_type,
    const location& loc) : FrontEndError(loc) {
  message_ = boost::str(
      boost::format("Incorrect type '%1%', '%2%' required.")
      % actual_type.getName() % expected_type.getName());
}

BreakError::BreakError(const BreakNode& node, const location& loc)
  : FrontEndError(loc) {
  message_ = "Break statement is not allowed here.";
}


UndeclaredIdentifierError::UndeclaredIdentifierError(
    const std::string& identifier, const location& loc) : FrontEndError(loc) {
  boost::format fmt("Use of undeclared identifier '%1%'.");
  setMessage(boost::str(fmt % identifier));
}

NoSuchFieldError::NoSuchFieldError(
    const std::string& class_name, const std::string& field_name,
    const location& loc) : FrontEndError(loc) {
  boost::format fmt("%1% has no such field '%2%'.");
  setMessage(boost::str(fmt % class_name % field_name));
}

NoSuchMemberFunctionError::NoSuchMemberFunctionError(
    const std::string& class_name, const std::string& func_name,
    const location& loc) : FrontEndError(loc) {
  boost::format fmt("Class %1% doesn't have member function %2%");
  setMessage(boost::str(fmt % class_name % func_name));
}

}  // namespace flang

