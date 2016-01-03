#ifndef FIELD_ACCESS_NODE_H_
#define FIELD_ACCESS_NODE_H_

#include <memory>

#include "exception/exception.h"
#include "syntax_tree/exp_node.h"
#include "syntax_tree/name_node.h"

namespace flang {

class NameNodeCastError : public FrontEndError {
 public:
  NameNodeCastError(const ExpNode& exp_node, const location& loc) : FrontEndError(loc) {
    boost::format fmt("Can't cast %1% to name.");
    setMessage(boost::str(fmt % exp_node.toString()));
  }
  ~NameNodeCastError() override {}
};


class FieldAccessNode : public ExpNode {
 INHERIT_AST_NODE(FieldAccessNode, ExpNode, FIELD_ACCESS_NODE)
 public:
  FieldAccessNode() {}
  ~FieldAccessNode() override {}

  void setExpression(ExpNode* expr);
  ExpNode* getExpression() const {
    return expr_.get();
  }
  void setFieldName(SimpleNameNode* name) {
    CHECK(name);
    field_name_.reset(name);
    field_name_->setParent(this);
  }
  SimpleNameNode* getFieldName() const {
    return field_name_.get();
  }

  bool getChildNodes(ASTNodeList* child_nodes) override;
  NameNode* toNameNode();

 protected:
  QualifiedNameNode* toQualifiedNameNode(QualifiedNameNode* name_node);
 
 private:
  std::unique_ptr<ExpNode> expr_;
  std::unique_ptr<SimpleNameNode> field_name_;
};

}  // namespace flang

#endif
