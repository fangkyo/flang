#ifndef PRINT_NODE_H
#define PRINT_NODE_H

#include <memory>

#include "syntax_tree/exp_node.h"
#include "syntax_tree/stmt_node.h"

namespace flang {

class PrintNode : public StmtNode {
 INHERIT_AST_NODE(PrintNode, StmtNode, PRINT_NODE)

 public:
  PrintNode(ExpNode* exp_node);

  ExpNode* getExpression() { return expr_.get(); }
  void setExpression(ExpNode* expr) {
    CHECK(expr);
    expr_.reset(expr);
    expr_->setParent(this);
  }

  bool getChildNodes(ASTNodeList*) override;

 private:
  std::unique_ptr<ExpNode> expr_;
};

}  // namespace flang

#endif
