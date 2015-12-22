#include "syntax_tree/new_node.h"

namespace flang {

NewNode::NewNode(NameNode* class_name) :
    ExpNode(ASTNode::NEW_EXP_NODE),
    class_name_(class_name) {
  class_name_->setParent(this);
}

}  // namespace flang
