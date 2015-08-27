#include <algorithm>

#include <boost/format.hpp>

#include "base/check.h"
#include "symbol_table/symbol.h"
#include "symbol_table/scope.h"

namespace flang {


Symbol::Symbol(SymbolType symbol_type) :
    symbol_type_(symbol_type), data_type_(nullptr) {
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

VariableSymbol::VariableSymbol() :
    Symbol(Symbol::SYMBOL_VARIABLE) {
}

void VariableSymbol::execute(SymbolHandler* handler) {
  handler->handle(this);
}

FunctionSymbol::FunctionSymbol() :
    Symbol(Symbol::SYMBOL_FUNCTION) {
  scope_.setOwnedBySymbolTable(false);
}

void FunctionSymbol::execute(SymbolHandler* handler) {
  handler->handle(this);
}

void FunctionSymbol::addParameter(VariableSymbol* parameter) {
  parameters_.push_back(parameter);
  scope_.insert(parameter->getName(), parameter);
}

ClassSymbol::ClassSymbol() :
    Symbol(Symbol::SYMBOL_CLASS), class_type_(this), super_class_(nullptr) {
  setDataType(&class_type_);
  scope_.setOwnedBySymbolTable(false);
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

void ClassSymbol::setName(const std::string& name) {
  CHECK_MSG(name.size(), "Can't assign the class an empty name.");
  scope_.setName(name);
  Symbol::setName(name);
}

void ClassSymbol::execute(SymbolHandler* handler) {
  CHECK(handler);
  handler->handle(this);
}

void ClassSymbol::setSuperClass(ClassSymbol* super_class) {
  CHECK(super_class);
  ClassSymbol* ancestor_class = super_class;
  while (nullptr != ancestor_class) {
    CHECK_NE_MSG(this, ancestor_class, "Super class circulation exists.");
  }
  super_class_ = super_class;
}

}  // namespace flang

