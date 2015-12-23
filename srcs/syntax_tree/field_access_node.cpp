#include "syntax_tree/field_access_node.h"

namespace flang {

void FieldAccessNode::setExpression(ExpNode* expr) {
  expr_.reset(expr);
}

void FieldAccessNode::setFieldName(NameNode* name) {
  field_name_.reset(name);
}

}
