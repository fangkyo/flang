#include "print_node.h"

namespace flang {

PrintNode::PrintNode(ExpNode* expr) {
  setExpression(expr);
}

bool PrintNode::getChildNodes(ASTNodeList* child_nodes) {
  CHECK(expr_);
  child_nodes->push_back(expr_.get());
  return true;
}

}  // namespace flang
