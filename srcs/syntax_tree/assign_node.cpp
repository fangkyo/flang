#include "syntax_tree/assign_node.h"

namespace flang {

void AssignNode::accept(ASTVisitor* visitor) {

  if (m_var) m_var->accept(visitor);
  if (m_exp) m_exp->accept(visitor);

  visitor->doAssignNode(this);
}

}  // namespace flang
