#include "syntax_tree/unary_exp_node.h"

namespace flang {

UnaryExpNode::UnaryExpNode(UnaryOpType op, ExpNode* operand) :
    operator_(op), operand_(operand) {
  operand_->setParent(this);
}

bool UnaryExpNode::getChildNodes(ASTNodeList* child_nodes) {
  child_nodes->push_back(operand_.get());
  return true;
}

}  // namespace flang
