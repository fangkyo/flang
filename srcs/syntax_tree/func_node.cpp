#include "syntax_tree/func_node.h"

namespace flang {

void FuncNode::accept(ASTVisitor* visitor) {
  visitor->start(this);
  for (auto& param : parameters_) {
    param.accept(visitor);
  }
  return_type_->accept(visitor);
  visitor->finish(this);
}

ReturnNode::ReturnNode(ExpNode* exp_node)
    : StmtNode(ASTNode::RETURN_NODE), expression_(exp_node) {}

void ReturnNode::accept(ASTVisitor* visitor) {
  visitor->start(this);
  if (expression_) {
    expression_->accept(visitor);
  }
  visitor->finish(this);
}

CallNode::CallNode(const std::string& name) :
  ExpNode(ASTNode::RETURN_NODE), name_(name){
}

void CallNode::accept(ASTVisitor* visitor) {
  visitor->start(this);
  for (auto& param : parameters_) {
    param.accept(visitor);
  }
  visitor->finish(this);
}

}  // namespace flang
