#include "syntax_tree/ctrl_node.h"

namespace flang {

IfNode::IfNode(ExpNode* test_node, ASTNode* if_node, ASTNode* else_node) :
    test_node_(test_node), if_node_(if_node), else_node_(else_node) {
}

WhileNode::WhileNode(ExpNode* test_node, ASTNode* body_node) :
    test_node_(test_node), body_node_(body_node) {
}

}  // namespace flang
