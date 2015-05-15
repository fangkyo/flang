#include <algorithm>

#include <boost/format.hpp>

#include "symbol_table/symbol_info.h"

namespace flang {

bool ArrayType::equals(const DataType& dtype) const {
  if (dtype.getType() != DATA_TYPE_ARRAY) {
    return false;
  }
  const ArrayType* array_type = static_cast<const ArrayType*>(&dtype);
  if (this == array_type) {
    return true;
  }
  if (!data_type_->equals(*(array_type->getDataType())) &&
      dimension_ != array_type->dimension_) {
    return false;
  }
  return true;
}

bool ClassType::equals(const DataType& dtype) const {
  if (dtype.getType() != DATA_TYPE_CLASS) {
    return false;
  }
  const ClassType* class_type = static_cast<const ClassType*>(&dtype);
  if (this == class_type) {
    return true;
  }
  return class_info_->equals(*(class_type->class_info_));
}


SymbolInfo::SymbolInfo(SymbolType symbol_type) :
    symbol_type_(symbol_type) {
}

SymbolInfo::~SymbolInfo() {
}

bool SymbolInfo::equals(const SymbolInfo& symbol_info) const {
  if (this == &symbol_info) {
    return true;
  }
  return (name_ == symbol_info.name_ && qualifier_ == symbol_info.qualifier_ &&
          symbol_type_ == symbol_info.symbol_type_);
}

std::string SymbolInfo::getFullName() {
  if (qualifier_.empty()) {
    return name_;
  } else {
    boost::format fmt("%1%.%2%");
    fmt % qualifier_ % name_;
    return fmt.str();
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

VariableInfo::VariableInfo() :
    SymbolInfo(SymbolType::SYMBOL_VARIABLE) {
}

void VariableInfo::execute(SymbolInfoHandler* handler) {
  handler->handle(this);
}

}
