#ifndef SYMBOL_TABLE_H_
#define SYMBOL_TABLE_H_

#include <list>
#include <memory>
#include <unordered_map>
#include <vector>

#include <boost/ptr_container/ptr_vector.hpp>

#include "symbol_table/abstract_scope.h"
#include "symbol_table/scope.h"
#include "symbol_table/symbol_info.h"

namespace flang {

class SymbolTable {
 public:
  SymbolTable();

  // Push a scope to the scope stack
  void pushScope(AbstractScope* scope);
  void popScope();

  // Insert a symbol to symbol table. Insert to global scope also if global
  // is set to true.
  void insert(const std::string& name, SymbolInfo* symbol_info);

  // Look up the symbol specification for the given symbol name.
  // Return nullptr if it can't find anything.
  SymbolInfo* lookup(const std::string& name);

  SymbolInfo* lookup(const std::vector<std::string*>& qualifiers,
                     const std::string& name);

/*   // Add a function */
  // void addFunction(const std::string& pkgName);
  // // Add a Variable
  // void addVariable(const std::string& pkgName);

  // void findFunction(const std::string& pkgName,
                    // const std::string& funcName,
                    // std::vector<std::string>* candidates);

  // // Find a variable specified by name, return the variable node if exists.
  // // Otherwise return NULL.
  // bool findVariable();

  // // Find a function specified by name, return the function node if exists.
  // // Otherwise return Null.
  // bool findFunction(const std::string& name,
                    // std::vector<std::string>* candidates);

  // // Find a class
  /* bool findClass(const std::string& name); */

 private:
  std::list<AbstractScope*> scope_stack_;
};

}  // namespace flang

#endif
