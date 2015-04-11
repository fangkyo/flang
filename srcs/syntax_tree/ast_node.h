#ifndef AST_NODE_H_
#define AST_NODE_H_

#include <cstdint>

#include "ast_visitor/ast_visitor.h"

namespace flang {

// Abstract syntax tree node class.
class ASTNode {
 public:
  // The type of ast nodes, which are the subclasses of ASTNode.
  enum ASTNodeType {
    PROGRAM_NODE, // Program node
    STMT_NODE, // Statement node
    FUNC_NODE, // Function definition node
    CALL_NODE, // call function node
    CLASS_NODE, // Class definition node
    BLOCK_NODE, // Code block node
    IF_NODE, // If statement node
    WHILE_NODE, // While statement node
    BREAK_NODE, // break statement node
    EMPTY_NODE, // Empty statement node
    RETURN_NODE, // Return statement node
    UNARY_EXP_NODE, // Unary expression node
    BINARY_EXP_NODE, // Binary expression node
    ASSIGN_EXP_NODE, // Assignment node
    NEW_EXP_NODE, // New expression node
    PARENTHESIZED_EXP_NODE, // Parenthesized expression node
    PRIMITIVE_NODE, // Primitive node
    INT_VAL_NODE, // Int value node
    STRING_VAL_NODE, // String value node
    FLOAT_VAL_NODE, // Float value node
    CHAR_VAL_NODE, // Char value node
    BOOL_VAL_NODE, // Bool value node, 'true' or 'false'
    NAME_NODE, // Name node
    NULL_NODE, // Null node
    SIMPLE_NAME_NODE, // Simple name node
    FUNC_INVOCATION_NODE, // Function invocation node
    QUALIFIED_NAME_NODE, // Qualified name node
    PRINT_NODE, // Print node
    VAR_NODE, // Variable node
    INT_TYPE_NODE,
    FLOAT_TYPE_NODE,
    CHAR_TYPE_NODE,
    STRING_TYPE_NODE,
    BOOL_TYPE_NODE,
    VOID_TYPE_NODE,
    COMPOSITE_TYPE_NODE,
    CLASS_TYPE_NODE,
    ARRAY_TYPE_NODE,
  };

  ASTNode(ASTNodeType node_type) :
      node_type_(node_type), parent_(nullptr) {}

  virtual ~ASTNode() {}
  virtual void accept(ASTVisitor*) = 0;

  // NodeType's getter
  ASTNodeType nodeType() { return node_type_; }

  // Parent's accessor
  void setParent(ASTNode* parent) { parent_ = parent; }
  ASTNode* parent() { return parent_; }

  // Lineno's accessor
  void setLineNum(int32_t line_num) { line_num_ = line_num; }
  int32_t lineNum() { return line_num_; }

 protected:
  ASTNodeType node_type_;
  ASTNode* parent_;
  int32_t line_num_;
};

}  // namespace flang

#endif
