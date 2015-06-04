#include <algorithm>

#include "symbol_table/symbol_table.h"

namespace flang {

SymbolTable::SymbolTable(){
  scope_stack_.emplace_back(new Scope());
}

void SymbolTable::pushScope(const std::shared_ptr<Scope>& scope) {
  scope_stack_.emplace_front(scope);
}

void SymbolTable::pushScope(Scope* scope) {
  scope_stack_.emplace_front(scope);
}

void SymbolTable::popScope() {
  CHECK_GT_MSG(scope_stack_.size(), 1, "Can't pop global scope.");
  scope_stack_.pop_front();
}

void SymbolTable::insert(
    const std::string& name, SymbolInfo* symbol_info) {
  std::shared_ptr<Scope>& local_scope = scope_stack_.front();
  local_scope->insert(name, symbol_info);
}

// Look up name starting in the first table in the list.
// If it is not there, then look up name in each successive table in the list.
SymbolInfo* SymbolTable::lookup(const std::string& name) {
  for (auto& scope : scope_stack_) {
    SymbolInfo* symbol_info = scope->lookup(name);
    if (symbol_info != nullptr) {
      return symbol_info;
    }
  }
  return nullptr;
}

SymbolInfo* SymbolTable::lookup(const std::vector<std::string*>& qualifiers,
                                const std::string& name) {
  CHECK_MSG(qualifiers.size(),
            "Using SymbolTable::lookup(name) instead.");
  for (auto& scope : scope_stack_) {
    auto iter = qualifiers.begin();
    SymbolInfo* symbol_info(nullptr);
    // The scope which probably has the symbol user are looking for.
    Scope* symbol_scope(nullptr);
    while (iter != qualifiers.end() && (symbol_info = scope->lookup(**iter))) {
      symbol_scope = symbol_info->getScope();
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
