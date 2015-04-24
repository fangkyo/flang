#ifndef CLASS_NODE_H
#define CLASS_NODE_H

#include <memory>
#include <string>

#include <boost/ptr_container/ptr_vector.hpp>

#include "syntax_tree/exp_node.h"
#include "syntax_tree/func_node.h"
#include "syntax_tree/name_node.h"
#include "syntax_tree/var_declaration_node.h"

namespace flang {

class ClassNode : public StmtNode {
public:
  ClassNode() : StmtNode(ASTNode::CLASS_NODE) {}
  ~ClassNode() override {}

  void setName(const std::string &name) { name_ = name; }
  const std::string &getName() { return name_; }

  void setBaseClass(NameNode* base_class) { base_class_.reset(base_class); }
  NameNode* getBaseClass() { return base_class_.get(); }

  // Add member variable declaration
  void addVarDeclaration(VarDeclarationNode* member_var) {
    member_var->setParent(this);
    member_var_list_.push_back(member_var);
  }
  const boost::ptr_vector<VarDeclarationNode>& getVarDeclarationList() {
    return member_var_list_;
  }

  void addFunction(FuncNode* member_func) {
    member_func->setParent(this);
    member_func_list_.push_back(member_func);
  }
  const boost::ptr_vector<FuncNode>& getFunctionList() {
    return member_func_list_;
  }

  bool hasBaseClass() { return base_class_ == nullptr; }

  void accept(ASTVisitor* visitor) override;

  // void acceptVars(Visitor &visitor);

  // void acceptFuncs(Visitor &visitor, ScopeManager &scopeManager,
                   // ErrorEngine &errorEngine);

  // ClassFuncNode *findMemberFunc(const std::string &funcName,
                                // vector<DataTypeNode *> &paramsType);

  // ClassFuncNode *findMemberFunc(const std::string &funcName);

  // VarNode *findMemberVar(const std::string &varName);

 private:
  std::string name_;
  std::unique_ptr<NameNode> base_class_;
  boost::ptr_vector<VarDeclarationNode> member_var_list_;
  boost::ptr_vector<FuncNode> member_func_list_;
};

}  // namespace flang

#endif
