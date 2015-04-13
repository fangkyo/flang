#include "syntax_tree/var_declaration_node.h"

namespace flang {

VarDeclarationFragmentNode::VarDeclarationFragmentNode(
    const std::string& name, ExpNode* initializer) :
    ASTNode(ASTNode::VAR_DECL_FRAGMENT_NODE),
    name_(name), initializer_(initializer) {

}

VarDeclarationNode::VarDeclarationNode() : StmtNode(ASTNode::VAR_DECL_NODE) {

}

void VarDeclarationNode::accept(ASTVisitor* visitor) {
}

}  // namespace flang
