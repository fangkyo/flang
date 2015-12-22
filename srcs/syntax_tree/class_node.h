#ifndef CLASS_NODE_H
#define CLASS_NODE_H

#include <memory>
#include <string>

#include <boost/ptr_container/ptr_vector.hpp>

#include "syntax_tree/exp_node.h"
#include "syntax_tree/name_node.h"

namespace flang {

class ClassNode : public StmtNode {
 INHERIT_AST_NODE(ClassNode, StmtNode)

public:
  ClassNode() : StmtNode(ASTNode::CLASS_NODE) {}
  ~ClassNode() override {}

  void setName(const std::string &name) { name_ = name; }
  const std::string &getName() { return name_; }

  void setSuperClass(NameNode* super_class) { super_class_.reset(super_class); }
  NameNode* getSuperClass() { return super_class_.get(); }

  // Add member variable declaration
  //void addVariable(VarDeclarationNode* member_var) {
    //member_var->setParent(this);
    //member_vars_.push_back(member_var);
  //}
  //const boost::ptr_vector<VarDeclarationNode>& getVarDeclar() {
    //return member_vars_;
  //}

  bool hasSuperClass() { return super_class_ == nullptr; }

	bool getChildNodes(ASTNodeList* child_nodes) override;

 private:
  std::string name_;
  std::unique_ptr<NameNode> super_class_;
  boost::ptr_vector<ASTNode> body_decls_;
  //boost::ptr_vector<VarDeclarationNode> member_vars_;
  //boost::ptr_vector<FuncNode> member_funcs_;
  //std::vector<ClassNode*> inner_classes_;
};

}  // namespace flang

#endif
