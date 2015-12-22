#include "syntax_tree/var_decl_node.h"

namespace flang {

VarDeclFragmentNode::VarDeclFragmentNode(
    const std::string& name, ExpNode* initializer) :
    ASTNode(ASTNode::VAR_DECL_FRAGMENT_NODE),
    name_(name), initializer_(initializer) {
  initializer_->setParent(this);
}

VarDeclNode::VarDeclNode() : StmtNode(ASTNode::VAR_DECL_NODE) {

}

}  // namespace flang
