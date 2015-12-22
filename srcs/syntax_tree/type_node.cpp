#include "syntax_tree/type_node.h"

namespace flang {

UserDefTypeNode::UserDefTypeNode(NameNode* name) : TypeNode(ASTNode::USER_DEF_TYPE_NODE), name_(name) {}

//ArrayTypeNode::ArrayTypeNode(DataTypeNode* data_type_node) :
  //DataTypeNode(ASTNode::ARRAY_TYPE_NODE),
  //data_type_node_(data_type_node) {
//}

}  // namespace flang

