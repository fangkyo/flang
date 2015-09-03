#include "base/check.h"
#include "symbol_table/scope.h"

namespace flang {

Scope::Scope() : owned_by_symtable_(true), parent_(nullptr) {
}

void Scope::insert(const std::string& name, Symbol* symbol) {
  symbol_map_[name] = symbol;
}

Symbol* Scope::lookup(const std::string& name,
                      std::set<Scope*>* exclusive_scopes) {
  if (exclusive_scopes) {
    if (exclusive_scopes->find(this) == exclusive_scopes->end()) {
      exclusive_scopes->insert(this);
    } else {
      return nullptr;
    }
  }
  auto iter = symbol_map_.find(name);
  if (iter == symbol_map_.end()){
    if (parent_) {
      return parent_->lookup(name, exclusive_scopes);
    } else {
      return nullptr;
    }
  } else {
    return iter->second;
  }
}

}  // namespace flang
