#ifndef DATA_TYPE_H
#define DATA_TYPE_H

#include <memory>
#include <string>

#include "syntax_tree/ast_node.h"

namespace flang {

class DataTypeNode : public ASTNode {
 public:
  DataTypeNode(ASTNode::ASTNodeType node_type) : ASTNode(node_type) {}
  ~DataTypeNode() override {}

  virtual bool isPrimitive() { return true; }
};

class Int32TypeNode : public DataTypeNode {
 public:
  Int32TypeNode() : DataTypeNode(ASTNode::INT32_TYPE_NODE) {}
  ~Int32TypeNode() override {}
};

class Int64TypeNode : public DataTypeNode {
 public:
  Int64TypeNode() : DataTypeNode(ASTNode::INT64_TYPE_NODE) {}
  ~Int64TypeNode() override {}
};

class CharTypeNode : public DataTypeNode {
 public:
  CharTypeNode() : DataTypeNode(ASTNode::CHAR_TYPE_NODE) {}
  ~CharTypeNode() override {}

};

class BoolTypeNode : public DataTypeNode {
 public:
  BoolTypeNode() : DataTypeNode(ASTNode::BOOL_TYPE_NODE) {}
  ~BoolTypeNode() override {}
};

class StringTypeNode : public DataTypeNode {
 public:
  StringTypeNode() : DataTypeNode(ASTNode::STRING_TYPE_NODE) {}
  ~StringTypeNode() override {}
};

class VoidTypeNode : public DataTypeNode {
 public:
  VoidTypeNode() : DataTypeNode(ASTNode::VOID_TYPE_NODE) {}
  ~VoidTypeNode() override {}
};

class SimpleTypeNode : public DataTypeNode {
 public:
  SimpleTypeNode(const std::string& name);
  ~SimpleTypeNode() override {}

  const std::string& getName() { return name_; }
  void setName(const std::string& name) { name_ = name; }

 private:
  std::string name_;
};

// DataType.SimpleName
class QualifiedTypeNode : public DataTypeNode {
 public:
  QualifiedTypeNode(DataTypeNode* data_type_node, const std::string& name);
  ~QualifiedTypeNode() override {}

  std::string& name() { return name_; }
  void setName(std::string& name) { name_ = name; }

  DataTypeNode* getQualifier() { return qualifier_.get(); }
  void setQualifier(DataTypeNode* qualifier) { qualifier_.reset(qualifier); }

  void accept(ASTVisitor* visitor) override;

 private:
  std::string name_;
  std::unique_ptr<DataTypeNode> qualifier_;
};

class ArrayTypeNode : public DataTypeNode {
 public:
  ArrayTypeNode(DataTypeNode* data_type_node);
  ~ArrayTypeNode() override {}

  DataTypeNode* dataTypeNode() { return data_type_node_.get(); }
  void setDataTypeNode(DataTypeNode* data_type_node) {
    data_type_node_.reset(data_type_node);
  }
 private:
  std::unique_ptr<DataTypeNode> data_type_node_;
};

}  // namespace std

#endif
