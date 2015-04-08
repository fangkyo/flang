#ifndef SYNTAX_TREE_EXP_NODE_H
#define SYNTAX_TREE_EXP_NODE_H

#include <sstream>
#include <memory>

#include <log4cxx/logger.h>

#include "syntax_tree/data_type.h"
#include "syntax_tree/stmt_node.h"
#include "syntax_tree/syntax_tree.h"

using namespace std;
using namespace log4cxx;

namespace flang {

class ClassNode;

class ExpNode : public StmtNode {
 public:
  ExpNode(ASTNode::ASTNodeType node_type = ASTNode::EXP_NODE) :
    StmtNode(node_type) {}
  virtual bool isConst() { return false; }
  void accept(Visitor& visitor) override;
};

template <class T>
class PrimitiveNode : public ExpNode {
  public:
    PrimitiveNode(ASTNodeType node_type) : ExpNode(node_type) {}
    void setValue(const T& value) { value_ = value; }
    const T& value() { return value_; }
  protected:
    T value_;
};

class IntegerNode : public PrimitiveNode<int> {
 public:
  IntegerNode() : PrimitiveNode(ASTNode::INTEGER_NODE) {}
  bool isConst() override { return true; }
};

class StringNode : public PrimitiveNode<std::string> {
 public:
  StringNode() : PrimitiveNode(ASTNode::STRING_NODE) {}
  bool isConst() override { return true; }
};

class BoolNode : public ExpNode {
 public:
  BoolNode(bool val) : m_val(val) {
    setDataTypeNode(BoolTypeNode::getInstance());
  }

  bool isConst() override { return true; }

  string toString() { return m_val ? string("true") : string("false"); }
};

class CharNode : public ExpNode {
 public:
  char m_val;

  CharNode(char val) : m_val(val) {
    setDataTypeNode(CharTypeNode::getInstance());
  }

  virtual bool isConst() { return true; }
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

  void accept(Visitor& visitor);

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

  void accept(Visitor& visitor);
};

class OpNode : public ExpNode {
 public:
  OpType m_op;
  ExpNode* m_leftOpnd;
  ExpNode* m_rightOpnd;

  OpNode(OpType op, ExpNode* leftOpnd, ExpNode* rightOpnd)
      : m_op(op), m_leftOpnd(leftOpnd), m_rightOpnd(rightOpnd) {}

  OpType getOp() { return m_op; }

  void accept(Visitor& visitor);

  bool hasLeftOpnd() { return m_leftOpnd != NULL; }
  bool hasRightOpnd() { return m_rightOpnd != NULL; }

  const char* getOpStr();

  string toString();

  DataTypeNode* getLeftDataTypeNode() { return m_leftOpnd->getDataTypeNode(); }
  DataTypeNode* getRightDataTypeNode() {
    return m_rightOpnd->getDataTypeNode();
  }
};

class AssignNode : public ExpNode {
 public:
  VarNode* m_var;
  ExpNode* m_exp;

  AssignNode(VarNode* var, ExpNode* exp = NULL) : m_var(var), m_exp(exp) {
    assert(m_var);
  }

  void setVarNode(VarNode* varNode) { m_var = varNode; }
  VarNode* getVarNode() { return m_var; }

  void setExpNode(ExpNode* expNode) { m_exp = expNode; }
  ExpNode* getExpNode() { return m_exp; }

  DataTypeNode* getVarDataTypeNode() {
    if (NULL == m_var) return UNDEF_TYPE_NODE;
    return m_var->getDataTypeNode();
  }

  DataTypeNode* getExpDataTypeNode() {
    if (NULL == m_exp) return UNDEF_TYPE_NODE;
    return m_exp->getDataTypeNode();
  }

  void setVarDataTypeNode(DataTypeNode* dtype) {
    if (NULL == dtype || NULL == m_var) return;
    m_var->setDataTypeNode(dtype);
  }

  void accept(Visitor& visitor);
};

class AddNode : public OpNode {

 public:
  AddNode(ExpNode* left, ExpNode* right) : OpNode(OP_ADD, left, right) {}

  void accept(Visitor& visitor);
};

class SubNode : public OpNode {
 public:
  SubNode(ExpNode* left, ExpNode* right) : OpNode(OP_SUB, left, right) {}

  void accept(Visitor& visitor);
};

class MulNode : public OpNode {
 public:
  MulNode(ExpNode* left, ExpNode* right) : OpNode(OP_MUL, left, right) {}

  void accept(Visitor& visitor);
};

class DivNode : public OpNode {
 public:
  DivNode(ExpNode* left, ExpNode* right) : OpNode(OP_DIV, left, right) {}

  void accept(Visitor& visitor);
};

class AndNode : public OpNode {
 public:
  AndNode(ExpNode* left, ExpNode* right) : OpNode(OP_AND, left, right) {}

  void accept(Visitor& visitor);
};

class LtNode : public OpNode {
 public:
  LtNode(ExpNode* left, ExpNode* right) : OpNode(OP_LT, left, right) {}
};

class EqNode : public OpNode {
 public:
  EqNode(ExpNode* left, ExpNode* right) : OpNode(OP_EQ, left, right) {}
};

class NewNode : public ExpNode {
 private:
  string m_className;
  ClassNode* m_class;

 public:
  NewNode(const string& className) : m_className(className), m_class(NULL) {}
  ~NewNode();

  string& getClassName() { return m_className; }
  void setClassNode(ClassNode* clazz) { m_class = clazz; }
  ClassNode* getClassNode() { return m_class; }

  void accept(Visitor& visitor);
};

} // namespace flang

#endif
