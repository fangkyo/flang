#ifndef PRINT_NODE_H
#define PRINT_NODE_H

#include <memory>

#include "syntax_tree/exp_node.h"
#include "syntax_tree/stmt_node.h"

namespace flang {

class PrintNode : public StmtNode {
 public:
  PrintNode(ExpNode* exp_node);

  void accept(ASTVisitor* visitor) override;

  ExpNode* getExpNode() { return exp_node_.get(); }
  void setExpNode(ExpNode* exp_node) { exp_node_.reset(exp_node); }

 private:
  std::unique_ptr<ExpNode> exp_node_;
};

}  // namespace flang

#endif
