#include "base/check.h"
#include "syntax_tree/ast_visitor.h"
#include "syntax_tree/reference_node.h"

namespace flang {

void ReferenceNode::accept(ASTVisitor* visitor) {
  CHECK(visitor);
  visitor->visit(this);
  for (auto& child : child_nodes_) {
    child.accept(visitor);
  }
  visitor->endVisit(this);
}

void ReferenceNode::addChildNode(ASTNode* child) {
  CHECK(child);
  child_nodes_.push_back(child);
  child->setParent(this);
}

}  // namespace
