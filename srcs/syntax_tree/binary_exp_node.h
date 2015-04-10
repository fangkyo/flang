#ifndef BINARY_EXP_NODE_H_
#define BINARY_EXP_NODE_H_

#include <memory>

#include "syntax_tree/exp_node.h"

namespace flang {

// Expression node with binary operator
class BinaryExpNode : public ExpNode {
 public:
  enum BinaryOpType {
    OP_ADD, // +
    OP_SUB, // -
    OP_MUL, // *
    OP_DIV, // /
    OP_EQ,  // ==
    OP_NE,  // !=
    OP_GT,  // >
    OP_GE,  // >=
    OP_LT,  // <
    OP_LE,  // <=
    OP_AND, // &&
    OP_OR,  // ||
  };

  BinaryExpNode(BinaryOpType op, ExpNode* left_exp, ExpNode* right_exp);
  ~BinaryExpNode() override {};

  void accept(ASTVisitor* visitor) override;

  BinaryOpType op() { return op_; }
  ExpNode* leftExp() { return left_exp_.get(); }
  void setLeftExp(ExpNode* exp_node) { left_exp_.reset(exp_node); }
  ExpNode* rightExp() { return right_exp_.get(); }
  void setRightExp(ExpNode* exp_node) { right_exp_.reset(exp_node); }

 protected:
  BinaryOpType op_;
  std::unique_ptr<ExpNode> left_exp_;
  std::unique_ptr<ExpNode> right_exp_;
};

/* class AddNode : public OpNode { */

 // public:
  // AddNode(ExpNode* left, ExpNode* right) : OpNode(OP_ADD, left, right) {}

  // void accept(Visitor& visitor);
// };

// class SubNode : public OpNode {
 // public:
  // SubNode(ExpNode* left, ExpNode* right) : OpNode(OP_SUB, left, right) {}

  // void accept(Visitor& visitor);
// };

// class MulNode : public OpNode {
 // public:
  // MulNode(ExpNode* left, ExpNode* right) : OpNode(OP_MUL, left, right) {}

  // void accept(Visitor& visitor);
// };

// class DivNode : public OpNode {
 // public:
  // DivNode(ExpNode* left, ExpNode* right) : OpNode(OP_DIV, left, right) {}

  // void accept(Visitor& visitor);
// };

// class AndNode : public OpNode {
 // public:
  // AndNode(ExpNode* left, ExpNode* right) : OpNode(OP_AND, left, right) {}

  // void accept(Visitor& visitor);
// };

// class LtNode : public OpNode {
 // public:
  // LtNode(ExpNode* left, ExpNode* right) : OpNode(OP_LT, left, right) {}
// };

// class EqNode : public OpNode {
 // public:
  // EqNode(ExpNode* left, ExpNode* right) : OpNode(OP_EQ, left, right) {}
// };

}  // namespace flang

#endif
