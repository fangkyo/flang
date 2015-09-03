#include <memory>

#include <gtest/gtest.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/logger.h>
#include <log4cxx/consoleappender.h>
#include <log4cxx/patternlayout.h>

#include "symbol_table/symbol.h"
#include "symbol_table/symbol_table.h"
#include "test/test.h"

namespace flang {

class SymbolTableTest : public Test {
 protected:
  SymbolTable symbol_table_;
};

TEST_F(SymbolTableTest, testInsert) {
  VariableSymbol* var = new VariableSymbol("my_var");
  var->setDataType(DataTypeFactory::getInt32Type());
  symbol_table_.insert("abc", var);
  Symbol* symbol = symbol_table_.lookup("abc");
  ASSERT_EQ(var, symbol);
}

TEST_F(SymbolTableTest, testEnterExit) {
  VariableSymbol var("var");
  symbol_table_.enter();
  symbol_table_.insert(var.getName(), &var);
  EXPECT_EQ(&var, symbol_table_.lookup(var.getName()));
  symbol_table_.exit();
  EXPECT_EQ(nullptr, symbol_table_.lookup(var.getName()));
  VariableSymbol foo("foo");
  foo.setDataType(DataTypeFactory::getInt32Type());
  Scope local_scope;
  local_scope.setOwnedBySymbolTable(false);
  {
    SymbolTableLock lock(&symbol_table_, &local_scope);
    symbol_table_.insert(foo.getName(), &foo);
    EXPECT_EQ(&foo, symbol_table_.lookup(foo.getName()));
  }
  EXPECT_EQ(nullptr, symbol_table_.lookup(foo.getName()));
  EXPECT_EQ(&foo, local_scope.lookup(foo.getName()));
}

TEST_F(SymbolTableTest, testLookUp) {
  ClassSymbol clazz("MyClass");
  VariableSymbol foo("foo");
  foo.setDataType(DataTypeFactory::getInt32Type());
  clazz.addVariable(&foo);

  FunctionSymbol func("getName");
  func.setReturnType(DataTypeFactory::getInt64Type());
  clazz.addFunction(&func);

  VariableSymbol bar("bar");
  bar.setDataType(DataTypeFactory::getClassType(&clazz));

  symbol_table_.insert(bar.getName(), &bar);
  EXPECT_EQ(&bar, symbol_table_.lookup(bar.getName()));
  EXPECT_EQ(nullptr, symbol_table_.lookup(foo.getName()));

  EXPECT_EQ(&foo, clazz.getScope()->lookup(foo.getName()));
  ClassSymbol child_class("Child");
  child_class.setSuperClass(&clazz);
  EXPECT_EQ(child_class.getScope()->getParent(), clazz.getScope());
  EXPECT_EQ(&foo, child_class.getScope()->lookup(foo.getName()));
  {
    SymbolTableLock lock(&symbol_table_, child_class.getScope());
    EXPECT_EQ(&foo, symbol_table_.lookup(foo.getName()));
  }
}

}  // namespace flang

