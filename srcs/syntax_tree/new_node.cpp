#include "syntax_tree/new_node.h"

namespace flang {

NewNode::~NewNode() {
}

void NewNode::accept(ASTVisitor* visitor) {
  visitor->doNewNode(this);
}

}  // namespace flang
