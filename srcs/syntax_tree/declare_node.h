#ifndef DECLARE_NODE_H
#define DECLARE_NODE_H

#include <memory>
#include <vector>

#include <boost/ptr_container/ptr_vector.hpp>

#include "syntax_tree/stmt_node.h"
#include "syntax_tree/var_node.h"
#include "syntax_tree/data_type.h"

namespace flang {

class DeclareNode : public StmtNode {
 public:
  DeclareNode(ASTNode* parent);
  ~DeclareNode() override {}

  void accept(ASTVisitor* visitor) override;

  void setDataTypeNode(DataTypeNode* data_type_node) {
    data_type_node_.reset(data_type_node);
  }
  DataTypeNode dataTypeNode() { return data_type_node_.get(); }

  // Add declare var node. This node can be a VarNode or an AssignNode used
  // for initialization.
  void addDeclVar(ASTNode* decl_var) {
    decl_var_list_.push_back(decl_var);
  }
  const boost::ptr_vector<AssignNode>& declVarList() {
    return decl_var_list_;
  }

 private:
  std::unique_ptr<DataTypeNode> data_type_node_;
  boost::ptr_vector<ASTNode> decl_var_list_;

};

}  // namespace flang

#endif
