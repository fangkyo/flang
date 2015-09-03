#include <gtest/gtest.h>

#include "symbol_table/symbol.h"
#include "symbol_table/scope.h"

namespace flang {

TEST(ScopeTest, testInsertLookUp) {
  Scope scope;
  VariableSymbol a("a");
  a.setDataType(DataTypeFactory::getBoolType());
  scope.insert(a.getName(), &a);
  Symbol* symbol = scope.lookup(a.getName());
  EXPECT_EQ(&a, symbol);
  FunctionSymbol b("b");
  b.setReturnType(DataTypeFactory::getInt32Type());
  scope.insert(b.getName(), &b);
  EXPECT_EQ(&b, scope.lookup(b.getName()));

  VariableSymbol d("d");
  Scope parent;
  parent.insert(d.getName(), &d);
  scope.setParent(&parent);
  EXPECT_EQ(&d, scope.lookup(d.getName()));

  std::set<Scope*> exclusive_scopes {&parent};
  EXPECT_EQ(nullptr, scope.lookup(d.getName(), &exclusive_scopes));
  EXPECT_EQ(2, exclusive_scopes.size());
  exclusive_scopes.clear();
  exclusive_scopes.insert(&scope);
  EXPECT_EQ(nullptr, scope.lookup(a.getName(), &exclusive_scopes));
  EXPECT_EQ(1, exclusive_scopes.size());
  EXPECT_EQ(nullptr, scope.lookup("not existing"));
}

}  // namespace flang
