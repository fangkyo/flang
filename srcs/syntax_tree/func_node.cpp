#include "ast_visitor/ast_visitor.h"
#include "syntax_tree/func_node.h"

namespace flang {

void FuncNode::accept(ASTVisitor* visitor) {
  for (auto& param : param_list_) {
    param.accept(visitor);
  }
  visitor->doFuncNode(this);
}

ReturnNode::ReturnNode(ExpNode* exp_returned)
    : StmtNode(ASTNode::RETURN_NODE), exp_returned_(exp_returned) {}

void ReturnNode::accept(ASTVisitor* visitor) {
  if (exp_returned_) {
    exp_returned_->accept(visitor);
  }
  visitor->doReturnNode(this);
}

CallNode::CallNode(const std::string& name) :
  ExpNode(ASTNode::RETURN_NODE), name_(name){
}

void CallNode::accept(ASTVisitor* visitor) {
  for (ExpNode& param : param_list_) {
    param.accept(visitor);
  }
  visitor->doCallNode(this);
}

}  // namespace flang
