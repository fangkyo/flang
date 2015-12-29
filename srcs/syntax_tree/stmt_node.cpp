#include "syntax_tree/stmt_node.h"
#include "base/stl_utils.h"

namespace flang {

bool StmtListNode::getChildNodes(ASTNodeList* child_nodes) {
  return ptrVectorToVector(stmt_list_, child_nodes);
}

}  // namespace flang
