#include "syntax_tree/data_type_node.h"

namespace flang {

ClassTypeNode::ClassTypeNode(const std::string& name) :
  DataTypeNode(ASTNode::CLASS_TYPE_NODE), name_(name) {
}

void ClassTypeNode::accept(ASTVisitor* visitor) {
  visitor->doClassTypeNode(this);
}

ArrayTypeNode::ArrayTypeNode(DataTypeNode* data_type_node) :
  DataTypeNode(ASTNode::ARRAY_TYPE_NODE),
  data_type_node_(data_type_node) {
}

}  // namespace flang

