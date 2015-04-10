#include "syntax_tree/assign_node.h"

namespace flang {

AssignNode::AssignNode(VarNode* var_node, ExpNode* exp_node) :
      ExpNode(ASTNode::ASSIGN_EXP_NODE),
      var_node_(var_node),
      exp_node_(exp_node) {
}

void AssignNode::accept(ASTVisitor* visitor) {
  var_node_->accept(visitor);
  exp_node_->accept(visitor);
  visitor->doAssignNode(this);
}

}  // namespace flang
