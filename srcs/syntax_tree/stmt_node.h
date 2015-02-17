#ifndef SYNTAX_TREE_STMT_NODE_H_
#define SYNTAX_TREE_STMT_NODE_H_

#include "syntax_tree/syntax_tree.h"

namespace flang {

// This class represents a statement node.
class StmtNode : public ASTNode {
 public:
  virtual ~StmtNode();
};

} // namespace flang

#endif
