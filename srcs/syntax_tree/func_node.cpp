#include "syntax_tree/func_node.h"

namespace flang {

void FuncNode::accept(ASTVisitor* visitor) {
  visitor->traverse(this);
}

ReturnNode::ReturnNode(ExpNode* exp_node)
  : StmtNode(ASTNode::RETURN_NODE), expression_(exp_node) {
  if (expression_) {
    expression_->setParent(this);
  }
}

void ReturnNode::accept(ASTVisitor* visitor) {
  visitor->visit(this);
  if (expression_) {
    expression_->accept(visitor);
  }
  visitor->endVisit(this);
}

CallNode::CallNode() : ExpNode(ASTNode::CALL_NODE) {
}

void CallNode::accept(ASTVisitor* visitor) {
  visitor->visit(this);
  for (auto& param : parameters_) {
    param.accept(visitor);
  }
  visitor->endVisit(this);
}

}  // namespace flang
