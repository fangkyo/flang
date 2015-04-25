#include "base/check.h"
#include "syntax_tree/block_node.h"

namespace flang {

BlockNode::BlockNode() : ASTNode(ASTNode::BLOCK_NODE) {
}

void BlockNode::accept(ASTVisitor* visitor) {
  CHECK_NOTNULL(visitor);
  visitor->visit(this);
}

void BlockNode::addStatement(StmtNode* stmt_node) {
  CHECK_NOTNULL(stmt_node);
  stmt_node->setParent(this);
  stmt_list_.push_back(stmt_node);
}

} // namespace flang
