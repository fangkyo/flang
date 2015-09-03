#include "syntax_tree/func_node.h"

namespace flang {

void FuncNode::accept(ASTVisitor* visitor) {
  visitor->visit(this);
  for (auto& param : parameters_) {
    param.accept(visitor);
  }
  return_type_->accept(visitor);
  visitor->endVisit(this);
}

ReturnNode::ReturnNode(ExpNode* exp_node)
    : StmtNode(ASTNode::RETURN_NODE), expression_(exp_node) {}

void ReturnNode::accept(ASTVisitor* visitor) {
  visitor->visit(this);
  if (expression_) {
    expression_->accept(visitor);
  }
  visitor->endVisit(this);
}

CallNode::CallNode(const std::string& name) :
  ExpNode(ASTNode::RETURN_NODE), name_(name){
}

void CallNode::accept(ASTVisitor* visitor) {
  visitor->visit(this);
  for (auto& param : parameters_) {
    param.accept(visitor);
  }
  visitor->endVisit(this);
}

}  // namespace flang
