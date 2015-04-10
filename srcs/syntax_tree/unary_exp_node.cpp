#include "syntax_tree/unary_exp_node.h"

namespace flang {

UnaryExpNode::UnaryExpNode(UnaryOpType op, ExpNode* exp_node) :
    ASTNode(ASTNode::UNARY_EXP_NODE),
    op_(op), exp_node_(exp_node) {
}

void UnaryExpNode::accept(ASTVisitor* visitor) {
  visitor->doUnaryExpNode(this);
}

}  // namespace flang
