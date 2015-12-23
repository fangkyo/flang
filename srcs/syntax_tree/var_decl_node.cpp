#include "syntax_tree/var_decl_node.h"

namespace flang {

VarDeclFragmentNode::VarDeclFragmentNode(
    const std::string& name, ExpNode* initializer) :
    name_(name), initializer_(initializer) {
  initializer_->setParent(this);
}

}  // namespace flang
