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
  VariableInfo* var_info = new VariableInfo();
  var_info->setDataType(new Int32Type());
  var_info->setName("my_var");
  symbol_table_.insert("abc", var_info);
  symbol_table_.pushScope(new Scope());
  FunctionInfo* func_info = new FunctionInfo();
  func_info->setName("abc");
  symbol_table_.insert("abc", func_info);

  SymbolInfo* symbol_info = symbol_table_.lookup("abc");
  ASSERT_EQ(func_info, symbol_info);
}

}  // namespace flang

