#ifndef SYMBOL_INFO_H_
#define SYMBOL_INFO_H_

#include <string>
#include <vector>

#include "symbol_table/symbol_info.pb.h"

namespace flang {

class SymbolInfoHandler;

// SymbolInfo is the information of a symbol in the symbol table.
class SymbolInfo {
 public:
  SymbolInfo(SymbolType type);
  virtual ~SymbolInfo() {}

  const std::string& getName() const { return name_; }
  void setName(const std::string& name) { name_ = name; }

  const std::string& getQualifier() const { return qualifier_; }
  void setQualifier(const std::string& qualifier) { qualifier_ = qualifier; }

  SymbolType getType() const { return type_; }

  std::string getFullName();

  virtual const std::string toString();
  virtual void execute(SymbolInfoHandler*) = 0;

 protected:
  std::string name_;
  std::string qualifier_;
  SymbolType type_;
};


class FunctionInfo : public SymbolInfo {
 public:
  FunctionInfo();
  void execute(SymbolInfoHandler* handler);
};

class ClassInfo : public SymbolInfo {
 public:
  ClassInfo();
  void execute(SymbolInfoHandler* handler);

 private:
  std::vector<FunctionInfo*> methods_;
};

class VariableInfo : public SymbolInfo {
 public:
  VariableInfo();
  void execute(SymbolInfoHandler* handler);

  void setDataType(DataType data_type) { data_type_ = data_type; }
  DataType getDataType() { return data_type_; }

 private:
  DataType data_type_;
  ClassInfo* class_info_;
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
