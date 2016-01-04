#include <string>
#include <sstream>
#include <memory>

#include "front_end/flang_scanner.h"
#include "front_end/flang_parser.h"
#include "syntax_tree/ast_visitor.h"
#include "test/test.h"

namespace flang {

class FlangParserTest : public Test {
 protected:
  void SetUp() override {
    filename_ = "test.f";
    scanner_.reset(new FlangScanner(&ss_));
    parser_.reset(new FlangParser(scanner_.get(), &ast_, &filename_));
  }

  std::unique_ptr<FlangScanner> scanner_;
  std::unique_ptr<FlangParser> parser_;
  std::istringstream ss_;
  SyntaxTree ast_;
  std::string filename_;
};

TEST_F(FlangParserTest, testParseProgram) {
  class ProgramVisitor : public ASTVisitor {
   public:
    ProgramVisitor() {
      num_imports = -1;
      import_node = nullptr;
    }
    bool visit(ImportListNode* node) override {
      num_imports = node->getImportList().size();
      EXPECT_EQ(1, num_imports);
      return true;
    }

    bool visit(ImportNode* node) override {
      pkg_name = node->getPackageName()->toString();
      import_node = node;
      EXPECT_EQ("org.flang.Parser", pkg_name);
      EXPECT_EQ("parser", node->getAlias()->toString());
      return true;
    }

    size_t num_imports;
    std::string pkg_name;
    ImportNode* import_node;
  };
  std::string src = "import org.flang.Parser as parser";
  ss_.str(src);
  parser_->parse();
  ASTNode* root = ast_.getRoot();
  ASSERT_NE(nullptr, root);
  ASSERT_EQ(ASTNodeType::PROGRAM_NODE, root->getNodeType());
  ProgramVisitor visitor;
  ast_.accept(&visitor);
}

TEST_F(FlangParserTest, testParseBinaryExpression) {
  std::string src =
      "2 + 4 * (5 + 1) ;";
  ss_.str(src);
  parser_->parse();

  auto* root = ast_.getRoot();
  ASSERT_NE(nullptr, root);
  ASSERT_EQ(ASTNodeType::PROGRAM_NODE, root->getNodeType());
  auto* program = dynamic_cast<ProgramNode*>(root);
  ASSERT_NE(nullptr, program);
  auto* stmt_list = program->getStmtList();
  ASSERT_NE(nullptr, stmt_list);
  ASSERT_EQ(1, stmt_list->getStmtList().size());
  for (auto& stmt : stmt_list->getStmtList()) {
    ASSERT_EQ(ASTNodeType::BINARY_EXP_NODE, stmt.getNodeType());
    const auto* binary_exp = dynamic_cast<const BinaryExpNode*>(&stmt);
    ASSERT_EQ(BinaryExpNode::OP_ADD, binary_exp->getOperator());

    auto* left = binary_exp->getLeftSide();
    ASSERT_NE(nullptr, left);
    ASSERT_EQ(ASTNodeType::INT_VAL_NODE, left->getNodeType());
    ASSERT_EQ(2, dynamic_cast<IntValNode*>(left)->getValue());

    auto* right = binary_exp->getRightSide();
    ASSERT_NE(nullptr, right);
    ASSERT_EQ(ASTNodeType::BINARY_EXP_NODE, right->getNodeType());
    binary_exp = dynamic_cast<BinaryExpNode*>(right);
    ASSERT_NE(nullptr, binary_exp);
    ASSERT_EQ(BinaryExpNode::OP_MUL, binary_exp->getOperator());

    left = binary_exp->getLeftSide();
    ASSERT_NE(nullptr, left);
    ASSERT_EQ(ASTNodeType::INT_VAL_NODE, left->getNodeType());
    ASSERT_EQ(4, dynamic_cast<IntValNode*>(left)->getValue());

    right = binary_exp->getRightSide();
    ASSERT_NE(nullptr, right);
    ASSERT_EQ(ASTNodeType::BINARY_EXP_NODE, right->getNodeType());
    binary_exp = dynamic_cast<BinaryExpNode*>(right);
    ASSERT_EQ(BinaryExpNode::OP_ADD, binary_exp->getOperator());

    left = binary_exp->getLeftSide();
    ASSERT_NE(nullptr, left);
    ASSERT_EQ(ASTNodeType::INT_VAL_NODE, left->getNodeType());
    ASSERT_EQ(5, dynamic_cast<IntValNode*>(left)->getValue());

    right = binary_exp->getRightSide();
    ASSERT_NE(nullptr, right);
    ASSERT_EQ(ASTNodeType::INT_VAL_NODE, right->getNodeType());
    ASSERT_EQ(1, dynamic_cast<IntValNode*>(right)->getValue());
    break;
  }
}

TEST_F(FlangParserTest, testAssignment) {
  std::string src = "a = 1;";
  ss_.str(src);
  parser_->parse();
  class AssignVisitor : public ASTVisitor {
    public:
     bool visit(AssignNode* node) override {
       EXPECT_EQ(AssignNode::OP_ASSIGN, node->getOperator());
       auto* left = node->getLeftSide();
       EXPECT_EQ(ASTNodeType::FIELD_ACCESS_NODE, left->getNodeType()) << left->getNodeTypeName();
       auto* field_access = left->getImpl<FieldAccessNode>();
       EXPECT_EQ("a", field_access->getFieldName()->toString());
       auto* right = node->getRightSide();
       EXPECT_EQ(ASTNodeType::INT_VAL_NODE, right->getNodeType());
       EXPECT_EQ(1, dynamic_cast<IntValNode*>(right)->getValue());
       return true;
     }
  };
  AssignVisitor visitor;
  ast_.accept(&visitor);
}

TEST_F(FlangParserTest, testInstantiate) {
  std::string src = "new A(3);";
  ss_.str(src);
  parser_->parse();
  auto* root = ast_.getRoot();
  ASSERT_NE(nullptr, root);
  ASSERT_EQ(ASTNodeType::PROGRAM_NODE, root->getNodeType());
  auto* program = dynamic_cast<ProgramNode*>(root);
  ASSERT_NE(nullptr, program);
  auto* stmt_list = program->getStmtList();
  ASSERT_NE(nullptr, stmt_list);
  ASSERT_EQ(1, stmt_list->getStmtList().size());
  for (auto& stmt : stmt_list->getStmtList()) {
    ASSERT_EQ(ASTNodeType::NEW_NODE, stmt.getNodeType())
        << stmt.getNodeTypeName();
    const NewNode* new_node = dynamic_cast<const NewNode*>(&stmt);
    ASSERT_NE(nullptr, new_node);
    auto* class_name = new_node->getClassName();
    ASSERT_EQ("A", class_name->toString());
    auto* param_list = new_node->getParamList();
    ASSERT_EQ(1, param_list->getParamList().size());
    for (const auto& param : param_list->getParamList()) {
      auto* int_val = param.getImpl<IntValNode>();
      ASSERT_EQ(3, int_val->getValue());
    }
    break;
  }
}

TEST_F(FlangParserTest, testCall) {
  std::string src = "a.b(1, 5).c(3);";
  ss_.str(src);
  parser_->parse();
  auto* root = ast_.getRoot();
  ASSERT_NE(nullptr, root);
  auto* program = root->getImpl<ProgramNode>();
  auto* stmt_list = program->getStmtList();
  ASSERT_NE(nullptr, stmt_list);
  ASSERT_EQ(1, stmt_list->getStmtList().size());
  for (auto& stmt : stmt_list->getStmtList()) {
    auto* call_node = stmt.getImpl<CallNode>();
    auto* name = call_node->getName();
    ASSERT_EQ("c", name->toString());
    auto* param_list = call_node->getParamList();
    ASSERT_EQ(1, param_list->getParamList().size());
    for (const auto& param : param_list->getParamList()) {
      auto* int_val = param.getImpl<IntValNode>();
      ASSERT_EQ(3, int_val->getValue());
    }
    auto* caller = call_node->getCaller();   
    call_node = caller->getImpl<CallNode>();
    name = call_node->getName();
    ASSERT_EQ("b", name->toString());
    param_list = call_node->getParamList();
    ASSERT_EQ(2, param_list->getParamList().size());
    auto* int_val = param_list->getParamList()[0].getImpl<IntValNode>();
    ASSERT_EQ(1, int_val->getValue());
    int_val = param_list->getParamList()[1].getImpl<IntValNode>();
    ASSERT_EQ(5, int_val->getValue());
    caller = call_node->getCaller();
    auto* field_access = caller->getImpl<FieldAccessNode>();
    ASSERT_EQ("a", field_access->getFieldName()->toString());
  }

}
}  // namespace flang
