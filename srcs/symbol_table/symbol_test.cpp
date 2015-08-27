#include <memory>
#include <gtest/gtest.h>

#include "symbol_table/symbol.h"
#include "symbol_table/scope.h"

namespace flang {

class SymbolTest : public ::testing::Test {
 public:
  void SetUp() override {
    var_.reset(new VariableSymbol);
    func_.reset(new FunctionSymbol);
    class_.reset(new ClassSymbol);
    var_->setName("a");
    func_->setName("b");
    class_->setName("c");
  }
 protected:
  std::unique_ptr<VariableSymbol> var_;
  std::unique_ptr<FunctionSymbol> func_;
  std::unique_ptr<ClassSymbol> class_;
};

class TestSymbolHandler : public SymbolHandler {
 public:
  void handle(ClassSymbol* symbol) override {
    class_name = symbol->getName();
  }
  void handle(FunctionSymbol* symbol) override {
    func_name = symbol->getName();
  }
  void handle(VariableSymbol* symbol) override {
    var_name = symbol->getName();
  }

  std::string var_name;
  std::string func_name;
  std::string class_name;
};

TEST_F(SymbolTest, testSymbolHandler) {
  TestSymbolHandler handler;
  var_->execute(&handler);
  class_->execute(&handler);
  func_->execute(&handler);
  EXPECT_EQ(var_->getName(), handler.var_name);
  EXPECT_EQ(func_->getName(), handler.func_name);
  EXPECT_EQ(class_->getName(), handler.class_name);
}

TEST_F(SymbolTest, testSymbolType) {
  EXPECT_EQ(Symbol::SYMBOL_CLASS, class_->getSymbolType());
  EXPECT_EQ(Symbol::SYMBOL_FUNCTION, func_->getSymbolType());
  EXPECT_EQ(Symbol::SYMBOL_VARIABLE, var_->getSymbolType());
}

TEST_F(SymbolTest, testFunctionSymbol) {
  EXPECT_EQ("b", func_->getName());
  VariableSymbol* p1 = new VariableSymbol();
  p1->setName("p1");
  p1->setDataType(DataTypeFactory::getInt32Type());
  func_->addParameter(p1);
  VariableSymbol* p2 = new VariableSymbol();
  p2->setName("p2");
  p2->setDataType(DataTypeFactory::getStringType());
  func_->addParameter(p2);
  const auto& actual_params = func_->getParameters();
  std::vector<VariableSymbol*> expected_params {p1, p2};
  EXPECT_EQ(expected_params, actual_params);

  func_->setReturnType(DataTypeFactory::getVoidType());
  EXPECT_EQ(DataTypeFactory::getVoidType(), func_->getReturnType());
  EXPECT_EQ(func_->getDataType(), func_->getReturnType());

  auto* scope = func_->getScope();
  ASSERT_NE(nullptr, scope);
  EXPECT_EQ(2, scope->getSize());
  EXPECT_EQ(p1, scope->lookup(p1->getName()));
  EXPECT_EQ(p2, scope->lookup(p2->getName()));
  EXPECT_FALSE(scope->isOwnedBySymbolTable());
}

TEST_F(SymbolTest, testClassSymbol) {
  DataType* data_type = class_->getDataType();
  ASSERT_NE(nullptr, data_type);
  ASSERT_EQ(DataType::DATA_TYPE_CLASS, data_type->getType());
  ClassType* type = dynamic_cast<ClassType*>(data_type);
  ASSERT_NE(nullptr, type);
  EXPECT_EQ(class_.get(), type->getClassSymbol());

  VariableSymbol* v1 = new VariableSymbol();
  v1->setName("v1");
  v1->setDataType(DataTypeFactory::getInt32Type());
  class_->addVariable(v1);

  VariableSymbol* v2 = new VariableSymbol();
  v2->setName("v2");
  v2->setDataType(DataTypeFactory::getStringType());
  class_->addVariable(v2);
  const auto& actual_vars = class_->getVariables();
  std::vector<VariableSymbol*> expected_vars {v1, v2};
  EXPECT_EQ(expected_vars, actual_vars);

  FunctionSymbol* f = new FunctionSymbol();
  f->setName("f");
  f->setReturnType(DataTypeFactory::getCharType());
  class_->addFunction(f);
  const auto& actual_funcs = class_->getFunctions();
  std::vector<FunctionSymbol*> expected_funcs {f};
  EXPECT_EQ(expected_funcs, actual_funcs);

  Scope* scope = class_->getScope();
  ASSERT_NE(nullptr, scope);
  EXPECT_FALSE(scope->isOwnedBySymbolTable());
  EXPECT_EQ(class_->getName(), scope->getName());

  EXPECT_EQ(3, scope->getSize());
  EXPECT_EQ(v1, scope->lookup(v1->getName()));
  EXPECT_EQ(v2, scope->lookup(v2->getName()));
  EXPECT_EQ(f, scope->lookup(f->getName()));
}

}  // namespace flang
