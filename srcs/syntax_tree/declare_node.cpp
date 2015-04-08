#include "base/stl_utils.h"
#include "declare_node.h"
#include "visitor.h"

namespace flang {

DeclareNode::~DeclareNode() {
  stdDeleteElements(m_varList);
}

void DeclareNode::accept(ASTVisitor* visitor) {
  visitor->doDeclareNode(this);
}

VarNode* DeclareNode::findVar(const string& varName) {
  for (auto* var : m_varList) {
    if (var->getVarNode()->getName() == varName)
      return var->getVarNode();
  }
  return NULL;
}

void DeclareNode::setVarClass(ClassNode* clazz) {
  for (size_t i = 0; i < m_varList.size(); ++i) {
    m_varList[i]->getVarNode()->setClass(clazz);
  }
}

}  // namespace flang
