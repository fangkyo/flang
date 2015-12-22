#ifndef BLOCK_NODE_H_
#define BLOCK_NODE_H_

#include "syntax_tree/stmt_node.h"

#include <boost/ptr_container/ptr_vector.hpp>

namespace flang {

class BlockNode : public ASTNode {
 INHERIT_AST_NODE(BlockNode, ASTNode)

 public:
  BlockNode();
  ~BlockNode() override {}

  const boost::ptr_vector<StmtNode>& getStatementList() {
    return stmt_list_;
  }
  void addStatement(StmtNode* stmt_node);

  //bool getChildNodes(ASTNodeList*) override;

 private:
  boost::ptr_vector<StmtNode> stmt_list_;
};

}  // namespace flang

#endif
