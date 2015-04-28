#include <boost/format.hpp>

#include "symbol_table/symbol_info.h"

namespace flang {

SymbolInfo::SymbolInfo(SymbolType type) : type_(type) {
}

const std::string SymbolInfo::toString() {
  return SymbolType_Name(type_);
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

FunctionInfo::FunctionInfo() :
  SymbolInfo(SymbolType::SYMBOL_FUNCTION) {
}

void FunctionInfo::execute(SymbolInfoHandler* handler) {
  handler->handle(this);
}

VariableInfo::VariableInfo() :
  SymbolInfo(SymbolType::SYMBOL_VARIABLE),
  class_info_(nullptr) {
}

void VariableInfo::execute(SymbolInfoHandler* handler) {
  handler->handle(this);
}

}

