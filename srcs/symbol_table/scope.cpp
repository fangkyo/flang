#include "symbol_table/scope.h"
#include "symbol_table/symbol_info.h"

namespace flang {

void Scope::insert(const std::string& name, Symbol* symbol) {
  std::string& key = const_cast<std::string&>(name);
  if (symbol_map_.find(key) != symbol_map_.end()) {
    throw "Redefine";
  }
  symbol_map_.insert(key, symbol);
}

Symbol* Scope::lookup(const std::string& name) {
  auto iter = symbol_map_.find(name);
  if (iter == symbol_map_.end()){
    return nullptr;
  } else {
    return iter->second;
  }
}


}  // namespace flang
