#include "syntax_tree/stmt_node.h"
#include "base/stl_utils.h"

namespace flang {

bool StmtListNode::getChildNodes(ASTNodeList* child_nodes) {
  ptrVectorToVector(stmt_list_, child_nodes);
  return stmt_list_.size() > 0;
}

}  // namespace flang
