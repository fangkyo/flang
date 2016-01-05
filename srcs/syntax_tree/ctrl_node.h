#ifndef CTRL_NODE_H
#define CTRL_NODE_H

#include <memory>

#include "base/check.h"
#include "syntax_tree/stmt_node.h"
#include "syntax_tree/exp_node.h"

namespace flang {

class IfNode : public StmtNode {
 INHERIT_AST_NODE(IfNode, StmtNode, IF_NODE)
 public:
  IfNode(ExpNode* test_node, ASTNode* if_node, ASTNode* else_node);
  IfNode(ExpNode* test_node, ASTNode* if_node);
  ~IfNode() override {}

  void setTestPart(ExpNode* test_node) {
    CHECK(test_node);
    test_part_.reset(test_node);
    test_part_->setParent(this);
  }
  ExpNode* getTestPart() { return test_part_.get(); }

  void setIfPart(ASTNode* if_node) {
    CHECK(if_node);
    if_part_.reset(if_node);
    if_part_->setParent(this);
  }
  ASTNode* getIfPart() { return if_part_.get(); }

  void setElsePart(ASTNode* else_node) {
    CHECK(else_node);
    else_part_.reset(else_node);
    else_part_->setParent(this);
  }
  ASTNode* getElsePart() { return else_part_.get(); }

  bool getChildNodes(ASTNodeList* child_nodes) override;
 private:
  std::unique_ptr<ExpNode> test_part_;
  std::unique_ptr<ASTNode> if_part_;
  std::unique_ptr<ASTNode> else_part_;
};

class WhileNode : public StmtNode {
 INHERIT_AST_NODE(WhileNode, StmtNode, WHILE_NODE)
 public:
  WhileNode(ExpNode* test_node, StmtNode* body_node);
  ~WhileNode() override {}

  void setTestNode(ExpNode* test_node) {
    CHECK(test_node);
    test_node_.reset(test_node);
    test_node_->setParent(this);
  }
  ExpNode* getTestNode() { return test_node_.get(); }

  void setBodyNode(StmtNode* body_node) {
    CHECK(body_node);
    body_node_.reset(body_node);
    body_node_->setParent(this);
  }
  StmtNode* getBodyNode() { return body_node_.get(); }

  bool getChildNodes(ASTNodeList* child_nodes) override;
 private:
  std::unique_ptr<ExpNode> test_node_;
  std::unique_ptr<StmtNode> body_node_;
};

class BreakNode : public StmtNode {
 INHERIT_AST_NODE(BreakNode, StmtNode, BREAK_NODE)
 public:
  BreakNode() {}
  ~BreakNode() override {}
};

class ContinueNode : public StmtNode {
 INHERIT_AST_NODE(ContinueNode, StmtNode, CONTINUE_NODE)
 public:
  ContinueNode() {}
  ~ContinueNode() override {}
};

}  // namespace flang

#endif
