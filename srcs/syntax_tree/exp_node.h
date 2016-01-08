#ifndef EXP_NODE_H_
#define EXP_NODE_H_

#include <memory>

#include "syntax_tree/ast_node.h"
#include "symbol_table/symbol.h"
#include "syntax_tree/stmt_node.h"

namespace flang {

// Expression node
class ExpNode : public StmtNode {
 INHERIT_AST_NODE(ExpNode, StmtNode, EXP_NODE)

 public:
  ~ExpNode() override {}
  virtual bool isConst() { return false; }

  // @brief Whether this expression is a "L-Value" expression.
  // @return Return true if this expression is a "L-Value" expression.
  //     Otherwise return false.
  virtual bool isLeftValue() const { return false; }

  void setDataType(DataType* data_type) {
    CHECK(data_type);
    data_type_ = data_type;
  }

  DataType* getDataType() const {
    return data_type_;
  }

 protected:
  ExpNode() : data_type_(nullptr) {}
  DataType* data_type_;
};


} // namespace flang

#endif
