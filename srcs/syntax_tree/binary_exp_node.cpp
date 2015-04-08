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

/* void AddNode::accept(Visitor& visitor) { */

  // assert(m_leftOpnd);
  // assert(m_rightOpnd);

  // m_leftOpnd->accept(visitor);
  // m_rightOpnd->accept(visitor);

  // visitor.doAddNode(this);
// }

// void SubNode::accept(Visitor& visitor) {

  // assert(m_leftOpnd);
  // assert(m_rightOpnd);

  // m_leftOpnd->accept(visitor);
  // m_rightOpnd->accept(visitor);

  // visitor.doSubNode(this);
// }

// void MulNode::accept(Visitor& visitor) {

  // assert(m_leftOpnd);
  // assert(m_rightOpnd);

  // m_leftOpnd->accept(visitor);
  // m_rightOpnd->accept(visitor);

  // visitor.doMulNode(this);
// }
// void DivNode::accept(Visitor& visitor) {

  // assert(m_leftOpnd);
  // assert(m_rightOpnd);

  // m_leftOpnd->accept(visitor);
  // m_rightOpnd->accept(visitor);

  // visitor.doDivNode(this);
// }

// void AndNode::accept(Visitor& visitor) {

  // assert(m_leftOpnd);
  // assert(m_rightOpnd);

  // m_leftOpnd->accept(visitor);
  // m_rightOpnd->accept(visitor);

  // visitor.doAndNode(this);
/* } */



}  // namespace flang