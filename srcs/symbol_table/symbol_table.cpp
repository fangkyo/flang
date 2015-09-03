#include <set>

#include <boost/range/adaptor/reversed.hpp>

#include "symbol_table/scope.h"
#include "symbol_table/symbol.h"
#include "symbol_table/symbol_table.h"

namespace flang {

// static
log4cxx::LoggerPtr SymbolTable::logger_(
    log4cxx::Logger::getLogger("flang.SymbolTable"));

SymbolTable::SymbolTable(){
  // Push the global scope
  scope_stack_.reserve(50);
  scope_stack_.push_back(new Scope());
}

SymbolTable::~SymbolTable() {
  CHECK_EQ_MSG(scope_stack_.size(), 1,
               "There are scopes left in scope stack except the global one.");
  // Delete the global scope
  delete scope_stack_[0];
  scope_stack_.clear();
}

void SymbolTable::enter() {
  enter(new Scope());
}

void SymbolTable::enter(Scope* scope) {
  CHECK(scope);
  scope_stack_.push_back(scope);
}

void SymbolTable::exit() {
  CHECK_GT_MSG(scope_stack_.size(), 1, "Can't pop global scope.");
  Scope* scope = scope_stack_.back();
  scope_stack_.pop_back();
  if (scope->isOwnedBySymbolTable()) {
    delete scope;
  }
}

void SymbolTable::insert(
    const std::string& name, Symbol* symbol) {
  CHECK_GT(scope_stack_.size(), 0);
  CHECK_MSG(name.length(), "Can't insert empty name.");
  CHECK(symbol);
  scope_stack_.back()->insert(name, symbol);
}

Symbol* SymbolTable::lookup(const std::string& name, bool global) {
  CHECK(name.length());
  if (global) {
    // Search the symbol from global scope
    return scope_stack_[0]->lookup(name);
  } else {
    std::set<Scope*> scope_set;
    for (Scope* scope : boost::adaptors::reverse(scope_stack_)) {
      Symbol* symbol = scope->lookup(name, &scope_set);
      if (symbol != nullptr) {
        return symbol;
      }
    }
  }
  return nullptr;
}

SymbolTableLock::SymbolTableLock(SymbolTable* symbol_table, Scope* scope) :
  symbol_table_(symbol_table) {
  CHECK(symbol_table_);
  if (scope) {
    symbol_table_->enter(scope);
  } else {
    symbol_table_->enter();
  }
}

SymbolTableLock::~SymbolTableLock() {
  symbol_table_->exit();
}

}  // namespace flang
