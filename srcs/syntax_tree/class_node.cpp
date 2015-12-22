#include "syntax_tree/class_node.h"
#include "base/stl_utils.h"

using namespace std;

namespace flang {

bool ClassNode::getChildNodes(ASTNodeList* child_nodes) {
	//child_nodes->push_back(super_class_.get());
	//for (auto& member_var: member_vars_) {
		//child_nodes->push_back(&member_var);
	//}
	//for (auto& member_func: member_funcs_) {
		//child_nodes->push_back(&member_func);
	//}
	//child_nodes.insert(
			//child_nodes.end(), inner_classes_.begin(), inner_classes_.end());
  return true;
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
