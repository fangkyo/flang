#include <memory>

#include <gtest/gtest.h>

#include "symbol_table/symbol.h"
#include "symbol_table/symbol_table.h"

namespace flang {

class SymbolTableTest : public ::testing::Test {
 public:
  void SetUp() override {
  }

 protected:
  SymbolTable symbol_table_;
};

TEST_F(SymbolTableTest, TestInsert) {
  VariableSymbol* var = new VariableSymbol();
  var->setDataType(DataTypeFactory::getInt32Type());
  var->setName("my_var");
  symbol_table_.insert("abc", var);
  Symbol* symbol = symbol_table_.lookup("abc");
  ASSERT_EQ(var, symbol);
}

TEST_F(SymbolTableTest, TestLookUp) {
  VariableSymbol* bar = new VariableSymbol();
  bar->setName("bar");

  ClassSymbol* class_symbol = new ClassSymbol();
  class_symbol->setName("MyClass");
  VariableSymbol* foo = new VariableSymbol();
  foo->setName("foo");
  foo->setDataType(DataTypeFactory::getInt32Type());
  class_symbol->addVariable(foo);

  FunctionSymbol* func = new FunctionSymbol();
  func->setName("getName");
  func->setReturnType(DataTypeFactory::getInt64Type());
  class_symbol->addFunction(func);

  DataType* bar_type = new ClassType(class_symbol);
  bar->setDataType(bar_type);

  symbol_table_.insert(bar->getName(), bar);
  ASSERT_EQ(bar, symbol_table_.lookup("bar"));

  std::vector<std::string*> qualifiers;
  std::string class_name = bar->getName();
  qualifiers.push_back(&class_name);
  ASSERT_EQ(foo, symbol_table_.lookup(qualifiers, "foo"));
}

}  // namespace flang

