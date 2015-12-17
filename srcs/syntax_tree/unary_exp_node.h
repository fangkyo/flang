#ifndef UNARY_EXP_NODE_H_
#define UNARY_EXP_NODE_H_

#include <memory>

#include "syntax_tree/ast_node.h"
#include "syntax_tree/exp_node.h"

namespace flang {

// Expression node with unary operator
class UnaryExpNode : public ExpNode {
 public:
  enum UnaryOpType {
    OP_INC, // ++
    OP_DEC, // --
    OP_POS, // +
    OP_NEG, // -
    OP_NOT, // !
  };

  UnaryExpNode(UnaryOpType op, ExpNode* exp_node);
  ~UnaryExpNode() override {}

  void accept(ASTVisitor* visitor) override;
  bool getChildNodes(ASTNodeList* child_nodes) override;

  // Accessor of operator
  UnaryOpType getOperator() { return operator_; }
  void setOperator(UnaryOpType op) { operator_ = op; }

  // Accessor of operand
  void setOperand(ExpNode* operand) {
    operand_.reset(operand);
    operand_->setParent(this);
  }
  ExpNode* getOperand() { return operand_.get(); }

 protected:
  UnaryOpType operator_;
  std::unique_ptr<ExpNode> operand_;
};

}  // namespace flang

#endif
