#include "syntax_tree/assign_node.h"

namespace flang {

AssignNode::AssignNode(ExpNode* left_side, ExpNode* right_side) :
      ExpNode(ASTNode::ASSIGN_EXP_NODE),
      left_side_(left_side),
      right_side_(right_side) {
}

void AssignNode::accept(ASTVisitor* visitor) {
  visitor->start(this);
  left_side_->accept(visitor);
  right_side_->accept(visitor);
  visitor->finish(this);
}

}  // namespace flang
