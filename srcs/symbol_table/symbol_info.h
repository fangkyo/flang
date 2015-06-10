#ifndef SYMBOL_INFO_H_
#define SYMBOL_INFO_H_

#include <memory>
#include <string>
#include <vector>

#include "base/check.h"
#include "symbol_table/symbol_info.pb.h"

namespace flang {

class ClassInfo;
class FunctionInfo;
class Scope;
class SymbolInfoHandler;

class DataType {
 public:
  DataType(DataTypeEnum type) : type_(type) {}
  virtual bool equals (const DataType& dtype) const;
  virtual uint32_t size() const = 0;
  DataTypeEnum getType() const { return type_; }
  virtual bool isPrimitive() const { return true; }
  virtual std::string getName() const = 0;

 protected:
  DataTypeEnum type_;
};

class VoidType : public DataType {
 public:
  VoidType() : DataType(DATA_TYPE_VOID) {}
  uint32_t size() const override { return 0; }
  std::string getName() const override { return "void"; }
  bool isPrimitive() const { return false; }
};

class Int32Type : public DataType {
 public:
  Int32Type() : DataType(DATA_TYPE_INT32) {}
  uint32_t size() const override { return 4; }
  std::string getName() const  override { return "int32"; }
};

class Int64Type : public DataType {
 public:
  Int64Type() : DataType(DATA_TYPE_INT64) {}
  uint32_t size() const override { return 8; }
  std::string getName() const override { return "int64"; }
};

class FloatType : public DataType {
 public:
  FloatType() : DataType(DATA_TYPE_FLOAT) {}
  uint32_t size() const override { return 8; }
  std::string getName() const override { return "float"; }
};

class StringType : public DataType {
 public:
  StringType() : DataType(DATA_TYPE_STRING) {}
  uint32_t size() const override { return 4; }
  std::string getName() const override { return "string"; }
};

class BoolType : public DataType {
 public:
  BoolType() : DataType(DATA_TYPE_BOOL) {}
  uint32_t size() const override { return 1; }
  std::string getName() const override { return "bool"; }
};

class CharType : public DataType {
 public:
  CharType() : DataType(DATA_TYPE_CHAR) {}
  uint32_t size() const override { return 1; }
  std::string getName() const override { return "char"; }
};

class ArrayType : public DataType {
 public:
  ArrayType() : DataType(DATA_TYPE_ARRAY) {}
  uint32_t size() const override { return 4; }
  bool isPrimitive() const override { return false; }

  std::string getName() const override;

  DataType* getDataType() const { return data_type_.get(); }
  void setDataType(DataType* dtype) {
    CHECK_NE(dtype->getType(), DATA_TYPE_ARRAY);
    data_type_.reset(dtype);
  }

  bool equals (const DataType& dtype) const override;

 private:
  std::unique_ptr<DataType> data_type_;
  uint32_t dimension_;
};

class ClassType : public DataType {
 public:
  ClassType(ClassInfo* class_info = nullptr) :
      DataType(DATA_TYPE_CLASS), class_info_(class_info) {}

  ClassInfo* getClassInfo() const { return class_info_; }
  void setClassInfo(ClassInfo* class_info) { class_info_ = class_info; }
  uint32_t size() const override { return 4; }
  bool isPrimitive() const override { return false; }
  std::string getName() const override;
  bool equals(const DataType& dtype) const override;

 protected:
  ClassInfo* class_info_;
};


// SymbolInfo is the information of a symbol in the symbol table.
class SymbolInfo {
 public:
  virtual ~SymbolInfo();

  const std::string& getName() { return name_; }
  void setName(const std::string& name) { name_ = name; }

  SymbolType getSymbolType() const { return symbol_type_; }

  virtual void execute(SymbolInfoHandler*) = 0;

  virtual bool equals(const SymbolInfo& symbol_info) const;

  virtual Scope* getScope() { return nullptr; }

 protected:
  SymbolInfo(SymbolType symbol_type);

  std::string name_;
  SymbolType symbol_type_;
};

class VariableInfo : public SymbolInfo {
 public:
  VariableInfo();
  void execute(SymbolInfoHandler* handler) override;

  void setDataType(DataType* data_type) { data_type_.reset(data_type); }
  const DataType* getDataType() { return data_type_.get(); }

  Scope* getScope() override;

 private:
  std::unique_ptr<DataType> data_type_;
};

class FunctionInfo : public SymbolInfo {
 public:
  FunctionInfo();
  void execute(SymbolInfoHandler* handler) override;

  std::vector<VariableInfo*>& getParameters() { return parameters_; }
  void addParameter(VariableInfo* parameter);

  const DataType* getReturnType() const {
    return return_type_.get();
  }
  void setReturnType(DataType* dtype) {
    return_type_.reset(dtype);
  }

  Scope* getScope() override { return scope_.get(); }
  void setScope(std::shared_ptr<Scope>& scope) { scope_ = scope; }

 private:
  std::shared_ptr<Scope> scope_;
  std::unique_ptr<DataType> return_type_;
  std::vector<VariableInfo*> parameters_;
};

class ClassInfo : public SymbolInfo {
 public:
  ClassInfo();
  void execute(SymbolInfoHandler* handler) override;

  const std::vector<FunctionInfo*>& getMemberFuncs() { return member_funcs_; }
  void addMemberFunc(FunctionInfo* func_info);

  const std::vector<VariableInfo*>& getMemberVars() { return member_vars_; }
  void addMemberVar(VariableInfo* var_info);

  bool equals(const SymbolInfo& symbol_info) const override;

  Scope* getScope() override { return scope_.get(); }
  void setScope(std::shared_ptr<Scope>& scope) { scope_ = scope; }

 private:
  std::shared_ptr<Scope> scope_;
  std::vector<FunctionInfo*> member_funcs_;
  std::vector<VariableInfo*> member_vars_;
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
