#include "base/check.h"
#include "syntax_tree/program_node.h"

namespace flang {

ProgramNode::ProgramNode() : ASTNode(ASTNode::PROGRAM_NODE) {
}

void ProgramNode::accept(ASTVisitor* visitor) {
  CHECK(visitor);
  visitor->visit(this);
  for (auto& child : child_nodes_) {
    child.accept(visitor);
  }
  visitor->endVisit(this);
}

void ProgramNode::addChildNode(ASTNode* child_node) {
  CHECK(child_node);
  child_node->setParent(this);
  child_nodes_.push_back(child_node);
}

bool ProgramNode::getChildNodes(ASTNodeList* child_nodes) {
  if (child_nodes_.size() > 0) {
    for (auto& child: child_nodes_) {
      child_nodes->push_back(&child);
    }
    return true;
  } else {
    return false;
  }
}

} // namespace flang
