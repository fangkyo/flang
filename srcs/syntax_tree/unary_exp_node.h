#ifndef UNARY_EXP_NODE_H_
#define UNARY_EXP_NODE_H_

#include "syntax_tree/ast_node.h"

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

  UnaryExpNode(UnaryOpType op, ASTNode* parent);
  ~UnaryExpNode() override {}

  void accept(ASTVisitor* visitor);

  // Getter of op
  UnaryOpType op() { return op_; }

 protected:
  UnaryOpType op_;
};

}  // namespace flang

#endif
