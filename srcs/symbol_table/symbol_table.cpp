#include "symbol_table.h"

namespace flang {

SymbolTable::SymbolTable(){

}

void SymbolTable::pushScope(AbstractScope* scope) {
  scope_stack_.push_back(scope);
}

void SymbolTable::insert(
    const std::string& name, SymbolInfo* symbol_info, bool global) {
  AbstractScope* local_scope = scope_stack_.last();
  local_scope->insert(name, symbol_info);
  if(global) {
    std::string qualifier = getNamespace();
    std::string symbol_name;
    if (!qualifier.empty()) {
      symbol_name = qualifier + "." + name;
    }
    global_scope_.insert(symbol_name, symbol_info);
  }
}

SymbolInfo* SymbolTable::lookup(const std::name) {
  AbstractScope* local_scope = scope_stack_.last();
  SymbolInfo* symbol_info = local_scope->lookup(name, symbol_info);
  if (nullptr == symbol_info) {
    symbol_info = global_scope_.lookup(name);
  }
  return symbol_info;
}

std::string SymbolTable::getNamespace() {
  return "";
}

}  // namespace flang
