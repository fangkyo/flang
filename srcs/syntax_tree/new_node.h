#ifndef NEW_NODE_H_
#define NEW_NODE_H_

#include <memory>
#include <string>

#include "syntax_tree/exp_node.h"
#include "syntax_tree/func_node.h"
#include "syntax_tree/name_node.h"

namespace flang {

class NewNode : public ExpNode {
 INHERIT_AST_NODE(NewNode, ExpNode, NEW_NODE)

 public:
  NewNode() {}
  ~NewNode() override {};

  void setClassName(NameNode* name) {
    CHECK(name);
    class_name_.reset(name);
    class_name_->setParent(this);
  }

  NameNode* getClassName() const {
    return class_name_.get();
  }

  void setParamList(ParamListNode* param_list) {
    CHECK(param_list);
    param_list_.reset(param_list);
    param_list_->setParent(this);
  }

  ParamListNode* getParamList() const {
    return param_list_.get();
  }

  bool getChildNodes(ASTNodeList* child_nodes) override;

 private:
  std::unique_ptr<NameNode> class_name_;
  std::unique_ptr<ParamListNode> param_list_;

};

}  // namespace flang

#endif
