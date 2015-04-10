#ifndef SYNTAX_TREE_STMT_NODE_H_
#define SYNTAX_TREE_STMT_NODE_H_

#include "syntax_tree/ast_node.h"

namespace flang {

// This node indicates a statement.
class StmtNode : public ASTNode {
 public:
  virtual ~StmtNode() {}

 protected:
  StmtNode(ASTNode::ASTNodeType node_type) :
    ASTNode(node_type) {}
};

} // namespace flang

#endif
