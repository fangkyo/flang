#include "base/stl_utils.h"
#include "base/check.h"
#include "syntax_tree/class_node.h"

using namespace std;

namespace flang {

void ClassBodyNode::addDeclaration(StmtNode* declaration) {
  CHECK(declaration);
  decl_list_.push_back(declaration);
}

bool ClassBodyNode::getChildNodes(ASTNodeList* child_nodes) {
  return ptrVectorToVector(decl_list_, child_nodes);
}

bool ClassNode::getChildNodes(ASTNodeList* child_nodes) {
  child_nodes->push_back(super_class_.get());
  child_nodes->push_back(body_.get());
  return true;
}

}  // namespace flang
