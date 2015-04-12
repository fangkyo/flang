#ifndef DECLARE_NODE_H
#define DECLARE_NODE_H

#include <memory>
#include <vector>

#include <boost/ptr_container/ptr_vector.hpp>

#include "syntax_tree/stmt_node.h"
#include "syntax_tree/var_node.h"
#include "syntax_tree/data_type_node.h"

namespace flang {


class VariableDeclarationFragmentNode {
 public:
  VariableDeclarationFragmentNode();
  ~VariableDeclarationFragmentNode() override {}

  void setNameNode(SimpleNameNode* name_node) { name_node_.reset(name_node); }
  void 

 private:
  std::unique_ptr<SimpleNameNode> name_;
};

class DeclareNode : public StmtNode {
 public:
  DeclareNode(ASTNode* parent);
  ~DeclareNode() override {}

  void accept(ASTVisitor* visitor) override;

  // Add declare var node. This node can be a VarNode or an AssignNode used
  // for initialization.
  void addDeclVar(ASTNode* decl_var) {
    decl_var_list_.push_back(decl_var);
  }
  const boost::ptr_vector<ASTNode>& declVarList() {
    return decl_var_list_;
  }

 private:
  std::unique_ptr<DataTypeNode> data_type_node_;
  boost::ptr_vector<ASTNode> decl_var_list_;

};


}  // namespace flang

#endif
