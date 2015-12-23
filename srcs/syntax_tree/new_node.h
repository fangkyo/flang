#ifndef NEW_NODE_H_
#define NEW_NODE_H_

#include <memory>
#include <string>

#include "syntax_tree/exp_node.h"
#include "syntax_tree/func_node.h"

namespace flang {

class NewNode : public ExpNode {
 INHERIT_AST_NODE(NewNode, ExpNode)

 public:
  NewNode(CallNode* constructor);
  ~NewNode() override {};

 private:
  std::unique_ptr<CallNode> constructor_;
};

}  // namespace flang

#endif
