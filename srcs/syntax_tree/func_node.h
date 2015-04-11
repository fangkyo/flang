#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>
#include <vector>

#include <boost/ptr_container/ptr_vector.hpp>

#include "syntax_tree/data_type_node.h"
#include "syntax_tree/declare_node.h"
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
  // Add parameter for the function node
  void addParam(DeclareNode* param) { param_list_.push_back(param); }

  void accept(ASTVisitor* visitor) override;

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
  CallNode(const std::string& name);
  ~CallNode() override;

  void accept(ASTVisitor* visitor) override;

  void setName(const std::string& name) { name_ = name; }
  const std::string& name() { return name_; }

  void addParam(ExpNode* param) { param_list_.push_back(param); }
  boost::ptr_vector<ExpNode>& paramList() { return param_list_; }

 private:
  boost::ptr_vector<ExpNode> param_list_;
  std::string name_;
};

}  // namespace flang

#endif
