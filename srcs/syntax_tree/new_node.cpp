#include "syntax_tree/new_node.h"

namespace flang {

NewNode::NewNode(CallNode* constructor) :
    ExpNode(ASTNode::NEW_EXP_NODE),
    constructor_(constructor) {
  constructor_->setParent(this);
}

}  // namespace flang
