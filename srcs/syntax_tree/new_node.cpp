#include "syntax_tree/new_node.h"

namespace flang {

NewNode::NewNode(NameNode* class_name) :
    ExpNode(ASTNode::NEW_EXP_NODE),
    class_name_(class_name) {
  class_name_->setParent(this);
}

void NewNode::accept(ASTVisitor* visitor) {
  visitor->visit(this);
  class_name_->accept(visitor);
  visitor->endVisit(this);
}

}  // namespace flang
