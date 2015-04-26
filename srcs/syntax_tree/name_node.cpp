#include <boost/format.hpp>

#include "syntax_tree/name_node.h"

namespace flang {

SimpleNameNode::SimpleNameNode(const std::string name) :
  NameNode(ASTNode::SIMPLE_NAME_NODE),
  name_(name) {
}

QualifiedNameNode::QualifiedNameNode(NameNode* qualifier, SimpleNameNode* name) :
    NameNode(ASTNode::QUALIFIED_NAME_NODE),
    qualifier_(qualifier), name_(name) {

}

std::string QualifiedNameNode::getFullyQualifiedName() {
  boost::format fmt = boost::format("%1%.%2%");
  fmt % qualifier_->getFullyQualifiedName() % name_->getName();
  return fmt.str();
}


}  // namespace flang

