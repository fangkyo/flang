#ifndef EXP_NODE_H_
#define EXP_NODE_H_

#include <memory>

#include "symbol_table/symbol.h"
#include "syntax_tree/stmt_node.h"

namespace flang {

// Expression node
class ExpNode : public StmtNode {
 public:
  ~ExpNode() override {}
  virtual bool isConst() { return false; }
 
  // @brief Whether this expression is a "L-Value" expression.
  // @return Return true if this expression is a "L-Value" expression.
  //     Otherwise return false.
  virtual bool isLeftValue() const { return false; }

 protected:
  ExpNode(ASTNode::ASTNodeType node_type) :
      StmtNode(node_type) {}
  std::unique_ptr<Symbol> symbol_;
};


} // namespace flang

#endif
