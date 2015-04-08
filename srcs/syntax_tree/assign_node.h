#ifndef ASSIGN_NODE_H_
#define ASSIGN_NODE_H_

#include <memory>

#include "syntax_tree/exp_node.h"

namespace flang {

class AssignNode : public ExpNode {
 public:
  enum AssignOpType {
    OP_ASSIGN,
    OP_ADD_ASSIGN,
    OP_SUB_ASSIGN,
    OP_MUL_ASSIGN,
    OP_DIV_ASSIGN,
  };

  AssignNode(VarNode* var, ExpNode* exp = NULL) : m_var(var), m_exp(exp) {
    assert(m_var);
  }

  void setVarNode(VarNode* var_node) { var_node_.reset(var_node); }
  VarNode* getVarNode() { return var_node_.get(); }

  void setExpNode(ExpNode* exp_node_) { var_node_.reset(exp_node); }
  ExpNode* getExpNode() { return exp_node_.get(); }

  // DataTypeNode* getVarDataTypeNode() {
    // if (NULL == m_var) return UNDEF_TYPE_NODE;
    // return m_var->getDataTypeNode();
  // }

  // DataTypeNode* getExpDataTypeNode() {
    // if (NULL == m_exp) return UNDEF_TYPE_NODE;
    // return m_exp->getDataTypeNode();
  /* } */

  void setVarDataTypeNode(DataTypeNode* dtype) {
    if (NULL == dtype || NULL == m_var) return;
    m_var->setDataTypeNode(dtype);
  }

  void accept(ASTVisitor* visitor) override;

 private:
  std::unique_ptr<VarNode> var_node_;
  std::unique_ptr<ExpNode> exp_node_;
};

}  // namespace flang

#endif
