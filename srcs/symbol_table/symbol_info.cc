#include "symbol_table/symbol_info.h"

namespace flang {

SymbolInfo::SymbolInfo(const std::string& name, symbol_info::SymbolType type) :
  name_(name), type_(type) {
}

const std::string SymbolInfo::toString() {
  return symbol_info::SymbolType_Name(this->type_);
}

ClassInfo::ClassInfo(const std::string& name) :
  SymbolInfo(name, symbol_info::CLASS) {
}

void ClassInfo::execute(SymbolInfoHandler* handler) {
  handler->handle(this);
}

FunctionInfo::FunctionInfo(const std::string& name) :
  SymbolInfo(name, symbol_info::FUNCTION) {
}

void FunctionInfo::execute(SymbolInfoHandler* handler) {
  handler->handle(this);
}

VariableInfo::VariableInfo(const std::string& name) :
  SymbolInfo(name, symbol_info::CLASS) {
}

void VariableInfo::execute(SymbolInfoHandler* handler) {
  handler->handle(this);
}

}

