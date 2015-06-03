#include <algorithm>

#include "symbol_table.h"

namespace flang {

SymbolTable::SymbolTable(){
}

void SymbolTable::pushScope(AbstractScope* scope) {
  scope_stack_.push_front(scope);
}

void SymbolTable::popScope() {
  CHECK_GT_MSG(scope_stack_.size(), 1, "Can't pop global scope.");
  AbstractScope* scope = scope_stack_.front();
  scope_stack_.pop_front();
  // Since parent scope doesn't have the ownship of anonymous scope, we have to
  // delete the scope in this function.
  // TODO: using shared_ptr instead.
  if (scope->getName().empty()) {
    delete scope;
  }
}

void SymbolTable::insert(
    const std::string& name, SymbolInfo* symbol_info) {
  AbstractScope* local_scope = scope_stack_.front();
  local_scope->insert(name, symbol_info);
}

// Look up name starting in the first table in the list.
// If it is not there, then look up name in each successive table in the list.
SymbolInfo* SymbolTable::lookup(const std::string& name) {
  for (auto* scope : scope_stack_) {
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
  auto iter = std::search(
      scope_stack_.rbegin(), scope_stack_.rend(),
      qualifiers.cbegin(), qualifiers.cend(),
      [](const AbstractScope* scope, const std::string& qualifier) -> bool {
          return scope->getName() == qualifier;
      });
  if (iter == scope_stack_.rend()) {
    return nullptr;
  } else {
    iter += qualifiers.size() - 1;
    return iter->lookup(name);
  }
}

}  // namespace flang
