#include <algorithm>

#include "symbol_table/scope.h"
#include "symbol_table/symbol.h"
#include "symbol_table/symbol_table.h"

namespace flang {

// static
log4cxx::LoggerPtr SymbolTable::logger_(
    log4cxx::Logger::getLogger("flang.SymbolTable"));

SymbolTable::SymbolTable(){
  scope_stack_.emplace_back(new Scope());
}

SymbolTable::~SymbolTable() {
  CHECK_EQ_MSG(scope_stack_.size(), 1,
               "There is scope left in scope track except the global one.");
  for (auto* scope : scope_stack_) {
    if (scope->isOwnedBySymbolTable()) {
      delete scope;
    }
  }
  scope_stack_.clear();
}

void SymbolTable::enter() {
  enter(new Scope());
}

void SymbolTable::enter(Scope* scope) {
  CHECK(scope);
  scope_stack_.push_front(scope);
  if (scope->getName().length()) {
    namespace_.push_back(scope->getName());
  }
}

void SymbolTable::exit() {
  CHECK_GT_MSG(scope_stack_.size(), 1, "Can't pop global scope.");
  Scope* scope = scope_stack_.front();
  scope_stack_.pop_front();
  // Pop the namespace if it isn't a anonymous scope
  if (scope->getName().length()) {
    CHECK_EQ(namespace_.back(), scope->getName());
    namespace_.pop_back();
  }
  if (scope->isOwnedBySymbolTable()) {
    delete scope;
  }
}

void SymbolTable::insert(
    const std::string& name, Symbol* symbol_info) {
  CHECK_GT(scope_stack_.size(), 0);
  Scope* local_scope = scope_stack_.front();
  local_scope->insert(name, symbol_info);
}

// Look up name starting in the first table in the list.
// If it is not there, then look up name in each successive table in the list.
Symbol* SymbolTable::lookup(const std::string& name) {
  for (auto& scope : scope_stack_) {
    Symbol* symbol = scope->lookup(name);
    if (symbol != nullptr) {
      return symbol;
    }
  }
  return nullptr;
}

Symbol* SymbolTable::lookup(const std::vector<std::string*>& qualifiers,
                            const std::string& name) {
  if (qualifiers.empty()) {
    return lookup(name);
  }
  for (auto& scope : scope_stack_) {
    auto iter = qualifiers.begin();
    Symbol* symbol(nullptr);
    // The scope which probably has the symbol user are looking for.
    Scope* symbol_scope(nullptr);
    while (iter != qualifiers.end() && (symbol = scope->lookup(**iter))) {
      symbol_scope = symbol->getScope();
      if (nullptr == symbol_scope) {
        break;
      }
      ++iter;
    }
    if (nullptr != symbol_scope && iter == qualifiers.end()) {
      return symbol_scope->lookup(name);
    }
  }
  return nullptr;
}

}  // namespace flang
