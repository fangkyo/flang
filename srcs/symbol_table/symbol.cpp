#include <algorithm>

#include <boost/format.hpp>

#include "base/check.h"
#include "symbol_table/symbol.h"
#include "symbol_table/scope.h"

namespace flang {


Symbol::Symbol(const std::string& name, SymbolType symbol_type) :
    name_(name), symbol_type_(symbol_type), data_type_(nullptr) {
}

Symbol::~Symbol() {
}

bool Symbol::equals(const Symbol& symbol) const {
  if (this == &symbol) {
    return true;
  }
  return (name_ == symbol.name_ &&
          symbol_type_ == symbol.symbol_type_);
}

VariableSymbol::VariableSymbol(const std::string& name) :
    Symbol(name, Symbol::SYMBOL_VARIABLE) {
  CHECK(name.length());
}

void VariableSymbol::execute(SymbolHandler* handler) {
  handler->handle(this);
}

FunctionSymbol::FunctionSymbol(const std::string& name) :
    Symbol(name, Symbol::SYMBOL_FUNCTION) {
  CHECK(name.length());
  scope_.setOwnedBySymbolTable(false);
  // Insert this function to its own scope when constructing
  scope_.insert(getName(), this);
}

void FunctionSymbol::execute(SymbolHandler* handler) {
  handler->handle(this);
}

void FunctionSymbol::addParameter(VariableSymbol* parameter) {
  parameters_.push_back(parameter);
  scope_.insert(parameter->getName(), parameter);
}

ClassSymbol::ClassSymbol(const std::string& name) :
    Symbol(name, Symbol::SYMBOL_CLASS),
    class_type_(this), super_class_(nullptr) {
  CHECK(name.length());
  setDataType(&class_type_);
  scope_.setOwnedBySymbolTable(false);
  // Insert this symbol to its own scope when constructing
  scope_.insert(getName(), this);
  scope_.setName(name);
}

void ClassSymbol::addFunction(FunctionSymbol* function) {
  CHECK(function);
  member_funcs_.push_back(function);
  scope_.insert(function->getName(), function);
}

void ClassSymbol::addVariable(VariableSymbol* variable) {
  CHECK(variable);
  member_vars_.push_back(variable);
  scope_.insert(variable->getName(), variable);
}

void ClassSymbol::execute(SymbolHandler* handler) {
  CHECK(handler);
  handler->handle(this);
}

void ClassSymbol::setSuperClass(ClassSymbol* super_class) {
  CHECK(super_class);
  ClassSymbol* ancestor_class = super_class;
  while (ancestor_class) {
    CHECK_NE_MSG(this, ancestor_class, "Super class circulation exists.");
    ancestor_class = ancestor_class->getSuperClass();
  }
  super_class_ = super_class;
  scope_.setParent(super_class->getScope());
}

}  // namespace flang

