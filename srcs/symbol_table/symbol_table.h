#ifndef SYMBOL_TABLE_H_
#define SYMBOL_TABLE_H_

#include <memory>
#include <unordered_map>
#include <vector>
#include <list>

namespace flang {

class AbstractScope {

 protected:
  std::unordered_map<std::string, std::string> map_;

};

class SymbolTable {
 public:
  enum ScopeType{
    CLASS_SCOPE,
    FUNCTION_SCOPE,
    BLOCK_SCOPE,
  };

  SymbolTable();
  virtual ~SymbolTable();

  // Push a scope to the scope stack
  void pushScope(ScopeType scope_type);
  // Pop a scope from the scope stack
  void popScope();

  // Add a function
  void addFunction(const std::string& pkgName);
  // Add a Variable
  void addVariable(const std::string& pkgName);

  void findFunction(const std::string& pkgName,
                    const std::string& funcName,
                    std::vector<std::string>* candidates);

  // Find a variable specified by name, return the variable node if exists.
  // Otherwise return NULL.
  bool findVariable();

  // Find a function specified by name, return the function node if exists.
  // Otherwise return Null.
  bool findFunction(const std::string& name,
                    std::vector<std::string>* candidates);

  // Find a class
  bool findClass(const std::string& name);

 private:
  std::list<AbstractScope*> scope_stack_;
};

}  // namespace flang

#endif
