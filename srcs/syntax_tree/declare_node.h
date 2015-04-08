#ifndef DECLARE_NODE_H
#define DECLARE_NODE_H

#include <vector>

#include "syntax_tree/stmt_node.h"

namespace flang {

class DeclareNode : public StmtNode {
 public:
  DeclareNode(ASTNode* parent);
  ~DeclareNode();

  void accept(ASTVisitor* visitor) override;

  void addDeclare(AssignNode* assignNode) { var_list_.push_back(assignNode); }

  const std::vector<AssignNode*>& varList() { return var_list_; }

 private:
  std::vector<AssignNode*> var_list_;

};

}  // namespace flang

#endif
