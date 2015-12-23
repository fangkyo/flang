#ifndef DATA_TYPE_H
#define DATA_TYPE_H

#include <memory>
#include <string>

#include "syntax_tree/ast_node.h"
#include "syntax_tree/name_node.h"

namespace flang {

class TypeNode : public ASTNode {
 INHERIT_AST_NODE(TypeNode, ASTNode)

 public:
  TypeNode(ASTNode::ASTNodeType node_type) : ASTNode(node_type) {}
  ~TypeNode() override {}

  virtual bool isPrimitive() { return true; }
};

class Int32TypeNode : public TypeNode {
 public:
  Int32TypeNode() : TypeNode(ASTNode::INT32_TYPE_NODE) {}
  ~Int32TypeNode() override {}
};

class Int64TypeNode : public TypeNode {
 public:
  Int64TypeNode() : TypeNode(ASTNode::INT64_TYPE_NODE) {}
  ~Int64TypeNode() override {}
};

class CharTypeNode : public TypeNode {
 public:
  CharTypeNode() : TypeNode(ASTNode::CHAR_TYPE_NODE) {}
  ~CharTypeNode() override {}

};

class BoolTypeNode : public TypeNode {
 public:
  BoolTypeNode() : TypeNode(ASTNode::BOOL_TYPE_NODE) {}
  ~BoolTypeNode() override {}
};

class StringTypeNode : public TypeNode {
 public:
  StringTypeNode() : TypeNode(ASTNode::STRING_TYPE_NODE) {}
  ~StringTypeNode() override {}
};

class VoidTypeNode : public TypeNode {
 public:
  VoidTypeNode() : TypeNode(ASTNode::VOID_TYPE_NODE) {}
  ~VoidTypeNode() override {}
};

class DoubleTypeNode : public TypeNode {
 public:
  DoubleTypeNode() : TypeNode(ASTNode::DOUBLE_TYPE_NODE) {}
  ~DoubleTypeNode() override {}
};

// User defined type node, such as class and enum.
class UserDefTypeNode : public TypeNode {
 INHERIT_AST_NODE(UserDefTypeNode, TypeNode)

 public:
  explicit UserDefTypeNode(NameNode* name);
  ~UserDefTypeNode() override {}

  NameNode* getName() { return name_.get(); }
  void setName(NameNode* name) { name_.reset(name); }

  bool getChildNodes(ASTNodeList* child_nodes) override;

 private:
  std::unique_ptr<NameNode> name_;
};

//class ArrayTypeNode : public TypeNode {
 //public:
  //ArrayTypeNode(TypeNode* data_type_node);
  //~ArrayTypeNode() override {}

  //TypeNode* dataTypeNode() { return data_type_node_.get(); }
  //void setTypeNode(TypeNode* data_type_node) {
    //data_type_node_.reset(data_type_node);
  //}
 //private:
  //std::unique_ptr<TypeNode> data_type_node_;
//};

}  // namespace std

#endif
