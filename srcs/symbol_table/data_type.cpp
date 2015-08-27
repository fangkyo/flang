#include "base/check.h"
#include "symbol_table/data_type.h"
#include "symbol_table/symbol_info.h"

namespace flang {

bool DataType::equals (const DataType& dtype) const {
  if (this == &dtype || dtype.getType() == type_) {
    return true;
  }
  return false;
}

VoidType VoidType::instance_;
Int32Type Int32Type::instance_;
Int64Type Int64Type::instance_;
CharType CharType::instance_;
BoolType BoolType::instance_;
DoubleType DoubleType::instance_;
StringType StringType::instance_;

bool ClassType::equals(const DataType& dtype) const {
  if (dtype.getType() != DataType::DATA_TYPE_CLASS) {
    return false;
  }
  const ClassType& class_type = static_cast<const ClassType&>(dtype);
  if (this == &class_type) {
    return true;
  }
  return class_symbol_->equals(*(class_type.getClassSymbol()));
}

std::string ClassType::getName() const {
  return class_symbol_->getName();
}

ClassType::ClassType(ClassSymbol* class_symbol) :
  DataType(DATA_TYPE_CLASS), class_symbol_(class_symbol) {
  CHECK(class_symbol);
}

DataType* DataTypeFactory::getClassType(ClassSymbol* class_symbol) {
  CHECK(class_symbol);
  return class_symbol->getClassType();
}

}  // namespace flang:
