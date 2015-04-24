#ifndef FUNC_NODE_H
#define FUNC_NODE_H

#include <string>
#include <vector>

#include <boost/ptr_container/ptr_vector.hpp>

#include "syntax_tree/data_type_node.h"
#include "syntax_tree/exp_node.h"
#include "syntax_tree/stmt_node.h"
#include "syntax_tree/var_declaration_node.h"

namespace flang {

class FuncNode : public StmtNode {
 public:
  FuncNode() : StmtNode(ASTNode::FUNC_NODE) {}
  ~FuncNode() override {}

  const std::string& getName() { return name_; }
  void setName(const std::string& name) { name_ = name; }

  ASTNode* getBody() { return body_.get(); }
  void setBody(ASTNode* body) { body_.reset(body); }

  boost::ptr_vector<VarDeclarationNode>& getParamList() { return param_list_; }
  void addParameter(VarDeclarationNode* param) { param_list_.push_back(param); }

  DataTypeNode* getReturnType() { return return_type_.get(); }
  void setReturnType(DataTypeNode* type) { return_type_.reset(type); }

  void accept(ASTVisitor* visitor) override;

 private:
  std::string name_;
  boost::ptr_vector<VarDeclarationNode> param_list_;
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
  }
  void accept(ASTVisitor* visitor) override;

 private:
  std::unique_ptr<ExpNode> expression_;
};

class CallNode : public ExpNode {
 public:
  CallNode(const std::string& name = "");
  ~CallNode() override {}

  void accept(ASTVisitor* visitor) override;

  void setName(const std::string& name) { name_ = name; }
  const std::string& getName() { return name_; }

  void addParameter(ExpNode* param) { param_list_.push_back(param); }
  boost::ptr_vector<ExpNode>& getParamList() { return param_list_; }

 private:
  boost::ptr_vector<ExpNode> param_list_;
  std::string name_;
};

}  // namespace flang

#endif
