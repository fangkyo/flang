#include "syntax_tree/class_node.h"
#include "base/stl_utils.h"

using namespace std;

namespace flang {

ClassNode::~ClassNode() {
  stdDeleteElements(inner_classes_);
}

void ClassNode::accept(ASTVisitor* visitor) {
  visitor->visit(this);
  for (auto& member_var : member_vars_) {
    member_var.accept(visitor);
  }
  for (auto& member_func : member_funcs_) {
    member_func.accept(visitor);
  }

  // for (auto& member_var : member_vars_) {
    // visitor->endVisit(member_var);
  // }
  // for (auto& member_func : member_funcs_) {
    // visitor->endVisit(member_func);
  // }
  visitor->endVisit(this);
}


void ClassNode::addInnerClass(ClassNode* class_node) {
  CHECK(class_node);
  inner_classes_.push_back(class_node);
}
// void ClassNode::acceptVars(Visitor& visitor) {

  // for (size_t i = 0; i < m_varList.size(); ++i) {
    // if (m_varList[i]) {
      // // set every node
      // m_varList[i]->setVarClass(this);
      // m_varList[i]->accept(visitor);
    // }
  // }
// }

// void ClassNode::acceptFuncs(Visitor& visitor, ScopeManager& scopeManager,
                            // ErrorEngine& errorEngine) {

  // unordered_map<std::string, FuncNode*> funcMap;
  // unordered_map<std::string, FuncNode*>::iterator iter;

  // for (size_t i = 0; i < m_funcList.size(); ++i) {

    // if (m_funcList[i]) {
      // iter = funcMap.find(m_funcList[i]->getName());
      // if (iter != funcMap.end()) {
        // FuncRedefinedError error(iter->second, m_funcList[i]);
        // errorEngine.emitError(&error);
      // } else {
        // funcMap.insert(make_pair(m_funcList[i]->getName(), m_funcList[i]));
      // }

      // m_funcList[i]->accept(visitor);
    // }
  // }
// }

// ClassFuncNode* ClassNode::findMemberFunc(const std::string& funcName,
                                         // vector<DataTypeNode*>& paramsType) {

  // for (size_t i = 0; i < m_funcList.size(); ++i) {

    // if (m_funcList[i])
      // if (m_funcList[i]->equals(funcName, paramsType)) return m_funcList[i];
  // }

  // if (m_parent)
    // return m_parent->findMemberFunc(funcName, paramsType);
  // else
    // return NULL;
// }

// ClassFuncNode* ClassNode::findMemberFunc(const std::string& funcName) {

  // for (size_t i = 0; i < m_funcList.size(); ++i) {
    // if (m_funcList[i] && m_funcList[i]->getName() == funcName)
      // return m_funcList[i];
  // }
  // return NULL;
// }

// VarNode* ClassNode::findMemberVar(const std::string& varName) {

  // VarNode* varNode = NULL;
  // for (size_t i = 0; i < m_varList.size(); ++i) {
    // varNode = m_varList[i]->findVar(varName);
    // if (varNode) return varNode;
  // }

  // if (m_parent)
    // return m_parent->findMemberVar(varName);
  // else
    // return NULL;
// }

}  // namespace flang
