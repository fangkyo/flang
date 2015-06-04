#ifndef SCOPE_H_
#define SCOPE_H_

#include <cstdint>
#include <string>
#include <list>
#include <unordered_map>
#include <vector>

#include <boost/ptr_container/ptr_map.hpp>

#include "symbol_table/symbol_info.h"

namespace flang {

class Scope {
 public:
  virtual ~Scope() {}

  virtual void insert(const std::string& name, SymbolInfo* symbol_info);
  virtual SymbolInfo* lookup(const std::string& name);

  const std::string& getName() const { return name_; }
  void setName(const std::string& name) { name_ = name; }

  Scope* getParent() { return parent_; }
  void setParent(Scope* parent) { parent_ = parent; }

 protected:
  // Map from symbol name to symbol info.
  boost::ptr_map<std::string, SymbolInfo> symbol_map_;

  std::string name_;
  Scope* parent_;
};

}  // namespace flang

#endif

