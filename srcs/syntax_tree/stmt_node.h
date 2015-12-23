#ifndef SYNTAX_TREE_STMT_NODE_H_
#define SYNTAX_TREE_STMT_NODE_H_

#include <boost/ptr_container/ptr_vector.hpp>

#include "syntax_tree/ast_node.h"

namespace flang {

// This node indicates a statement.
class StmtNode : public ASTNode {
 INHERIT_AST_NODE(StmtNode, ASTNode)

 public:
  ~StmtNode() override {}

 protected:
  StmtNode(ASTNode::ASTNodeType node_type) :
    ASTNode(node_type) {}
};

class EmptyStmtNode : public StmtNode {
 INHERIT_AST_NODE(EmptyStmtNode, StmtNode)
 public:
  EmptyStmtNode() : StmtNode(ASTNode::EMPTY_STMT_NODE) {}
  ~EmptyStmtNode() override {}
};

class StmtListNode : public ASTNode {
 INHERIT_AST_NODE(StmtListNode, ASTNode)
 public:
  StmtListNode() : ASTNode(ASTNode::STMT_LIST_NODE) {}
  ~StmtListNode() override {}

  void addStatement(StmtNode* stmt) {
    stmt_list_.push_back(stmt);
  }

 private:
  boost::ptr_vector<StmtNode> stmt_list_;
};

} // namespace flang

#endif
