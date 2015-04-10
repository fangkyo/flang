#ifndef EXP_NODE_H_
#define EXP_NODE_H_

#include <memory>

#include "syntax_tree/stmt_node.h"

namespace flang {

// Expression node
class ExpNode : public StmtNode {
 public:
  ~ExpNode() override {}
  virtual bool isConst() { return false; }

 protected:
  ExpNode(ASTNode::ASTNodeType node_type) : StmtNode(node_type) {}
};


} // namespace flang

#endif
