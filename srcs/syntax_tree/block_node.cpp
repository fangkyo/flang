#include "base/stl_utils.h"
#include "syntax_tree/block_node.h"
#include "syntax_tree/ast_visitor.h"

namespace flang {

bool BlockNode::getChildNodes(ASTNodeList* child_nodes) {
  child_nodes->push_back(stmt_list_.get());
  return true;
}

} // namespace flang
