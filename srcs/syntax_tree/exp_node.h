#ifndef SYNTAX_TREE_EXP_NODE_H
#define SYNTAX_TREE_EXP_NODE_H

#include <sstream>
#include <memory>

#include <log4cxx/logger.h>

#include "ast_visitor/ast_visitor.h"
#include "syntax_tree/data_type.h"
#include "syntax_tree/stmt_node.h"

using namespace std;
using namespace log4cxx;

namespace flang {

class ClassNode;

// Expression node
class ExpNode : public StmtNode {
 public:
  ~ExpNode() override {}
  virtual bool isConst() { return false; }

 protected:
  ExpNode(ASTNode::ASTNodeType node_type, ASTNode* parent) :
      StmtNode(node_type, parent) {}
};


class VarNode : public ExpNode {
 public:
  // member data
  string m_name;

  ClassNode* m_class;  // the class it belongs to

  // member function

  VarNode(const string& name, DataTypeNode* dtypeNode)
      : m_name(name), m_class(NULL) {
    setDataTypeNode(dtypeNode);
  }

  VarNode(const string& name) : m_name(name), m_class(NULL) {
    setDataTypeNode(UNDEF_TYPE_NODE);
  }

  void setClass(ClassNode* clazz) { m_class = clazz; }

  void accept(ASTVisitor* visitor) override;

  const string& getName() { return m_name; }
  void setName(const string& name) { m_name = name; }

  string toString() { return m_name; }
};

class VarDeclareNode : public VarNode {
 public:
  VarDeclareNode(const string& name) : VarNode(name) {}
};

class VarRefNode : public VarNode {
 private:
  VarNode* m_var;

 public:
  VarRefNode(const string& name, VarNode* varNode = NULL)
      : VarNode(name, UNDEF_TYPE_NODE), m_var(varNode) {}

  void setVarNode(VarNode* varNode) {
    m_var = varNode;
    if (m_var)
      setDataTypeNode(m_var->getDataTypeNode());
    else
      setDataTypeNode(UNDEF_TYPE_NODE);
  }

  VarNode* getVarNode() { return m_var; }

  void accept(ASTVisitor* visitor) override;
};

class NewNode : public ExpNode {
 public:
  NewNode(const string& class_name) : class_name_(class_name) {}
  ~NewNode();

  string& getClassName() { return class_name_; }

  void accept(ASTVisitor* visitor) override;

 private:
  string class_name_;
};

} // namespace flang

#endif
