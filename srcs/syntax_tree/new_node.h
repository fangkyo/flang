#ifndef NEW_NODE_H_
#define NEW_NODE_H_

#include <memory>
#include <string>

#include "syntax_tree/exp_node.h"
#include "syntax_tree/name_node.h"

namespace flang {

class NewNode : public ExpNode {
 public:
  NewNode(NameNode* class_name);
  ~NewNode() override {};

  NameNode* getClassName() { return class_name_.get(); }
  void setClassName(NameNode* class_name) { class_name_.reset(class_name); }

  void accept(ASTVisitor* visitor) override;

 private:
  std::unique_ptr<NameNode> class_name_;
};

}  // namespace flang

#endif
