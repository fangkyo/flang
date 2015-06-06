#include <memory>

#include <gtest/gtest.h>

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
  VariableInfo* var_info = new VariableInfo();
  var_info->setDataType(new Int32Type());
  var_info->setName("my_var");
  symbol_table_.insert("abc", var_info);
  SymbolInfo* symbol_info = symbol_table_.lookup("abc");
  ASSERT_EQ(var_info, symbol_info);
}

TEST_F(SymbolTableTest, TestLookUp) {
  VariableInfo* bar = new VariableInfo();
  bar->setName("bar");

  ClassInfo* class_info = new ClassInfo();
  std::shared_ptr<Scope> class_scope(new Scope());
  class_info->setScope(class_scope);
  class_info->setName("MyClass");
  VariableInfo* foo = new VariableInfo();
  foo->setName("foo");
  foo->setDataType(new Int32Type());
  class_info->addMemberVar(foo);

  FunctionInfo* func_info = new FunctionInfo();
  func_info->setName("getName");
  func_info->setReturnType(new Int64Type());
  class_info->addMemberFunc(func_info);

  DataType* bar_type = new ClassType(class_info);
  bar->setDataType(bar_type);

  symbol_table_.insert(bar->getName(), bar);
  ASSERT_EQ(bar, symbol_table_.lookup("bar"));

  std::vector<std::string*> qualifiers;
  std::string class_name = bar->getName();
  qualifiers.push_back(&class_name);
  ASSERT_EQ(foo, symbol_table_.lookup(qualifiers, "foo"));
}

}  // namespace flang

