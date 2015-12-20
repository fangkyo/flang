#include "syntax_tree/var_decl_node.h"

namespace flang {

VarDeclFragmentNode::VarDeclFragmentNode(
    const std::string& name, ExpNode* initializer) :
    ASTNode(ASTNode::VAR_DECL_FRAGMENT_NODE),
    name_(name), initializer_(initializer) {
  initializer_->setParent(this);
}

void VarDeclFragmentNode::accept(ASTVisitor* visitor) {
  visitor->visit(this);
  initializer_->accept(visitor);
  visitor->endVisit(this);
}

VarDeclNode::VarDeclNode() : StmtNode(ASTNode::VAR_DECL_NODE) {

}

void VarDeclNode::accept(ASTVisitor* visitor) {
  visitor->visit(this);
  for (auto& var_decl_fragment : var_decl_fragments_) {
    var_decl_fragment.accept(visitor);
  }
  visitor->endVisit(this);
}

}  // namespace flang
