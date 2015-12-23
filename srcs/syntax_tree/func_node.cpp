#include "syntax_tree/func_node.h"

namespace flang {

void ParamListNode::addParameter(VarDeclNode* param) {
  param->setParent(this);
  param_list_.push_back(param);
}

ReturnNode::ReturnNode(ExpNode* exp_node)
  : StmtNode(ASTNode::RETURN_NODE), expression_(exp_node) {
  if (expression_) {
    expression_->setParent(this);
  }
}

CallNode::CallNode() : ExpNode(ASTNode::CALL_NODE) {
}

}  // namespace flang
