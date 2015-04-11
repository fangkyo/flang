#include "base/stl_utils.h"
#include "declare_node.h"

namespace flang {

void DeclareNode::accept(ASTVisitor* visitor) {
  visitor->doDeclareNode(this);
}

}  // namespace flang
