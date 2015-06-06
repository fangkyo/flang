#ifndef SYMBOL_TABLE_H_
#define SYMBOL_TABLE_H_

#include <list>
#include <memory>
#include <unordered_map>
#include <vector>

#include <boost/ptr_container/ptr_vector.hpp>

#include "symbol_table/scope.h"
#include "symbol_table/symbol_info.h"

namespace flang {

class SymbolTable {
 public:
  SymbolTable();

  /** Push a scope to the symbol table's scope stack.
   *
   *  @param[in] scope The scope to push. Symbol table has a refenence of the scope.
   */
  void pushScope(const std::shared_ptr<Scope>& scope);

  /** Push a scope to the symbol table's scope stack.
   *
   *  @param[in] scope The scope to push. Symbol table takes its ownership.
   */
  void pushScope(Scope* scope);

  /** Pop the top scope of symbol table's scope stack. */
  void popScope();

  /** Insert a symbol to symbol table. Insert to global scope also if global
   *  is set to true. It takes the ownership of passed in <symbol_info>.
   *
   *  @param[in] name The name of the symbol, which is the key to look up.
   *  @param[in] symbol_info The symbol to insert. Symbol table takes its ownership.
   */
  void insert(const std::string& name, SymbolInfo* symbol_info);

  /** Look up the symbol specification for the given symbol name.
   *
   *  @param[in] name The symbol's name.
   *  @return The symbol if found or nullptr if not.
   */
  SymbolInfo* lookup(const std::string& name);


  /** Look up the symbol specification for the given symbol name.
   *
   *  @param[in] qualifers The symbol's qualifier list.
   *  @param[in] name The symbol's name.
   *  @return The symbol if found or nullptr if not.
   */
  SymbolInfo* lookup(const std::vector<std::string*>& qualifiers,
                     const std::string& name);

 private:
  std::list<std::shared_ptr<Scope>> scope_stack_;
};

}  // namespace flang

#endif
