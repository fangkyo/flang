#include "syntax_tree/unary_exp_node.h"

namespace flang {

UnaryExpNode::UnaryExpNode(UnaryOpType op, ASTNode* parent) :
    ASTNode(ASTNode::UNARY_EXP_NODE, parent),
    op_(op) { 
}

void UnaryExpNode::accept(ASTVisitor* visitor) {
  visitor->doUnaryExpNode(this);
}

}  // namespace flang
