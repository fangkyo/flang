#ifndef SYMBOL_INFO_H_
#define SYMBOL_INFO_H_

#include <string>

#include "symbol_table/symbol_info.pb.h"

namespace flang {

class SymbolInfoHandler;

// SymbolInfo is the information of a symbol in the symbol table.
class SymbolInfo {
 public:
  SymbolInfo(const std::string& name, symbol_info::SymbolType type);
  virtual ~SymbolInfo() {}

  const std::string& getName() { return name_; }
  void setName(const std::string& name) { name_ = name; }

  symbol_info::SymbolType getType() { return type_; }

  virtual const std::string toString();
  virtual void execute(SymbolInfoHandler*) = 0;

 protected:
  std::string name_;
  symbol_info::SymbolType type_;
};

class ClassInfo : public SymbolInfo {
 public:
  ClassInfo(const std::string& name);
  void execute(SymbolInfoHandler* handler);
};

class FunctionInfo : public SymbolInfo {
 public:
  FunctionInfo(const std::string& name);
  void execute(SymbolInfoHandler* handler);
};

class VariableInfo : public SymbolInfo {
 public:
  VariableInfo(const std::string& name);
  void execute(SymbolInfoHandler* handler);
};

class SymbolInfoHandler {
 public:
  virtual void handle(ClassInfo*) {}
  virtual void handle(FunctionInfo*) {}
  virtual void handle(VariableInfo*) {}

 protected:
  SymbolInfoHandler() {}
};

}  // namespace flang

#endif
