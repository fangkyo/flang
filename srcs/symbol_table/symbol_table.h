#ifndef SYMBOL_TABLE_H_
#define SYMBOL_TABLE_H_

#include <list>
#include <memory>
#include <unordered_map>
#include <vector>

#include <log4cxx/logger.h>

namespace flang {

class Scope;
class Symbol;

class SymbolTable {
 public:
  SymbolTable();
  ~SymbolTable();

  /**
   * @brief Enter an anonymous scope.
   */
  void enter();

  /**
   * @brief Enter a scope and push it to the symbol table's scope stack.
   * @param[in] scope The scope to push. Symbol table takes its ownership.
   */
  void enter(Scope* scope);

  /**
   * @brief Exit a scope and pop it from symbol table's scope stack.
   */
  void exit();

  /**
   * @brief Insert a symbol to symbol table.
   *
   * The symbol table also takes the ownership of passed in <symbol>.
   *
   * @param[in] name The name of the symbol, which also is the key to look up.
   * @param[in] symbol The symbol to be inserted.
   */
  void insert(const std::string& name, Symbol* symbol);

  /**
   * @brief Look up the symbol specification for the given symbol name.
   *
   * @param[in] name The symbol's name.
   * @param[in] global Whether search the symbol from global scope.
   * @return The symbol if found or nullptr if not.
   */
  Symbol* lookup(const std::string& name, bool global = false);

 private:
  std::vector<Scope*> scope_stack_;

  // Namespace of the current scope
  std::vector<std::string> namespace_;
  static log4cxx::LoggerPtr logger_;
};

/**
 * @brief SymbolTableLock lets symbole table enter a scope when constructed and
 * exit it when destroyed.
 */
class SymbolTableLock {
 public:
  SymbolTableLock(SymbolTable* symbol_table, Scope* scope = nullptr);
  ~SymbolTableLock();
 private:
  SymbolTable* symbol_table_;
};

}  // namespace flang

#endif
