#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>

#include "exp_node.h"

using namespace std;

class ClassNode;

enum FuncType {
  FUNC_GLOBAL,  // global function
  FUNC_CLASS    // class function
};

/**
 * A interface of function node
 */
class FuncNode : public SyntaxNode {
 public:
  virtual const string& getName() = 0;
  virtual void setName(const string& name) = 0;

  virtual void setRetType(DataTypeNode* retType) = 0;
  virtual DataTypeNode* getRetType() = 0;

  virtual void setBody(SyntaxNode* body) = 0;
  virtual SyntaxNode* getBody() = 0;

  virtual void setParamList(vector<VarNode>& paramList) = 0;
  virtual vector<VarNode>& getParamList() = 0;
  virtual void addParam(const VarNode& var) = 0;

  virtual bool hasReturn() = 0;
  virtual void setReturn(bool hasRet) = 0;

  virtual bool equals(const FuncNode& funcNode) = 0;
  virtual bool equals(const string& funcName,
                      vector<DataTypeNode*>& paramsType) = 0;

  virtual void getParamsType(vector<DataTypeNode*>& paramsType) = 0;

  virtual FuncType getFuncType() = 0;
};

/**
 * Global function node
 */
class GlobalFuncNode : public FuncNode {
 protected:
  string m_name;                // function name
  vector<VarNode> m_paramList;  // param list
  DataTypeNode* m_retType;      // return type
  SyntaxNode* m_body;           // function body
  bool m_hasRet;                // has return node in body

 public:
  GlobalFuncNode(const string& name = "", DataTypeNode* retType = NULL,
                 SyntaxNode* body = NULL)
      : m_name(name), m_retType(retType), m_body(body), m_hasRet(false) {}

  virtual const string& getName() { return m_name; }
  virtual void setName(const string& name) { m_name = name; }

  virtual void setRetType(DataTypeNode* retType) { m_retType = retType; }
  virtual DataTypeNode* getRetType() { return m_retType; }

  virtual void setBody(SyntaxNode* body) { m_body = body; }
  virtual SyntaxNode* getBody() { return m_body; }

  virtual void addParam(const VarNode& param);

  virtual void setParamList(vector<VarNode>& paramList) {
    m_paramList = paramList;
  }
  virtual vector<VarNode>& getParamList() { return m_paramList; }

  virtual bool hasReturn() { return m_hasRet; }
  virtual void setReturn(bool hasRet) { m_hasRet = hasRet; }

  void accept(Visitor& visitor);

  bool matchParamsType(vector<DataTypeNode*>& paramsType);

  virtual bool equals(const string& name, vector<DataTypeNode*>& paramsType);
  virtual bool equals(const FuncNode& funcNode);

  virtual void getParamsType(vector<DataTypeNode*>& paramsType);

  virtual FuncType getFuncType() { return FUNC_GLOBAL; }
  string toString();
};

/**
 * ClassFuncNode is class member function, a decorator of another function node
 *
 */
class ClassFuncNode : public FuncNode {
 private:
  FuncNode* m_func;    // the function node
  ClassNode* m_class;  // the class it belongs to
 public:
  /**
   * Create a ClassFuncNode decorate another function node
   *
   * @classNode the class it belongs to
   * @funcNode  the decorated function node
   */
  ClassFuncNode(ClassNode* classNode, FuncNode* funcNode)
      : m_func(funcNode), m_class(classNode) {
    assert(funcNode);
    assert(classNode);
  }

  FuncNode* getFuncNode() { return m_func; }

  void setFuncNode(FuncNode* funcNode) { m_func = funcNode; }

  void accept(Visitor& visitor);

  virtual const string& getName() { return m_func->getName(); }
  virtual void setName(const string& name) { m_func->setName(name); }

  virtual void setRetType(DataTypeNode* retType) {
    m_func->setRetType(retType);
  };
  virtual DataTypeNode* getRetType() { return m_func->getRetType(); }

  virtual void setBody(SyntaxNode* body) { m_func->setBody(body); }
  virtual SyntaxNode* getBody() { return m_func->getBody(); }

  virtual void setParamList(vector<VarNode>& paramList) {
    m_func->setParamList(paramList);
  }
  virtual vector<VarNode>& getParamList() { return m_func->getParamList(); }

  virtual void addParam(const VarNode& param) { m_func->addParam(param); }

  virtual bool hasReturn() { return m_func->hasReturn(); }

  virtual void setReturn(bool hasRet) { m_func->setReturn(hasRet); }

  virtual bool equals(const FuncNode& funcNode);

  virtual bool equals(const string& funcName,
                      vector<DataTypeNode*>& paramsType) {
    return m_func->equals(funcName, paramsType);
  }

  virtual void getParamsType(vector<DataTypeNode*>& paramsType) {
    m_func->getParamsType(paramsType);
  }

  virtual FuncType getFuncType() { return FUNC_CLASS; }

  ClassNode* getClassNode() { return m_class; }

  void setClassNode(ClassNode* classNode) { m_class = classNode; }
};

class ReturnNode : public SyntaxNode {
 private:
  ExpNode* m_exp;

 public:
  ReturnNode(ExpNode* exp = NULL) : m_exp(exp) {}
  DataTypeNode* getRetType();
  ExpNode* getExpNode() { return m_exp; }
  void accept(Visitor& visitor);
};

class CallNode : public ExpNode {
 protected:
  vector<ExpNode*> m_paramList;
  string m_funcName;
  FuncNode* m_func;
  string m_callerName;
  VarNode* m_caller;
  bool m_memberFuncHint;  // hint that this is a member functiuon call

 public:
  CallNode() : m_func(NULL), m_caller(NULL), m_memberFuncHint(false) {}
  ~CallNode();

  void setFuncName(const string& funcName) { m_funcName = funcName; }
  string& getFuncName() { return m_funcName; }

  void setFuncNode(FuncNode* func) { m_func = func; }
  FuncNode* getFuncNode() { return m_func; }

  void addParam(ExpNode* exp);
  void accept(Visitor& visitor);

  void getParamsType(vector<DataTypeNode*>& paramsType);  // paramsType is
                                                          // output

  void setMemberFuncHint(bool hint) { m_memberFuncHint = hint; }
  bool getMemberFuncHint() { return m_memberFuncHint; }

  void setCallerName(const string& name) { m_callerName = name; }
  string& getCallerName() { return m_callerName; }

  void setCaller(VarNode* caller) { m_caller = caller; }
  VarNode* getCaller() { return m_caller; }

  string toString();
};

#endif
