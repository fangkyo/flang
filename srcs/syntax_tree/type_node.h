#ifndef DATA_TYPE_H
#define DATA_TYPE_H

#include <memory>
#include <string>

#include "syntax_tree/ast_node.h"
#include "syntax_tree/name_node.h"

namespace flang {

class TypeNode : public ASTNode {
 INHERIT_AST_NODE(TypeNode, ASTNode, TYPE_NODE)

 public:
  ~TypeNode() override {}

  virtual bool isPrimitive() { return true; }
};

class Int32TypeNode : public TypeNode {
 INHERIT_AST_NODE(Int32TypeNode, TypeNode, INT32_TYPE_NODE)
 public:
  Int32TypeNode() {}
  ~Int32TypeNode() override {}
};

class Int64TypeNode : public TypeNode {
 INHERIT_AST_NODE(Int32TypeNode, TypeNode, INT64_TYPE_NODE)
 public:
  Int64TypeNode() {}
  ~Int64TypeNode() override {}
};

class CharTypeNode : public TypeNode {
 INHERIT_AST_NODE(Int32TypeNode, TypeNode, CHAR_TYPE_NODE)
 public:
  CharTypeNode() {}
  ~CharTypeNode() override {}

};

class BoolTypeNode : public TypeNode {
 INHERIT_AST_NODE(Int32TypeNode, TypeNode, BOOL_TYPE_NODE)
 public:
  BoolTypeNode() {}
  ~BoolTypeNode() override {}
};

class StringTypeNode : public TypeNode {
 INHERIT_AST_NODE(Int32TypeNode, TypeNode, STRING_TYPE_NODE)
 public:
  StringTypeNode() {}
  ~StringTypeNode() override {}
};

class VoidTypeNode : public TypeNode {
 INHERIT_AST_NODE(Int32TypeNode, TypeNode, VOID_TYPE_NODE)
 public:
  VoidTypeNode() {}
  ~VoidTypeNode() override {}
};

class DoubleTypeNode : public TypeNode {
 INHERIT_AST_NODE(Int32TypeNode, TypeNode, DOUBLE_TYPE_NODE)
 public:
  DoubleTypeNode() {}
  ~DoubleTypeNode() override {}
};

// User defined type node, such as class and enum.
class UserDefTypeNode : public TypeNode {
 INHERIT_AST_NODE(UserDefTypeNode, TypeNode, USER_DEF_TYPE_NODE)

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
