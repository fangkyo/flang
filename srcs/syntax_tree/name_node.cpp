#include <sstream>

#include <boost/format.hpp>

#include "base/stl_utils.h"
#include "syntax_tree/name_node.h"

namespace flang {

SimpleNameNode::SimpleNameNode(const std::string name) :
  name_(name) {
}

bool QualifiedNameNode::getChildNodes(ASTNodeList* child_nodes) {
  return ptrVectorToVector(name_list_, child_nodes);
}

std::string QualifiedNameNode::toString() const {
  CHECK_GT(name_list_.size(), 2);
  std::ostringstream oss;
  auto iter = name_list_.begin();
  oss << iter->toString();
  ++iter;
  for (; iter != name_list_.end(); ++iter) {
    oss << SEPARATOR << iter->toString();
  }
  return oss.str();
}

}  // namespace flang

