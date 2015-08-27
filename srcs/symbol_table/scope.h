#ifndef SYMBOL_TABLE_SCOPE_H_
#define SYMBOL_TABLE_SCOPE_H_

#include <cstdint>
#include <string>
#include <list>
#include <unordered_map>
#include <vector>

#include <boost/ptr_container/ptr_map.hpp>

namespace flang {

class Symbol;

class Scope {
 public:
  Scope() : owned_by_symtable_(true) {}
  virtual ~Scope() {}

  void insert(const std::string& name, Symbol* symbol);
  Symbol* lookup(const std::string& name);

  const std::string& getName() const { return name_; }
  void setName(const std::string& name) { name_ = name; }

  Scope* getParent() { return parent_; }
  void setParent(Scope* parent) { parent_ = parent; }

  bool isOwnedBySymbolTable() { return owned_by_symtable_; }
  void setOwnedBySymbolTable(bool owned) { owned_by_symtable_ = owned; }

 protected:
  // Map from symbol name to symbol info.
  boost::ptr_map<std::string, Symbol> symbol_map_;

  std::string name_;
  Scope* parent_;

  // Whether this scope object is owned by a symbol table (like class, function or
  // named namespace). If so, the symbol table will delete this scope object
  // after exiting this scope.
  bool owned_by_symtable_;
};

}  // namespace flang

#endif

