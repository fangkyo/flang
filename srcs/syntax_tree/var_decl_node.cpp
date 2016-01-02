#include "syntax_tree/var_decl_node.h"

namespace flang {

VarDeclFragmentNode::VarDeclFragmentNode(
    const std::string& name, ExpNode* initializer) :
    name_(name), initializer_(initializer) {
  initializer_->setParent(this);
}

VarNode::VarNode(SimpleNameNode* node) {
  setName(node);
}

bool VarNode::getChildNodes(ASTNodeList* child_nodes) {
  CHECK(name_);
  child_nodes->push_back(name_.get());
  return true;
}

}  // namespace flang
