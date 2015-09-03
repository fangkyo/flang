#include "syntax_tree/unary_exp_node.h"

namespace flang {

UnaryExpNode::UnaryExpNode(UnaryOpType op, ExpNode* operand) :
    ExpNode(ASTNode::UNARY_EXP_NODE),
    operator_(op), operand_(operand) {
}

void UnaryExpNode::accept(ASTVisitor* visitor) {
  visitor->visit(this);
  operand_->accept(visitor);
  visitor->endVisit(this);
}

}  // namespace flang
