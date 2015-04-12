#ifndef DECLARE_NODE_H
#define DECLARE_NODE_H

#include <memory>
#include <vector>

#include <boost/ptr_container/ptr_vector.hpp>

#include "syntax_tree/stmt_node.h"
#include "syntax_tree/data_type_node.h"
#include "syntax_tree/exp_node.h"

namespace flang {

class VarDeclarationFragmentNode : public ASTNode {
 public:
  VarDeclarationFragmentNode(const std::string& name, ExpNode* initializer);
  ~VarDeclarationFragmentNode() override {}

  void setName(std::string name) { name_ = name; }
  const std::string& getName() { return name_; }

  ExpNode* getInitializer() { return initializer_.get(); }
  void setInitializer(ExpNode* initializer) { initializer_.reset(initializer); }

 private:
  std::string name_;
  std::unique_ptr<ExpNode> initializer_;
};

class VarDeclarationNode : public StmtNode {
 public:
  VarDeclarationNode();
  ~VarDeclarationNode() override {}

  void accept(ASTVisitor* visitor) override;

  void addVarDeclFragment(VarDeclarationFragmentNode* var_decl_fragment) {
    var_decl_list_.push_back(var_decl_fragment);
  }
  const boost::ptr_vector<VarDeclarationFragmentNode>& getVarDeclFragmentList() {
    return var_decl_list_;
  }

  DataTypeNode* getDataType() { return data_type_.get(); }
  void setDataType(DataTypeNode* data_type) { data_type_.reset(data_type); }

 private:
  std::unique_ptr<DataTypeNode> data_type_;
  boost::ptr_vector<VarDeclarationFragmentNode> var_decl_list_;
};

}  // namespace flang

#endif
