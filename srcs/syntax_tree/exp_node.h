#ifndef EXP_NODE_H_
#define EXP_NODE_H_

#include <memory>

#include "symbol_table/symbol_info.h"
#include "syntax_tree/stmt_node.h"

namespace flang {

// Expression node
class ExpNode : public StmtNode {
 public:
  ~ExpNode() override {}
  virtual bool isConst() { return false; }
  DataType* getType() const { return data_type_; }
  void setType(DataType* data_type) { data_type_ = data_type; }

 protected:
  ExpNode(ASTNode::ASTNodeType node_type) :
      StmtNode(node_type), data_type_(nullptr) {}
  DataType* data_type_;
};


} // namespace flang

#endif
