#ifndef NEW_NODE_H_
#define NEW_NODE_H_

#include <string>

#include "syntax_tree/exp_node.h"

namespace flang {

class NewNode : public ExpNode {
 public:
  NewNode(const std::string& class_name);
  ~NewNode() override {};

  std::string& className() { return class_name_; }
  void setClassName(const std::string& class_name) { class_name_ = class_name; }

  void accept(ASTVisitor* visitor) override;

 private:
  std::string class_name_;
};

}  // namespace flang

#endif
