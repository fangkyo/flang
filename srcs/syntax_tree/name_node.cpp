#include "syntax_tree/var_node.h"

namespace flang {

VarNode::VarNode(const std::string& name) :
    ExpNode(ASTNode::VAR_NODE),
    name_(name) {
}

void VarNode::accept(ASTVisitor* visitor) {
  visitor->doVarNode(this);
}

}  // namespace flang

