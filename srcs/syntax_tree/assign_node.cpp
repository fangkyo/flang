#include "syntax_tree/assign_node.h"

namespace flang {

AssignNode::AssignNode(
    ExpNode* left_side, ExpNode* right_side, AssignOpType op) :
    left_side_(left_side),
    right_side_(right_side),
    operator_(op) {
  left_side_->setParent(this);
  right_side_->setParent(this);
}

bool AssignNode::getChildNodes(ASTNodeList* child_nodes) {
  child_nodes->push_back(left_side_.get());
  child_nodes->push_back(right_side_.get());
  return true;
}

}  // namespace flang
