#include "symbol_table/scope.h"

namespace flang {

AbstractScope::AbstractScope() : SymbolInfo(SYMBOL_SCOPE) {
}

void AbstractScope::insert(const std::string& name, SymbolInfo* symbol_info) {
  std::string& key = const_cast<std::string&>(name);
  if (symbol_map_.find(key) != symbol_map_.end()) {
    throw "Redefine";
  }
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

ClassInfo::ClassInfo() :
    SymbolInfo(SymbolType::SYMBOL_CLASS) {
}

void ClassInfo::execute(SymbolInfoHandler* handler) {
  handler->handle(this);
}


bool ClassInfo::equals(const SymbolInfo& symbol_info) const {
  if (this == &symbol_info) {
    return true;
  }
  if (!SymbolInfo::equals(symbol_info)) {
    return false;
  }
  const ClassInfo* class_info = dynamic_cast<const ClassInfo*>(&symbol_info);
  if (member_vars_.size() == class_info->member_vars_.size()) {
    return false;
  }

  bool member_vars_equal =
      std::equal(member_vars_.begin(), member_vars_.end(),
           class_info->member_vars_.begin(),
           [](const VariableInfo* a, const VariableInfo* b) {
               return a->equals(*b); });
  if (!member_vars_equal) {
    return false;
  }

  if (member_funcs_.size() == class_info->member_funcs_.size()) {
    return false;
  }
  bool member_funcs_equal =
      std::equal(member_funcs_.begin(), member_funcs_.end(),
             class_info->member_funcs_.begin(),
             [](const FunctionInfo* a, const FunctionInfo* b) {
                return a->equals(*b); });
  if (!member_funcs_equal) {
    return false;
  }
  return true;
}

FunctionInfo::FunctionInfo() :
    SymbolInfo(SymbolType::SYMBOL_FUNCTION) {
}

void FunctionInfo::execute(SymbolInfoHandler* handler) {
  handler->handle(this);
}

}  // namespace flang
