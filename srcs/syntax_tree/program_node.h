#ifndef SYNTAX_TREE_PROGRAM_NODE_H_
#define SYNTAX_TREE_PROGRAM_NODE_H_

#include <boost/ptr_container/ptr_vector.hpp>

#include "syntax_tree/ast_node.h"
#include "syntax_tree/import_node.h"
#include "syntax_tree/stmt_node.h"

namespace flang {

// This class represents the program of a file, which is the root
// of a syntax tree.
class ProgramNode : public ASTNode {
 INHERIT_AST_NODE(ProgramNode, ASTNode, PROGRAM_NODE)

 public:
  ProgramNode() {}
  ~ProgramNode() override {}

  void setImportList(ImportListNode* import_list);
  ImportListNode* getImportList() const {
    return import_list_.get();
  }
  void setStmtList(StmtListNode* stmt_list);
  StmtListNode* getStmtList() const {
    return stmt_list_.get();
  }
  bool getChildNodes(ASTNodeList* child_nodes) override;

 private:
  std::unique_ptr<ImportListNode> import_list_;
  std::unique_ptr<StmtListNode> stmt_list_;
};

} // namespace flang

#endif
