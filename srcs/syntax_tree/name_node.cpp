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

void QualifiedNameNode::getQualifiers(
    std::vector<const std::string*>* qualifiers) {
  CHECK(qualifiers);
  qualifier_->getNames(qualifiers);
}

void QualifiedNameNode::getName(std::vector<const std::string*>* name) {
  CHECK(name);
  qualifier_->getNames(name);
  name->push_back(&(name_->getName()));
}

void QualifiedNameNode::accept(ASTVisitor* visitor) {
  visitor->start(this);
  qualifier_->accept(visitor);
  name_->accept(visitor);
  visitor->finish(this);
}

}  // namespace flang

