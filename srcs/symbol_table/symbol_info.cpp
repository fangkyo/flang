#include <boost/format.hpp>

#include "symbol_table/symbol_info.h"

namespace flang {

SymbolInfo::SymbolInfo(SymbolInfoProto* symbol_info_proto, bool is_owner) :
  symbol_info_proto_(symbol_info_proto),
  is_owner_(is_owner) {

}

SymbolInfo::~SymbolInfo() {
  if (!is_owner_) {
    symbol_info_proto_.release();
  }
}

const std::string SymbolInfo::toString() {
  return SymbolType_Name(symbol_info_proto_->type());
}

std::string SymbolInfo::getFullName() {
  if (symbol_info_proto_->qualifier().empty()) {
    return symbol_info_proto_->name();
  } else {
    boost::format fmt("%1%.%2%");
    fmt % symbol_info_proto_->qualifier() % symbol_info_proto_->name();
    return fmt.str();
  }
}

// ClassInfo::ClassInfo() :
  // SymbolInfo(SymbolType::SYMBOL_CLASS) {
// }

// void ClassInfo::execute(SymbolInfoHandler* handler) {
  // handler->handle(this);
// }

// FunctionInfo::FunctionInfo() :
  // SymbolInfo(SymbolType::SYMBOL_FUNCTION) {
// }

// void FunctionInfo::execute(SymbolInfoHandler* handler) {
  // handler->handle(this);
// }

// VariableInfo::VariableInfo() :
  // SymbolInfo(SymbolType::SYMBOL_VARIABLE),
  // class_info_(nullptr) {
// }

// void VariableInfo::execute(SymbolInfoHandler* handler) {
  // handler->handle(this);
// }

}

