#ifndef VAR_NODE_H_
#define VAR_NODE_H_

#include <string>

#include "syntax_tree/exp_node.h"

namespace flang{

class VarNode : public ExpNode {
 public:
  VarNode(const std::string& name);
  ~VarNode() override {}

  void accept(ASTVisitor* visitor) override;

  const std::string& name() { return name_; }
  void setName(const std::string& name) { name_= name; }

 private:
  std::string name_;

};

}  // namespace flang

#endif
