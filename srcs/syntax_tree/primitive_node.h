#ifndef PRIMITIVE_NODE_H_
#define PRIMITIVE_NODE_H_

#include <cstdint>

#include "syntax_tree/exp_node.h"

namespace flang {

// The base class of primitive value node (e.g. string, int, etc.).
template <class T>
class PrimitiveNode : public ExpNode {
 INHERIT_AST_NODE(PrimitiveNode, ExpNode)

 public:
  void setValue(const T& value) { value_ = value; }
  const T& value() { return value_; }

 protected:
  PrimitiveNode(const T& value, ASTNode::ASTNodeType node_type) :
      ExpNode(node_type), value_(value) {}
  T value_;
};

// 32 bits integer value node
class Int32ValNode : public PrimitiveNode<int32_t> {
 INHERIT_AST_NODE(Int32ValNode, PrimitiveNode<int32_t>)
 public:
  Int32ValNode(int32_t value) :
      PrimitiveNode(value, ASTNode::INT_VAL_NODE) {}
};

// 64 bits integer value node
class Int64ValNode : public PrimitiveNode<int64_t> {
 INHERIT_AST_NODE(Int64ValNode, PrimitiveNode<int64_t>)
 public:
  Int64ValNode(int64_t value) :
      PrimitiveNode(value, ASTNode::INT_VAL_NODE) {}
};

// String value node
class StringValNode : public PrimitiveNode<std::string> {
 INHERIT_AST_NODE(StringValNode, PrimitiveNode<std::string>)
 public:
  StringValNode(const std::string& value) :
      PrimitiveNode(value, ASTNode::STRING_VAL_NODE) {}
  StringValNode(const char* str, uint32_t len) :
      PrimitiveNode(std::string(str, len), ASTNode::STRING_VAL_NODE) {}
};

// Bool value node. The value can only be 'true' or 'false'.
class BoolValNode : public PrimitiveNode<bool> {
 INHERIT_AST_NODE(BoolValNode, PrimitiveNode<bool>)
 public:
  BoolValNode(bool value) :
      PrimitiveNode(value, ASTNode::BOOL_VAL_NODE) {}
};

// Char value node.
class CharValNode : public PrimitiveNode<char> {
 INHERIT_AST_NODE(CharValNode, PrimitiveNode<char>)
 public:
  CharValNode(char value) :
      PrimitiveNode(value, ASTNode::CHAR_VAL_NODE) {}
};

// Float value node
class DoubleValNode : public PrimitiveNode<double> {
 INHERIT_AST_NODE(DoubleValNode, PrimitiveNode<double>)
 public:
  DoubleValNode(double value) :
      PrimitiveNode(value, ASTNode::DOUBLE_VAL_NODE) {}
};

}  // namespace flang

#endif
