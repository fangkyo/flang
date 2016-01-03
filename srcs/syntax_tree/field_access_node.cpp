#include <boost/format.hpp>

#include "syntax_tree/field_access_node.h"

namespace flang {

void FieldAccessNode::setExpression(ExpNode* expr) {
  expr_.reset(expr);
  expr_->setParent(this);
}

NameNode* FieldAccessNode::toNameNode() {
  if (expr_) {
    std::unique_ptr<QualifiedNameNode> name_node(new QualifiedNameNode());
    return toQualifiedNameNode(name_node.release());
  } else {
    return field_name_.release();
  }
}

QualifiedNameNode* FieldAccessNode::toQualifiedNameNode(QualifiedNameNode* name_node) {
  CHECK(name_node);
  switch (expr_->getNodeType()) {
    case ASTNodeType::FIELD_ACCESS_NODE: {
      auto* field_access = dynamic_cast<FieldAccessNode*>(expr_.get());
      CHECK(field_access);
      name_node = field_access->toQualifiedNameNode(name_node);
      break;
    }
    case ASTNodeType::SIMPLE_NAME_NODE: {
      auto* simple_name = dynamic_cast<SimpleNameNode*>(expr_.release());
      CHECK(simple_name);
      name_node->addSimpleName(simple_name);
      break;
    }
    default:
      throw new NameNodeCastError(*expr_, getLocation());
  } // end swtich

  name_node->addSimpleName(field_name_.release());
  return name_node;
}

bool FieldAccessNode::getChildNodes(ASTNodeList* child_nodes) {
  if (expr_) {
    child_nodes->push_back(expr_.get());
    return true;
  } else {
    return false;
  }
}

}
