#include "syntax_tree/ctrl_node.h"

namespace flang {

IfNode::IfNode(ExpNode* test_node, ASTNode* if_node, ASTNode* else_node) :
    StmtNode(ASTNode::IF_NODE),
    test_node_(test_node), if_node_(if_node), else_node_(else_node) {
}

void IfNode::accept(ASTVisitor* visitor) {
  visitor->visit(this);
  test_node_->accept(visitor);
  if_node_->accept(visitor);
  else_node_->accept(visitor);
  visitor->endVisit(this);
}


WhileNode::WhileNode(ExpNode* test_node, ASTNode* body_node) :
    StmtNode(ASTNode::WHILE_NODE),
    test_node_(test_node), body_node_(body_node) {
}

void WhileNode::accept(ASTVisitor* visitor) {
  visitor->visit(this);
  test_node_->accept(visitor);
  body_node_->accept(visitor);
  visitor->endVisit(this);
}

BreakNode::BreakNode() : StmtNode(ASTNode::BREAK_NODE) {}

void BreakNode::accept(ASTVisitor* visitor) {
  visitor->visit(this);
  visitor->endVisit(this);
}

ContinueNode::ContinueNode() : StmtNode(ASTNode::CONTINUE_NODE) {}

void ContinueNode::accept(ASTVisitor* visitor) {
  visitor->visit(this);
  visitor->endVisit(this);
}

}  // namespace flang
