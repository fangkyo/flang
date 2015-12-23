#ifndef FIELD_ACCESS_NODE_H_
#define FIELD_ACCESS_NODE_H_

#include <memory>

#include "syntax_tree/exp_node.h"
#include "syntax_tree/name_node.h"

namespace flang {

class FieldAccessNode : public ExpNode {
 INHERIT_AST_NODE(FieldAccessNode, ExpNode, FIELD_ACCESS_NODE)
 public:
  FieldAccessNode() {}
  ~FieldAccessNode() override {}

  void setExpression(ExpNode* expr);
  void setFieldName(NameNode* name);

 private:
  std::unique_ptr<ExpNode> expr_;
  std::unique_ptr<NameNode> field_name_;
};

}  // namespace flang

#endif
