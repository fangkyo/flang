#include "syntax_tree/binary_exp_node.h"

namespace flang {

BinaryExpNode::BinaryExpNode(
    BinaryOpType op, ExpNode* left_exp, ExpNode* right_exp) :
    ExpNode(ASTNode::BINARY_EXP_NODE),
    operator_(op), left_side_(left_exp), right_side_(right_exp) {
}

void BinaryExpNode::accept(ASTVisitor* visitor) {
  if (visitor->beforeVisit(this)) {
    left_side_->accept(visitor);
    right_side_->accept(visitor);
    if (visitor->visit(this)) {
      visitor->afterVisit(this);
    }
  }
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
