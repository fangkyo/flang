#ifndef SYNTAX_TREE_STMT_NODE_H_
#define SYNTAX_TREE_STMT_NODE_H_

#include "syntax_tree/ast_node.h"

namespace flang {

// This node indicates a statement.
class StmtNode : public ASTNode {
 public:
  ~StmtNode() override {}

 protected:
  StmtNode(ASTNode::ASTNodeType node_type) :
    ASTNode(node_type) {}
};

class EmptyNode : public StmtNode {
 public:
  EmptyNode() : StmtNode(ASTNode::EMPTY_NODE) {}
  ~EmptyNode() override {}
};

} // namespace flang

#endif
