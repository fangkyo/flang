#ifndef AST_NODE_H_
#define AST_NODE_H_

#include <cstdint>

#include "symbol_table/symbol.h"
#include "syntax_tree/ast_visitor.h"

namespace flang {

// Abstract syntax tree node class.
class ASTNode {
 public:
  // The type of ast nodes, which are the subclasses of ASTNode.
  enum ASTNodeType {
    PROGRAM_NODE, // Program node
    EMPTY_NODE, // Empty node
    VAR_DECL_NODE, // variable declaration node
    VAR_DECL_FRAGMENT_NODE, // variable declaration fragment node.
    STMT_NODE, // Statement node
    FUNC_NODE, // Function definition node
    CALL_NODE, // call function node
    CLASS_NODE, // Class definition node
    BLOCK_NODE, // Code block node
    IF_NODE, // If statement node
    WHILE_NODE, // While statement node
    BREAK_NODE, // break statement node
    RETURN_NODE, // Return statement node
    UNARY_EXP_NODE, // Unary expression node
    BINARY_EXP_NODE, // Binary expression node
    ASSIGN_EXP_NODE, // Assignment node
    NEW_EXP_NODE, // New expression node
    PRIMITIVE_NODE, // Primitive node
    INT_VAL_NODE, // Int value node
    STRING_VAL_NODE, // String value node
    FLOAT_VAL_NODE, // Float value node
    DOUBLE_VAL_NODE,
    CHAR_VAL_NODE, // Char value node
    BOOL_VAL_NODE, // Bool value node, 'true' or 'false'
    NAME_NODE, // Name node
    NULL_NODE, // Null node
    SIMPLE_NAME_NODE, // Simple name node
    QUALIFIED_NAME_NODE, // Qualified name node
    PRINT_NODE, // Print node
    VAR_NODE, // Variable node
    INT32_TYPE_NODE,
    INT64_TYPE_NODE,
    FLOAT_TYPE_NODE,
    DOUBLE_TYPE_NODE,
    CHAR_TYPE_NODE,
    STRING_TYPE_NODE,
    BOOL_TYPE_NODE,
    VOID_TYPE_NODE,
    COMPOSITE_TYPE_NODE,
    CLASS_TYPE_NODE,
    ARRAY_TYPE_NODE,
    REFERENCE_NODE,
  };

  ASTNode(ASTNodeType node_type) :
      node_type_(node_type), parent_(nullptr) {}

  virtual ~ASTNode() {}
  virtual void accept(ASTVisitor*) {}

  ASTNodeType getNodeType() const { return node_type_; }

  // Parent's accessor
  void setParent(ASTNode* parent) { parent_ = parent; }
  ASTNode* getParent() const { return parent_; }

  void setSymbol(Symbol* symbol) { symbol_.reset(symbol); }
  Symbol* getSymbol() const { return symbol_.get(); }

  // Lineno's accessor
  void setLineNum(int32_t line_num) { line_num_ = line_num; }
  int32_t getLineNum() const { return line_num_; }

 protected:
  ASTNodeType node_type_;
  ASTNode* parent_;
  std::unique_ptr<Symbol> symbol_;
  int32_t line_num_;
};

class EmptyNode : public ASTNode {
 public:
  EmptyNode() : ASTNode(ASTNode::EMPTY_NODE) {}
  ~EmptyNode() override {}
};

}  // namespace flang

#endif
