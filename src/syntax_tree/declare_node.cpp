#include "base/utils.h"
#include "declare_node.h"
#include "visitor.h"

/*********************************************
 *                 DeclareNode
 *********************************************/
DeclareNode::~DeclareNode() {
  stdDeleteElements(m_varList);
}

void DeclareNode::accept(Visitor& visitor) { visitor.doDeclareNode(this); }

VarNode* DeclareNode::findVar(const string& varName) {
  for (auto* var : m_varList) {
    if (var->getVarNode()->getName() == varName)
      return var->getVarNode();
  }
  return NULL;
}

void DeclareNode::setVarClass(ClassNode* clazz) {
  for (int i = 0; i < m_varList.size(); ++i) {
    m_varList[i]->getVarNode()->setClass(clazz);
  }
}
