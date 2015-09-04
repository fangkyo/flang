#ifndef CTRL_NODE_H
#define CTRL_NODE_H

#include <memory>

#include "syntax_tree/stmt_node.h"
#include "syntax_tree/exp_node.h"

namespace flang {

class IfNode : public StmtNode {
 public:
  IfNode(ExpNode* test_node, ASTNode* if_node, ASTNode* else_node);
  ~IfNode() override {}

  void setTestNode(ExpNode* test_node) {
    test_node_.reset(test_node);
    test_node_->setParent(this);
  }
  ExpNode* getTestNode() { return test_node_.get(); }

  void setIfNode(ASTNode* if_node) {
    if_node_.reset(if_node);
    if_node_->setParent(this);
  }
  ASTNode* getIfNode() { return if_node_.get(); }

  void setElseNode(ASTNode* else_node) {
    else_node_.reset(else_node);
    else_node_->setParent(this);
  }
  ASTNode* getElseNode() { return else_node_.get(); }

  void accept(ASTVisitor* visitor) override;

 private:
  std::unique_ptr<ExpNode> test_node_;
  std::unique_ptr<ASTNode> if_node_;
  std::unique_ptr<ASTNode> else_node_;
};

class WhileNode : public StmtNode {
 public:
  WhileNode(ExpNode* test_node, ASTNode* body_node);
  ~WhileNode() override {}

  void setTestNode(ExpNode* test_node) {
    test_node_.reset(test_node);
    test_node_->setParent(this);
  }
  ExpNode* getTestNode() { return test_node_.get(); }

  void setBodyNode(ASTNode* body_node) {
    body_node_.reset(body_node);
    body_node_->setParent(this);
  }
  ASTNode* getBodyNode() { return body_node_.get(); }

  void accept(ASTVisitor* visitor) override;

 private:
  std::unique_ptr<ExpNode> test_node_;
  std::unique_ptr<ASTNode> body_node_;
};

class BreakNode : public StmtNode {
 public:
  BreakNode();
  ~BreakNode() override {}

  void accept(ASTVisitor* visitor) override;
};

class ContinueNode : public StmtNode {
 public:
  ContinueNode();
  ~ContinueNode() override {}

  void accept(ASTVisitor* visitor) override;
};

}  // namespace flang

#endif
