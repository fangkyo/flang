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
  bool isConst() override { return true; }

 protected:
  PrimitiveNode(const T& value, ASTNodeType node_type, ASTNode* parent) :
      ExpNode(node_type, parent), value_(value) {}
  T value_;
};

// 32 bits integer value node
class IntValNode : public PrimitiveNode<int32_t> {
 public:
  IntValNode(int32_t value, ASTNode* parent) :
      PrimitiveNode(value, ASTNode::INTEGER_NODE, parent) {}
};

// String value node
class StringValNode : public PrimitiveNode<std::string> {
 public:
  StringValNode(const string& value, ASTNode* parent) :
      PrimitiveNode(value, ASTNode::STRING_VAL_NODE, parent) {}
};

// Bool value node. The value can only be 'true' or 'false'.
class BoolValNode : public PrimitiveNode<bool> {
 public:
  BoolValNode(bool value, ASTNodeType* parent) :
      PrimitiveNode(value, ASTNode::BOOL_VAL_NODE, parent) {}
};

// Char value node.
class CharValNode : public PrimitiveNode<char> {
 public:
  CharValNode(char value) :  {
      PrimitiveNode(value, ASTNode::CHAR_VAL_NODE, parent) {}
};

// Float value node
class FloatValNode : public PrimitiveNode<float> {
 public:
  CharValNode(float value) :  {
      PrimitiveNode(value, ASTNode::FLOAT_VAL_NODE, parent) {}
};

}  // namespace flang

#endif
