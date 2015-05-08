#ifndef SYMBOL_INFO_H_
#define SYMBOL_INFO_H_

#include <memory>
#include <string>
#include <vector>

#include "symbol_table/symbol_info.pb.h"

namespace flang {

class SymbolInfoHandler;

// SymbolInfo is the information of a symbol in the symbol table.
class SymbolInfo {
 public:
  SymbolInfo(SymbolInfoProto* symbol_info_proto, bool is_owner = true);
  virtual ~SymbolInfo();

  std::string getFullName();

  virtual const std::string toString();
  virtual void execute(SymbolInfoHandler*) = 0;

  const SymbolInfoProto& getSymbolInfoProto() { return * symbol_info_proto_; }
  SymbolInfoProto* getMutableSymbolInfoProto() {
    return symbol_info_proto_.get();
  }

 protected:
  std::unique_ptr<SymbolInfoProto> symbol_info_proto_;
  bool is_owner_;
};


// class FunctionInfo : public SymbolInfo {
 // public:
  // FunctionInfo();
  // void execute(SymbolInfoHandler* handler);
// };

// class ClassInfo : public SymbolInfo {
 // public:
  // ClassInfo();
  // void execute(SymbolInfoHandler* handler);

 // private:
  // std::vector<FunctionInfo*> methods_;
// };

// class VariableInfo : public SymbolInfo {
 // public:
  // VariableInfo();
  // void execute(SymbolInfoHandler* handler);

  // void setDataType(DataType data_type) { data_type_ = data_type; }
  // DataType getDataType() { return data_type_; }

 // private:
  // DataType data_type_;
  // ClassInfo* class_info_;
// };

class SymbolInfoHandler {
 public:
/*   virtual void handle(ClassInfo*) {} */
  // virtual void handle(FunctionInfo*) {}
  /* virtual void handle(VariableInfo*) {} */

 protected:
  SymbolInfoHandler() {}
};

}  // namespace flang

#endif
