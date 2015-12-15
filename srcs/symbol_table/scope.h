#ifndef SYMBOL_TABLE_SCOPE_H_
#define SYMBOL_TABLE_SCOPE_H_

#include <cstdint>
#include <set>
#include <string>
#include <unordered_map>

namespace flang {

class Symbol;

/**
 * This class means an area which contains symbols.
 * The Scope class doesn't hava the ownership of symbols.
 */
class Scope {
 public:
  Scope();
  virtual ~Scope() {}

  /**
   * @brief Insert a symbol to scope.
   *
   * Scope doesn't take the ownship of this symbol.
   *
   * @param [in] name The name of the symbol.
   * @param [in] symbol The symbol to be inserted.
   */
  void insert(const std::string& name, Symbol* symbol);

  /**
   * @brief Look up symbol in the scope and its ancestors.
   *
   * @param [in] name The name of symbol.
   * @param [in, out] exclusive_scopes The exclusive scopes in the look up.
   * @return The found symbol, return nullptr if not found.
   */
  Symbol* lookup(
      const std::string& name, std::set<Scope*>* exclusive_scopes = nullptr);

  size_t getSize() const { return symbol_map_.size(); }

  const std::string& getName() const { return name_; }
  void setName(const std::string& name) { name_ = name; }

  bool isOwnedBySymbolTable() const { return owned_by_symtable_; }
  void setOwnedBySymbolTable(bool owned) { owned_by_symtable_ = owned; }

  /**
   * @brief Get the parent scope of this scope.
   *
   * A scope has parent only if it's a class scope. And its parent must be the
   * scope of class' super class.
   *
   * @return The parent scope.
   */
  Scope* getParent() const { return parent_; }
  void setParent(Scope* parent) { parent_ = parent; }

 protected:
  // Map from symbol name to symbol info.
  std::unordered_map<std::string, Symbol*>  symbol_map_;

  std::string name_;

  // Whether this scope object is owned by a symbol table (like class, function or
  // named namespace). If so, the symbol table will delete this scope object
  // after exiting this scope.
  bool owned_by_symtable_;
  Scope* parent_;

};

}  // namespace flang

#endif

