#include "base/check.h"
#include "syntax_tree/program_node.h"

namespace flang {

void ProgramNode::setImportList(ImportListNode* import_list) {
  import_list_.reset(import_list);
}

void ProgramNode::setStmtList(StmtListNode* stmt_list) {
  stmt_list_.reset(stmt_list);
}

bool ProgramNode::getChildNodes(ASTNodeList* child_nodes) {
  child_nodes->push_back(import_list_.get());
  child_nodes->push_back(stmt_list_.get());
  return true;
}

} // namespace flang
