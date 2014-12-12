#ifndef DECLARE_NODE_H
#define DECLARE_NODE_H

#include "data_type.h"
#include "exp_node.h"

class DeclareNode : public SyntaxNode {
 public:
  DataTypeNode* m_dataType;
  vector<AssignNode*> m_varList;

  DeclareNode() { m_dataType = UNDEF_TYPE_NODE; }
  ~DeclareNode();

  void accept(Visitor& visitor);

  void setDataTypeNode(DataTypeNode* dataType) { m_dataType = dataType; }
  DataTypeNode* getDataTypeNode() { return m_dataType; }

  void addDeclare(AssignNode* assignNode) { m_varList.push_back(assignNode); }

  vector<AssignNode*>& getDeclareList() { return m_varList; }

  // find declared var by varName
  VarNode* findVar(const string& varName);

  // set the var's class it belongs to
  void setVarClass(ClassNode* clazz);
};

#endif
