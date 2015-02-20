#ifndef SYNTAX_TREE_PROGRAM_NODE_H_
#define SYNTAX_TREE_PROGRAM_NODE_H_

#include <list>

#include "syntax_tree/syntax_tree.h"
#include "syntax_tree/stmt_node.h"

namespace flang {

// This class represents the program of a file, which is the root
// of a syntax tree.
class ProgramNode : public ASTNode {
 public:
  ProgramNode();
  virtual ~ProgramNode();
  void accept(ASTVisitor* visitor) override;
  const list<StmtNode*>& stmtList() { return stmt_list_; };
  void addStmt(StmtNode* stmt_node);
 private:
  std::list<StmtNode*> stmt_list_;
};

} // namespace flang

#endif
