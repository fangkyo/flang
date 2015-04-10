#include "ast_visitor/ast_visitor.h"
#include "base/check.h"
#include "base/stl_utils.h"
#include "syntax_tree/stmt_node.h"
#include "syntax_tree/program_node.h"

namespace flang {

ProgramNode::ProgramNode() : ASTNode(ASTNode::PROGRAM_NODE){
}

ProgramNode::~ProgramNode() {
  stdDeleteElements(stmt_list_);
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
