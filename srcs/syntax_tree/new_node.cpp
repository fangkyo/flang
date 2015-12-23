#include "syntax_tree/new_node.h"

namespace flang {

NewNode::NewNode(CallNode* constructor) :
    constructor_(constructor) {
  constructor_->setParent(this);
}

}  // namespace flang
