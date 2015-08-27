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
   * @return The symbol if found or nullptr if not.
   */
  Symbol* lookup(const std::string& name);

  /**
   * @brief Look up the symbol specification for the given symbol name.
   *
   * @param[in] qualifers The symbol's qualifier list.
   * @param[in] name The symbol's name.
   * @return The symbol if found or nullptr if not.
   */
  Symbol* lookup(const std::vector<std::string*>& qualifiers,
                 const std::string& name);

  const std::vector<std::string>& getNamespace() { return namespace_; }

 private:
  std::list<Scope*> scope_stack_;
  // Namespace of the current scope
  std::vector<std::string> namespace_;
  static log4cxx::LoggerPtr logger_;
};

}  // namespace flang

#endif
