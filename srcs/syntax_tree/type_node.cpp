#include "syntax_tree/type_node.h"

namespace flang {

UserDefTypeNode::UserDefTypeNode(NameNode* name) :
  TypeNode(ASTNode::USER_DEF_TYPE_NODE), name_(name) {}


bool UserDefTypeNode::getChildNodes(ASTNodeList* child_nodes) {
  child_nodes->push_back(name_.get());
  return true;
}

//ArrayTypeNode::ArrayTypeNode(DataTypeNode* data_type_node) :
  //DataTypeNode(ASTNode::ARRAY_TYPE_NODE),
  //data_type_node_(data_type_node) {
//}

}  // namespace flang

