#include "syntax_tree/data_type_node.h"

namespace flang {

ArrayTypeNode::ArrayTypeNode(DataTypeNode* data_type_node) :
  DataTypeNode(ASTNode::ARRAY_TYPE_NODE),
  data_type_node_(data_type_node) {
}

}  // namespace flang

