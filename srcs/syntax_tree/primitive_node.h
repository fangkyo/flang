#ifndef PRIMITIVE_NODE_H_
#define PRIMITIVE_NODE_H_

#include <cstdint>

#include "syntax_tree/exp_node.h"

namespace flang {

// The base class of primitive value node (e.g. string, int, etc.).
template <class T>
class PrimitiveNode : public ExpNode {
 INHERIT_AST_NODE(PrimitiveNode, ExpNode, PRIMITIVE_NODE)

 public:
  void setValue(const T& value) { value_ = value; }
  const T& value() { return value_; }

 protected:
  PrimitiveNode(const T& value) : value_(value) {}
  T value_;
};

// 32 bits integer value node
class IntValNode : public PrimitiveNode<int64_t> {
 INHERIT_AST_NODE(IntValNode, PrimitiveNode<int64_t>, INT_VAL_NODE)
 public:
  IntValNode(int64_t value) : PrimitiveNode(value) {}
};

// 64 bits integer value node
// class Int64ValNode : public PrimitiveNode<int64_t> {
 // INHERIT_AST_NODE(Int64ValNode, PrimitiveNode<int64_t>)
 // public:
  // Int64ValNode(int64_t value) :
      // PrimitiveNode(value, ASTNode::INT_VAL_NODE) {}
// };

// String value node
class StringValNode : public PrimitiveNode<std::string> {
 INHERIT_AST_NODE(StringValNode, PrimitiveNode<std::string>, STRING_VAL_NODE)
 public:
  StringValNode(const std::string& value) :
      PrimitiveNode(value) {}
};

// Bool value node. The value can only be 'true' or 'false'.
class BoolValNode : public PrimitiveNode<bool> {
 INHERIT_AST_NODE(BoolValNode, PrimitiveNode<bool>, BOOL_VAL_NODE)
 public:
  BoolValNode(bool value) :
      PrimitiveNode(value) {}
};

// Char value node.
class CharValNode : public PrimitiveNode<char> {
 INHERIT_AST_NODE(CharValNode, PrimitiveNode<char>, CHAR_VAL_NODE)
 public:
  CharValNode(char value) :
      PrimitiveNode(value) {}
};

// Float value node
class DoubleValNode : public PrimitiveNode<double> {
 INHERIT_AST_NODE(DoubleValNode, PrimitiveNode<double>, DOUBLE_VAL_NODE)
 public:
  DoubleValNode(double value) :
      PrimitiveNode(value) {}
};

}  // namespace flang

#endif
