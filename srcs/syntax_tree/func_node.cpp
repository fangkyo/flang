#include "base/stl_utils.h"
#include "syntax_tree/func_node.h"

namespace flang {

void ParamListNode::addParameter(ExpNode* param) {
  param->setParent(this);
  param_list_.push_back(param);
}

bool ParamListNode::getChildNodes(ASTNodeList* child_nodes) {
  return ptrVectorToVector(param_list_, child_nodes);
}


bool ParamDeclListNode::getChildNodes(ASTNodeList* child_nodes) {
  return ptrVectorToVector(decl_list_, child_nodes);
}


bool FuncNode::getChildNodes(ASTNodeList* child_nodes) {
  CHECK(param_decl_list_);
  child_nodes->push_back(param_decl_list_.get());
  CHECK(return_type_);
  child_nodes->push_back(return_type_.get());
  CHECK(body_);
  child_nodes->push_back(body_.get());
  return true;
}

ReturnNode::ReturnNode() {}

ReturnNode::ReturnNode(ExpNode* exp_node) {
  setExpression(exp_node);
}

bool ReturnNode::getChildNodes(ASTNodeList* child_nodes) {
  CHECK(expression_);
  child_nodes->push_back(expression_.get());
  return true;
}

bool CallNode::getChildNodes(ASTNodeList* child_nodes) {
  CHECK(caller_);
  child_nodes->push_back(caller_.get());
  CHECK(param_list_);
  child_nodes->push_back(param_list_.get());
  CHECK(name_);
  child_nodes->push_back(name_.get());
  return true;
}

}  // namespace flang
