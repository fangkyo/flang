#include <gtest/gtest.h>

#include "symbol_table/symbol.h"
#include "symbol_table/scope.h"

namespace flang {

TEST(ScopeTest, testInsertLookUp) {
  auto* a = new VariableSymbol();
  a->setName("a");
  a->setDataType(DataTypeFactory::getBoolType());
  Scope scope;
  scope.insert(a->getName(), a);
  Symbol* symbol = scope.lookup(a->getName());
  EXPECT_EQ(a, symbol);
  auto* b = new FunctionSymbol();
  b->setName("b");
  b->setReturnType(DataTypeFactory::getInt32Type());
  scope.insert(b->getName(), b);
  EXPECT_EQ(b, scope.lookup(b->getName()));
}

}  // namespace flang
