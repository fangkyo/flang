#include "syntax_tree/import_node.h"
#include "base/stl_utils.h"

namespace flang {

void ImportListNode::addImport(ImportNode* import) {
  import_list_.push_back(import);
  import->setParent(this);
}

bool ImportNode::getChildNodes(ASTNodeList* child_nodes) {
  CHECK(package_name_);
  child_nodes->push_back(package_name_.get());
  if (alias_) {
    child_nodes->push_back(alias_.get());
  }
  return true;
}

bool ImportListNode::getChildNodes(ASTNodeList* child_nodes) {
  return ptrVectorToVector(import_list_, child_nodes);
}

}  // namespace flang
