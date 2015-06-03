#ifndef ABSTRACT_SCOPE_H_
#define ABSTRACT_SCOPE_H_

#include <cstdint>
#include <string>
#include <list>
#include <unordered_map>
#include <vector>

#include <boost/ptr_container/ptr_map.hpp>

#include "symbol_table/symbol_info.h"

namespace flang {

/* enum ScopeType { */
  // SCOPE_BLOCK,
  // SCOPE_GLOBAL,
  // SCOPE_WHILE,
  // SCOPE_FUNC,
  // SCOPE_CLASS,
  // SCOPE_CLASS_FUNC,
/* }; */

class AbstractScope : public SymbolInfo {
 public:
  virtual ~AbstractScope() {}

  virtual void insert(const std::string& name, SymbolInfo* symbol_info);
  virtual SymbolInfo* lookup(const std::string& name);
  virtual AbstractScope* lookupScope(const std::string& name);

  // const std::string& getName() const { return name_; }
  // void setName(const std::string& name) { name_ = name; }

  AbstractScope* getParent() { return parent_; }
  void setParent(AbstractScope* parent) { parent_ = parent; }

 protected:
  AbstractScope();

  // Map from symbol name to symbol info.
  boost::ptr_map<std::string, SymbolInfo> symbol_map_;

  std::string name_;
  AbstractScope* parent_;
};

class FunctionInfo : public AbstractScope {
 public:
  FunctionInfo();
  void execute(SymbolInfoHandler* handler);

  std::vector<VariableInfo*> getParameters() { return parameters_; }
  void addParameter(VariableInfo* parameter) {
    parameters_.push_back(parameter);
    insert(parameter->getName(), parameter);
  }

  const DataType* getReturnType() {
    return return_type_.get();
  }
  void setReturnType(DataType* dtype) {
    return_type_.reset(dtype);
  }

  const AbstractScope* getScope() override { return this; }

 private:
  std::unique_ptr<DataType> return_type_;
  std::vector<VariableInfo*> parameters_;
};

class ClassInfo : public AbstractScope {
 public:
  ClassInfo();
  void execute(SymbolInfoHandler* handler) override;

  const std::vector<FunctionInfo*>& getMemberFuncs() { return member_funcs_; }
  void addMemberFunc(FunctionInfo* func_info) {
    member_funcs_.push_back(func_info);
    insert(func_info->getName(), func_info);
  }

  const std::vector<VariableInfo*>& getMemberVars() { return member_vars_; }
  void addMemberVar(VariableInfo* var_info) {
    member_vars_.push_back(var_info);
    insert(var_info->getName(), var_info);
  }

  bool equals(const SymbolInfo& symbol_info) const override;

  const AbstractScope* getScope() override { return this; }

 private:
  std::vector<FunctionInfo*> member_funcs_;
  std::vector<VariableInfo*> member_vars_;
};

}  // namespace flang

#endif

