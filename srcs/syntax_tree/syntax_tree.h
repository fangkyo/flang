#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include <string>
#include <list>
#include <set>

#include "base/check.h"

using namespace std;

enum DataType {
  TYPE_INT,     // int
  TYPE_BOOL,    // bool
  TYPE_CHAR,    // char
  TYPE_STRING,  // string
  TYPE_CLASS,   // class
  TYPE_VOID,    // void
  TYPE_UNDEF    // undefined
};

const char* dataTypeStr(DataType);

enum OpType {
  OP_ADD,
  OP_SUB,
  OP_MUL,
  OP_DIV,
  OP_EQ,
  OP_NE,
  OP_GT,
  OP_GE,
  OP_LT,
  OP_LE,
  OP_AND,
  OP_OR,
  OP_NOT
};

// Abstract syntax tree visitor
class ASTVisitor;
class Visitor;

typedef class SyntaxTree {
 public:
  int m_lineNum;

  SyntaxTree() : m_lineNum(0) {}
  virtual ~SyntaxTree() {}

  void setLineNum(int lineNum) { m_lineNum = lineNum; }
  int getLineNum() { return m_lineNum; }

  virtual void print() {}
  virtual void accept(Visitor& visitor) {};
  virtual string toString() { return string(""); }

} SyntaxNode;

// This class is abstract syntax tree node, which is the baseclass
// for all the concret syntax tree nodes.
class ASTNode {
 public:
  enum ASTNodeType {
    PROGRAM_NODE, // Program node
    STMT_NODE, // Statement node
    FUNC_NODE, // Function definition node
    CLASS_NODE, // Class definition node
    BLOCK_NODE, // Code block node
    EXP_STMT_NODE, // Expression statement node
    IF_STMT_NODE, // If statement node
    WHILE_STMT_NODE, // While statement node
    EMPTY_STMT_NODE, // Empty statement node
    RETURN_STMT_NODE, // Return statement node
    EXP_NODE, // Expression node
    ASSIGNMENT_NODE, // Assignment node
    INFIX_EXP_NODE, // Infix Expression node
    PREFIX_EXP_NODE, // Prefix expression node
    PARENTHESIZED_EXP_NODE, // Parenthesized expression node
    PRIMITIVE_NODE, // Primitive node
    INTEGER_NODE, // Integer node
    STRING_NODE, // String node
    FLOAT_NODE, // Float node
    CHAR_NODE, // Char node
    BOOL_NODE, // Bool node
    NAME_NODE, // Name node
    NULL_NODE, // Null node
    SIMPLE_NAME_NODE, // Simple name node
    FUNC_INVOCATION_NODE, // Function invocation node
    QUALIFIED_NAME_NODE, // Qualified name node
  };

  ASTNode(ASTNodeType node_type) :
      node_type_(node_type), parent_(nullptr) {}
  virtual ~ASTNode(){}
  virtual void accept(ASTVisitor* visitor) = 0;
  ASTNodeType nodeType() { return node_type_; }
  // Accessor for parent
  void setParent(ASTNode* parent) { parent_ = parent; }
  ASTNode* parent() { return parent_; }

 protected:
  ASTNodeType node_type_;
  ASTNode* parent_;
};

class StmtListNode : public SyntaxNode {
 public:
  list<SyntaxNode*> m_stmtList;

  ~StmtListNode();
  void addStmt(SyntaxNode* stmt);
  void accept(Visitor& visitor);
};

class SyntaxNodeCollector {
 private:
  set<SyntaxNode*> m_nodes;

 public:
  SyntaxNodeCollector();
  ~SyntaxNodeCollector();

  void insert(SyntaxNode* node);
  void remove(SyntaxNode* node);
  void collect(SyntaxNode* node);
};

extern SyntaxNodeCollector g_collector;

#endif
