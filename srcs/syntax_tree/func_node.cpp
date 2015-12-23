#include "syntax_tree/func_node.h"

namespace flang {

void ParamListNode::addParameter(ExpNode* param) {
  param->setParent(this);
  param_list_.push_back(param);
}


ReturnNode::ReturnNode(ExpNode* exp_node) :
    expression_(exp_node) {
  if (expression_) {
    expression_->setParent(this);
  }
}

bool CallNode::getChildNodes(ASTNodeList* child_nodes) {
  child_nodes->push_back(caller_.get());
  child_nodes->push_back(param_list_.get());
  return true;
}

}  // namespace flang
