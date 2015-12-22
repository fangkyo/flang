#include "print_node.h"

namespace flang {

PrintNode::PrintNode(ExpNode* exp_node)
    : StmtNode(ASTNode::PRINT_NODE), exp_node_(exp_node) {}

}  // namespace flang
