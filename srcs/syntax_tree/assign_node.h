#ifndef ASSIGN_NODE_H_
#define ASSIGN_NODE_H_

#include <memory>

#include "syntax_tree/exp_node.h"

namespace flang {

// Assignment statement node
// assignment:
//   destination '=' source
class AssignNode : public ExpNode {
 INHERIT_AST_NODE(AssignNode, ExpNode, ASSIGN_NODE)

 public:
  enum AssignOpType {
    OP_ASSIGN,  // =
    OP_ADD_ASSIGN, // +=
    OP_SUB_ASSIGN, // -=
    OP_MUL_ASSIGN, // *=
    OP_DIV_ASSIGN, // /=
  };

  AssignNode(ExpNode* left_side, ExpNode* right_side,
             AssignOpType op = AssignOpType::OP_ASSIGN);
  ~AssignNode() override {}

  void setLeftSide(ExpNode* exp_node) {
    left_side_.reset(exp_node);
    left_side_->setParent(this);
  }
  ExpNode* getLeftSide() const { return left_side_.get(); }

  void setRightSide(ExpNode* exp_node) {
    right_side_.reset(exp_node);
    right_side_->setParent(this);
  }
  ExpNode* getRightSide() const { return right_side_.get(); }

  AssignOpType getOperator() const { return operator_; }
  void setOperator(AssignOpType op) { operator_ = op; }

  bool getChildNodes(ASTNodeList* child_nodes) override;

 private:
  std::unique_ptr<ExpNode> left_side_;
  std::unique_ptr<ExpNode> right_side_;
  AssignOpType operator_;
};

}  // namespace flang

#endif
