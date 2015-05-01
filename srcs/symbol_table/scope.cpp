#include <memory>

#include <boost/assign/ptr_map_inserter.hpp>

#include "symbol_table/scope.h"

using boost::assign::ptr_map_insert;


namespace flang {

AbstractScope::AbstractScope() {
  // Insert primitive type entries to data_type_map_
/*   ptr_map_insert<Int32TypeEntry>(data_type_map_)("int32"); */
  // ptr_map_insert<CharTypeEntry>(data_type_map_)("char");
  // ptr_map_insert<StringTypeEntry>(data_type_map_)("string");
  /* ptr_map_insert<BoolTypeEntry>(data_type_map_)("bool"); */
}

void AbstractScope::insert(const std::string& name, SymbolInfo* symbol_info) {
  std::auto_ptr<SymbolInfo> ptr(symbol_info);
  symbol_map_.insert(name, ptr);
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

}  // namespace flang
