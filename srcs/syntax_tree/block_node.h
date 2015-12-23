#ifndef BLOCK_NODE_H_
#define BLOCK_NODE_H_

#include <memory>

#include "syntax_tree/stmt_node.h"

#include <boost/ptr_container/ptr_vector.hpp>

namespace flang {

class BlockNode : public StmtNode {
 INHERIT_AST_NODE(BlockNode, StmtNode)

 public:
  BlockNode();
  ~BlockNode() override {}

  StmtListNode* getStatementList() {
    return stmt_list_.get();
  }
  void setStmtList(StmtListNode* stmt_list) {
    stmt_list_.reset(stmt_list);
  }

  bool getChildNodes(ASTNodeList*) override;

 private:
  // boost::ptr_vector<StmtNode> stmt_list_;
  std::unique_ptr<StmtListNode> stmt_list_;
};

}  // namespace flang

#endif
