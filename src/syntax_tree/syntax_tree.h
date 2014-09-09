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
