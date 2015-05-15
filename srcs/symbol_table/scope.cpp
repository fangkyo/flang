#include <memory>

#include <boost/assign/ptr_map_inserter.hpp>

#include "symbol_table/scope.h"

namespace flang {

AbstractScope::AbstractScope() : SymbolInfo(SYMBOL_SCOPE) {
}

void AbstractScope::insert(const std::string& name, SymbolInfo* symbol_info) {
  std::string& key = const_cast<std::string&>(name);
  symbol_map_.insert(key, symbol_info);
}

SymbolInfo* AbstractScope::lookup(const std::string& name) {
  auto iter = symbol_map_.find(name);
  if (iter == symbol_map_.end()){
    return nullptr;
  } else {
    return iter->second;
  }
}


bool AbstractScope::exists(const std::string& name) {
  return symbol_map_.find(name) == symbol_map_.end();
}

GlobalScope::GlobalScope() {
  this->setName(".");
}

FunctionScope::FunctionScope(FunctionInfo* func_info) :
    func_info_(func_info) {
}

ClassScope::ClassScope(ClassInfo* class_info) :
    class_info_(class_info) {
}

}  // namespace flang
