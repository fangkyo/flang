#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>
#include <vector>

#include <boost/ptr_container/ptr_vector.hpp>

#include "syntax_tree/data_type_node.h"
#include "syntax_tree/exp_node.h"
#include "syntax_tree/stmt_node.h"

namespace flang {

class FuncNode : public StmtNode {
 public:
  FuncNode() : StmtNode(ASTNode::FUNC_NODE) {}
  ~FuncNode() override {}

  const std::string& name() { return name_; }
  void setName(const std::string& name) { name_ = name; }

  ASTNode* body() { return body_.get(); }
  void setBody(ASTNode* body) { body_.reset(body); }

  boost::ptr_vector<DeclareNode>& paramList() { return param_list_; }
  void addParameter(DeclareNode* param) { param_list_.push_back(param); }

 private:
  std::string name_;
  boost::ptr_vector<DeclareNode> param_list_;
  std::unique_ptr<DataTypeNode> return_type_;
  std::unique_ptr<ASTNode> body_;
};

class ReturnNode : public StmtNode {
 public:
  ReturnNode(ExpNode* exp_returned);
  ~ReturnNode() override {}

  ExpNode* expReturned() { return exp_returned_.get(); }
  void setExpReturned(ExpNode* exp_returned) {
    exp_returned_.reset(exp_returned);
  }
  void accept(ASTVisitor* visitor) override;

 private:
  std::unique_ptr<ExpNode> exp_returned_;
};

class CallNode : public ExpNode {

 public:
  CallNode() : m_func(NULL), m_caller(NULL), m_memberFuncHint(false) {}
  ~CallNode();

  void accept(ASTVisitor* visitor) override;

  void setFuncName(const string& funcName) { m_funcName = funcName; }
  string& getFuncName() { return m_funcName; }

  void setFuncNode(FuncNode* func) { m_func = func; }
  FuncNode* getFuncNode() { return m_func; }

  void addParameter(ExpNode* parameter);

  void getParamsType(vector<DataTypeNode*>& paramsType);  // paramsType is
                                                          // output

  void setMemberFuncHint(bool hint) { m_memberFuncHint = hint; }
  bool getMemberFuncHint() { return m_memberFuncHint; }

  void setCallerName(const string& name) { m_callerName = name; }
  string& getCallerName() { return m_callerName; }

 protected:
  boost::ptr_vector<ExpNode> param_list_;
  std::string func_name_;
};

}  // namespace flang

#endif
