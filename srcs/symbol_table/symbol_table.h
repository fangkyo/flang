#ifndef SYMBOL_TABLE
#define SYMBOL_TABLE

#include <memory>
#include <unordered_map>
#include <vector>

using namespace std;

class SymbolTable {
 public:
  SymbolTable();
  virtual ~SymbolTable();

  // Push a scope to the scope stack
  void pushScope();
  // Pop a scope from the scope stack
  void popScope();
  // Add a function
  void addFunction(const string& pkgName);
  // Add a Variable
  void addVariable(const string& pkgName);

  void findFunction(const string& pkgName,
                    const string& funcName,
                    vector<string>* candidates);

  // Find a variable specified by name, return the variable node if exists.
  // Otherwise return NULL.
  bool findVariable();

  // Find a function specified by name, return the function node if exists.
  // Otherwise return Null.
  bool findFunction(const string& name, vector<string>* candidates);

  // Find a class
  bool findClass(const string& name);

 private:
  // Child Scope
  unique_ptr<SymbolTable> m_child;
  // Parent Scope
  SymbolTable* m_parent;
  unordered_map<string, string> m_name_map;
};

#endif
