#include "syntax_tree/field_access_node.h"

namespace flang {

void FieldAccessNode::setExpression(ExpNode* expr) {
  expr_.reset(expr);
  expr_->setParent(this);
}

void FieldAccessNode::setFieldName(SimpleNameNode* name) {
  field_name_.reset(name);
  field_name_->setParent(this);
}

}
