#ifndef SYNTAX_TREE_STMT_NODE_H_
#define SYNTAX_TREE_STMT_NODE_H_

#include <boost/ptr_container/ptr_vector.hpp>

#include "syntax_tree/ast_node.h"

namespace flang {

// This node indicates a statement.
class StmtNode : public ASTNode {
 INHERIT_AST_NODE(StmtNode, ASTNode, STMT_NODE)

 public:
  ~StmtNode() override {}

 protected:
  StmtNode() {}
};

class EmptyStmtNode : public StmtNode {
 INHERIT_AST_NODE(EmptyStmtNode, StmtNode, EMPTY_STMT_NODE)

 public:
  EmptyStmtNode() {}
  ~EmptyStmtNode() override {}

};

class StmtListNode : public ASTNode {
 INHERIT_AST_NODE(StmtListNode, ASTNode, STMT_LIST_NODE)

 public:
  StmtListNode() {}
  ~StmtListNode() override {}

  void addStatement(StmtNode* stmt) {
    stmt_list_.push_back(stmt);
  }

  const boost::ptr_vector<StmtNode>& getStmtList() const {
    return stmt_list_;
  }

  bool getChildNodes(ASTNodeList* child_nodes) override;

 private:
  boost::ptr_vector<StmtNode> stmt_list_;
};

} // namespace flang

#endif
