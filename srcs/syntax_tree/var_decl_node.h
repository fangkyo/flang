#ifndef DECLARE_NODE_H
#define DECLARE_NODE_H

#include <memory>
#include <vector>

#include <boost/ptr_container/ptr_vector.hpp>

#include "syntax_tree/stmt_node.h"
#include "syntax_tree/data_type_node.h"
#include "syntax_tree/exp_node.h"

namespace flang {

class VarDeclFragmentNode : public ASTNode {
 public:
  VarDeclFragmentNode(const std::string& name, ExpNode* initializer);
  ~VarDeclFragmentNode() override {}

  void setName(std::string name) { name_ = name; }
  const std::string& getName() { return name_; }

  ExpNode* getInitializer() { return initializer_.get(); }
  void setInitializer(ExpNode* initializer) {
    initializer_.reset(initializer);
    initializer_->setParent(this);
  }

  void accept(ASTVisitor* visitor) override;

 private:
  std::string name_;
  std::unique_ptr<ExpNode> initializer_;
};

class VarDeclNode : public StmtNode {
 public:
  VarDeclNode();
  ~VarDeclNode() override {}

  void accept(ASTVisitor* visitor) override;

  void addVarDeclFragment(VarDeclFragmentNode* var_decl_fragment) {
    var_decl_fragments_.push_back(var_decl_fragment);
    var_decl_fragment->setParent(this);
  }
  const boost::ptr_vector<VarDeclFragmentNode>& getVarDeclFragmentList() {
    return var_decl_fragments_;
  }

  TypeNode* getDataType() { return data_type_.get(); }
  void setDataType(TypeNode* data_type) {
    data_type_.reset(data_type);
    data_type_->setParent(this);
  }

 private:
  std::unique_ptr<TypeNode> data_type_;
  boost::ptr_vector<VarDeclFragmentNode> var_decl_fragments_;
};

}  // namespace flang

#endif
