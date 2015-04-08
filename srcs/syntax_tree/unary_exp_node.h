#ifndef UNARY_EXP_NODE_H_
#define UNARY_EXP_NODE_H_

#include <memory>

#include "syntax_tree/ast_node.h"
#include "syntax_tree/exp_node.h"

namespace flang {

// Expression node with unary operator
class UnaryExpNode : public ASTNode {
 public:
  enum UnaryOpType {
    OP_INC, // ++
    OP_DEC, // --
    OP_POS, // +
    OP_NEG, // -
    OP_NOT, // !
  };

  UnaryExpNode(UnaryOpType op, ExpNode* exp_node, ASTNode* parent);
  ~UnaryExpNode() override {}

  void accept(ASTVisitor* visitor) override;

  // Accessor of op
  UnaryOpType op() { return op_; }

  // Accessor of exp_node
  void setExpNode(ExpNode* exp_node) { exp_node_.reset(exp_node); }
  ExpNode* expNode() { return exp_node.get(); }

 protected:
  UnaryOpType op_;
  std::unique_ptr<ExpNode> exp_node_;
};

}  // namespace flang

#endif
