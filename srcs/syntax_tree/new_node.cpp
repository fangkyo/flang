#include "syntax_tree/new_node.h"

namespace flang {

bool NewNode::getChildNodes(ASTNodeList* child_nodes) {
  child_nodes->push_back(class_name_.get());
  child_nodes->push_back(param_list_.get());
  return true;
}

}  // namespace flang
