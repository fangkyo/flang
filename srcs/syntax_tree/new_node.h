#ifndef NEW_NODE_H_
#define NEW_NODE_H_

#include "syntax_tree/exp_node.h"

namespace flang {

class NewNode : public ExpNode {
 public:
  NewNode(const string& class_name) : class_name_(class_name) {}
  ~NewNode();

  string& getClassName() { return class_name_; }

  void accept(ASTVisitor* visitor) override;

 private:
  string class_name_;
};

}  // namespace flang

#endif
