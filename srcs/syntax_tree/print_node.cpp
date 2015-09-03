#include "print_node.h"

namespace flang {

PrintNode::PrintNode(ExpNode* exp_node)
    : StmtNode(ASTNode::PRINT_NODE), exp_node_(exp_node) {}

void PrintNode::accept(ASTVisitor* visitor) {
  visitor->visit(this);
  exp_node_->accept(visitor);
  visitor->endVisit(this);
}

}  // namespace flang
