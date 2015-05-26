#include "syntax_tree/var_decl_node.h"

namespace flang {

VarDeclarationFragmentNode::VarDeclarationFragmentNode(
    const std::string& name, ExpNode* initializer) :
    ASTNode(ASTNode::VAR_DECL_FRAGMENT_NODE),
    name_(name), initializer_(initializer) {

}

void VarDeclarationFragmentNode::accept(ASTVisitor* visitor) {
  visitor->start(this);
  initializer_->accept(visitor);
  visitor->finish(this);
}

VarDeclarationNode::VarDeclarationNode() : StmtNode(ASTNode::VAR_DECL_NODE) {

}

void VarDeclarationNode::accept(ASTVisitor* visitor) {
  visitor->start(this);
  for (auto& var_decl_fragment : var_decl_fragments_) {
    var_decl_fragment.accept(visitor);
  }
  visitor->finish(this);
}

}  // namespace flang
