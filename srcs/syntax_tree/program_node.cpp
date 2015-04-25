#include "base/check.h"
#include "syntax_tree/program_node.h"
#include "syntax_tree/stmt_node.h"

namespace flang {

ProgramNode::ProgramNode() : ASTNode(ASTNode::PROGRAM_NODE) {
}

void ProgramNode::accept(ASTVisitor* visitor) {
  CHECK_NOTNULL(visitor);
  if (visitor->beforeVisit(this)) {
    for (auto& stmt : stmt_list_) {
      stmt.accept(visitor);
    }
    if (visitor->visit(this)) {
      visitor->afterVisit(this);
    }
  }
}

void ProgramNode::addStatement(StmtNode* stmt_node) {
  CHECK_NOTNULL(stmt_node);
  stmt_node->setParent(this);
  stmt_list_.push_back(stmt_node);
}

} // namespace flang
