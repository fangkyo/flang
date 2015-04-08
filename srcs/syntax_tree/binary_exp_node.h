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

  BinaryExpNode(BinaryOpType op, ExpNode* left_exp,
                ExpNode* right_exp, ASTNode* parent);
  ~BinaryExpNode() override {};

  void accept(ASTVisitor& visitor);

  BinaryOpType op() { return op_; }
  ExpNode* leftExp() { return left_exp_; }
  void setLeftExp(ExpNode* exp_node) { left_exp_ = exp_node; }
  ExpNode* rightExp() { return right_exp_; }
  void setRightExp(ExpNode* exp_node) { right_exp_ = exp_node; }

 protected:
  BinaryOpType op_;
  std::unique_ptr<ExpNode> left_exp_;
  std::unique_ptr<ExpNode> right_exp_;
};

}  // namespace flang

#endif
