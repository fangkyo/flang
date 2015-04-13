#include "base/check.h"
#include "syntax_tree/program_node.h"
#include "syntax_tree/stmt_node.h"

namespace flang {

ProgramNode::ProgramNode() : ASTNode(ASTNode::PROGRAM_NODE) {
}

void ProgramNode::accept(ASTVisitor* visitor) {
  CHECK_NOTNULL(visitor);
  visitor->doProgramNode(this);
}

void ProgramNode::addStmt(StmtNode* stmt_node) {
  CHECK_NOTNULL(stmt_node);
  stmt_list_.push_back(stmt_node);
}

} // namespace flang
