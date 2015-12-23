#ifndef FUNC_NODE_H_
#define FUNC_NODE_H_

#include <string>
#include <vector>

#include <boost/ptr_container/ptr_vector.hpp>

#include "syntax_tree/type_node.h"
#include "syntax_tree/exp_node.h"
#include "syntax_tree/stmt_node.h"
#include "syntax_tree/var_decl_node.h"
#include "syntax_tree/name_node.h"

namespace flang {

class ParamListNode : public ASTNode {
 INHERIT_AST_NODE(ParamListNode, ASTNode)
 public:
  ParamListNode() : ASTNode(ASTNode::PARAM_LIST_NODE) {}
  ~ParamListNode() override {}

  void addParameter(ExpNode* param);
  const boost::ptr_vector<ExpNode>& getParamList() const {
    return param_list_;
  }
 private:
  boost::ptr_vector<ExpNode> param_list_;
};

class ParamDeclListNode : public ASTNode {
 INHERIT_AST_NODE(ParamDeclListNode, ASTNode)
 public:
  ParamDeclListNode() : ASTNode(ASTNode::PARAM_DECL_LIST_NODE) {}

  void addDeclaration(VarDeclNode* decl) {
    decl->setParent(this);
    decl_list_.push_back(decl);
  }
  const boost::ptr_vector<VarDeclNode>& getDeclList() const {
    return decl_list_;
  }

 private:
  boost::ptr_vector<VarDeclNode> decl_list_;
} ;

class FuncNode : public StmtNode {
 INHERIT_AST_NODE(FuncNode, StmtNode)
 public:
  FuncNode() : StmtNode(ASTNode::FUNC_NODE) {}
  ~FuncNode() override {}

  const std::string& getName() { return name_; }
  void setName(const std::string& name) { name_ = name; }

  ASTNode* getBody() { return body_.get(); }
  void setBody(ASTNode* body) {
    body_.reset(body);
    body_->setParent(this);
  }

  // boost::ptr_vector<VarDeclNode>& getParameters() { return parameters_; }
  // void addParameter(VarDeclNode* param) {
    // parameters_.push_back(param);
    // param->setParent(this);
  // }

  void setParamDeclList(ParamDeclListNode* param_decl_list) {
    param_decl_list->setParent(this);
    param_decl_list_.reset(param_decl_list);
  }

  ParamDeclListNode* getParamDeclList() const {
    return param_decl_list_.get();
  }

  TypeNode* getReturnType() { return return_type_.get(); }
  void setReturnType(TypeNode* type) {
    return_type_.reset(type);
    return_type_->setParent(this);
  }

 protected:
  std::string name_;
  // boost::ptr_vector<VarDeclNode> parameters_;
  std::unique_ptr<ParamDeclListNode> param_decl_list_;
  std::unique_ptr<TypeNode> return_type_;
  std::unique_ptr<ASTNode> body_;
};

class ReturnNode : public StmtNode {
 INHERIT_AST_NODE(ReturnNode, StmtNode)
 public:
  ReturnNode(ExpNode* exp_node = nullptr);
  ~ReturnNode() override {}

  ExpNode* getExpression() { return expression_.get(); }
  void setExpression(ExpNode* exp_node) {
    expression_.reset(exp_node);
    if (expression_) {
      expression_->setParent(this);
    }
  }

 private:
  std::unique_ptr<ExpNode> expression_;
};

class CallNode : public ExpNode {
 INHERIT_AST_NODE(CallNode, ExpNode)
 public:
  CallNode();
  ~CallNode() override {}

  void setCaller(ExpNode* caller) {
    caller->setParent(this);
    caller_.reset(caller);
  }

  void setName(SimpleNameNode* name) {
    name->setParent(this);
    name_.reset(name);
  }

  SimpleNameNode* getName() {
    return name_.get();
  }

  void setParamList(ParamListNode* param_list) {
    param_list->setParent(this);
    param_list_.reset(param_list);
  }

  ParamListNode* getParamList() {
    return param_list_.get();
  }

  bool getChildNodes(ASTNodeList* child_nodes) override;

 private:
  std::unique_ptr<ParamListNode> param_list_;
  std::unique_ptr<ExpNode> caller_;
  std::unique_ptr<SimpleNameNode> name_;
};

}  // namespace flang

#endif
