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



VariableInfo::VariableInfo() :
    SymbolInfo(SymbolType::SYMBOL_VARIABLE) {
}

void VariableInfo::execute(SymbolInfoHandler* handler) {
  handler->handle(this);
}

}

