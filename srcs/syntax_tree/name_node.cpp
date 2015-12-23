#include <boost/format.hpp>

#include "syntax_tree/name_node.h"

namespace flang {

SimpleNameNode::SimpleNameNode(const std::string name) :
  name_(name) {
}

QualifiedNameNode::QualifiedNameNode(
    NameNode* qualifier, SimpleNameNode* name) :
    qualifier_(qualifier), name_(name) {
  name_->setParent(this);
}

std::string QualifiedNameNode::getFullName() {
  boost::format fmt = boost::format("%1%$%2%");
  fmt % qualifier_->getFullName() % name_->getName();
  return fmt.str();
}

}  // namespace flang

