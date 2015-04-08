#include <iostream>

#include "exp_node.h"
#include "visitor.h"

using namespace std;

namespace flang {

void VarNode::accept(ASTVisitor* visitor) {
  visitor->doVarNode(this);
}

void VarRefNode::accept(ASTVisitor* visitor) {
  visitor->doVarRefNode(this);
}



NewNode::~NewNode() {
}

void NewNode::accept(ASTVisitor* visitor) {
  visitor->doNewNode(this);
}

}  // namespace flang
