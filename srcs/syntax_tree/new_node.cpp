#include "syntax_tree/new_node.h"

namespace flang {

NewNode::NewNode(CallNode* constructor) {
  setConstructor(constructor);
}

void NewNode::setConstructor(CallNode* constructor) {
  CHECK(constructor);
  constructor_.reset(constructor);
  constructor_->setParent(this);
}

}  // namespace flang
