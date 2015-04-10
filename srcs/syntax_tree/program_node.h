#ifndef SYNTAX_TREE_PROGRAM_NODE_H_
#define SYNTAX_TREE_PROGRAM_NODE_H_

#include <vector>

#include "syntax_tree/ast_node.h"

namespace flang {

class StmtNode;

// This class represents the program of a file, which is the root
// of a syntax tree.
class ProgramNode : public ASTNode {
 public:
  ProgramNode();
  virtual ~ProgramNode();
  void accept(ASTVisitor* visitor) override;
  const std::vector<StmtNode*>& stmtList() { return stmt_list_; };
  void addStmt(StmtNode* stmt_node);

 private:
  std::vector<StmtNode*> stmt_list_;
};

} // namespace flang

#endif
