#ifndef FUNC_NODE_H
#define FUNC_NODE_H

#include <string>
#include <vector>

#include <boost/ptr_container/ptr_vector.hpp>

#include "syntax_tree/data_type_node.h"
#include "syntax_tree/exp_node.h"
#include "syntax_tree/stmt_node.h"
#include "syntax_tree/var_decl_node.h"
#include "syntax_tree/name_node.h"

namespace flang {

class FuncNode : public StmtNode {
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

  boost::ptr_vector<VarDeclarationNode>& getParameters() { return parameters_; }
  void addParameter(VarDeclarationNode* param) {
    parameters_.push_back(param);
    param->setParent(this);
  }

  DataTypeNode* getReturnType() { return return_type_.get(); }
  void setReturnType(DataTypeNode* type) {
    return_type_.reset(type);
    return_type_->setParent(this);
  }

  void accept(ASTVisitor* visitor) override;

 private:
  std::string name_;
  boost::ptr_vector<VarDeclarationNode> parameters_;
  std::unique_ptr<DataTypeNode> return_type_;
  std::unique_ptr<ASTNode> body_;
};

class ReturnNode : public StmtNode {
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
  void accept(ASTVisitor* visitor) override;

 private:
  std::unique_ptr<ExpNode> expression_;
};

class CallNode : public ExpNode {
 public:
  CallNode();
  ~CallNode() override {}

  void accept(ASTVisitor* visitor) override;

  void setName(NameNode* name) {
    name_.reset(name);
    name_->setParent(this);
  }
  NameNode* getName() const { return name_.get(); }

  void addParameter(ExpNode* param) {
    parameters_.push_back(param);
    param->setParent(this);
  }
  boost::ptr_vector<ExpNode>& getParameters() { return parameters_; }

 private:
  boost::ptr_vector<ExpNode> parameters_;
  std::unique_ptr<NameNode> name_;
};

}  // namespace flang

#endif
