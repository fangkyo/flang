#ifndef CLASS_NODE_H
#define CLASS_NODE_H

#include <cassert>
#include <vector>
#include <string>

#include <boost/ptr_container/ptr_vector.hpp>

#include "exp_node.h"
#include "func_node.h"
#include "declare_node.h"
#include "scope.h"

using namespace std;

namespace flang {

class ClassNode : public StmtNode {
public:
  ClassNode() : StmtNode(ASTNODE::CLASS_NODE) {}
  ~ClassNode() override;

  void setName(const string &name) { m_name = name; }
  const string &getName() { return m_name; }

  void setParentName(const string &name) { m_parentName = name; }
  const string &getParentName() { return m_parentName; }

  void setParent(ClassNode *parent);
  ClassNode *getParent() { return m_parent; }
  int getVarsNum() { return m_varList.size(); }
  int getFuncsNum() { return m_funcList.size(); }

  bool hasParent() { return m_parentName.length() > 0; }

  void addVarDeclare(DeclareNode *declare);

  void addFuncion(ClassFuncNode *func);
  void accept(Visitor &visitor);

  void acceptVars(Visitor &visitor);

  void acceptFuncs(Visitor &visitor, ScopeManager &scopeManager,
                   ErrorEngine &errorEngine);

  ClassFuncNode *findMemberFunc(const string &funcName,
                                vector<DataTypeNode *> &paramsType);

  ClassFuncNode *findMemberFunc(const string &funcName);

  VarNode *findMemberVar(const string &varName);

  ClassNode *getClassNode() { return this; }


 private:
  std::string name_;       // class name
  std::string derived_class_; // parent class name
  // Member variable declaration list
  boost::ptr_vector<DeclareNode> member_var_list_;
};

}  // namespace flang

#endif
