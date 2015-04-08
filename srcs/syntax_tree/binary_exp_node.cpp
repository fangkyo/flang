#include "syntax_tree/binary_exp_node.h"

namespace flang {

BinaryExpNode::BinaryExpNode(
    BinaryOpType op, ExpNode* left_exp,
    ExpNode* right_exp, ASTNode* parent) :
    ExpNode(ASTNodeType::BINARY_EXP_NODE, parent),   
    op_(op), m_leftOpnd(left_exp), m_rightOpnd(right_exp) {
}

void BinaryExpNode::accept(ASTVisitor* visitor) {
  visitor->doBinaryExpNode(this);
}

}  // namespace flang
