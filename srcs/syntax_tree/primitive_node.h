#ifndef PRIMITIVE_NODE_H_
#define PRIMITIVE_NODE_H_

#include <cstdint>

#include "syntax_tree/exp_node.h"

namespace flang {

// The base class of primitive value node (e.g. string, int, etc.).
template <class T>
class PrimitiveNode : public ExpNode {
 public:
  void setValue(const T& value) { value_ = value; }
  const T& value() { return value_; }

 protected:
  PrimitiveNode(const T& value, ASTNode::ASTNodeType node_type) :
      ExpNode(node_type), value_(value) {}
  T value_;
};

// 32 bits integer value node
class IntValNode : public PrimitiveNode<int32_t> {
 public:
  IntValNode(int32_t value) :
      PrimitiveNode(value, ASTNode::INT_VAL_NODE) {}
};

// String value node
class StringValNode : public PrimitiveNode<std::string> {
 public:
  StringValNode(const std::string& value) :
      PrimitiveNode(value, ASTNode::STRING_VAL_NODE) {}
};

// Bool value node. The value can only be 'true' or 'false'.
class BoolValNode : public PrimitiveNode<bool> {
 public:
  BoolValNode(bool value) :
      PrimitiveNode(value, ASTNode::BOOL_VAL_NODE) {}
};

// Char value node.
class CharValNode : public PrimitiveNode<char> {
 public:
  CharValNode(char value) :
      PrimitiveNode(value, ASTNode::CHAR_VAL_NODE) {}
};

// Float value node
class FloatValNode : public PrimitiveNode<float> {
 public:
  FloatValNode(float value) :
      PrimitiveNode(value, ASTNode::FLOAT_VAL_NODE) {}
};

}  // namespace flang

#endif
