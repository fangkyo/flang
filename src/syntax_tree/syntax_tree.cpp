#include <cstring>
#include <iostream>

#include "common/check.h"
#include "common/utils.h"
#include "syntax_tree.h"
#include "visitor.h"

using namespace std;

const char* dataTypeStr( DataType dtype ){
  static const char* typeStr[] = {
    "int",
    "bool",
    "char",
    "string",
    "class",
    "void",
    "undefined"
  };
  return typeStr[dtype];
}

/*********************************************
 *               StmtListNode
 *********************************************/

StmtListNode::~StmtListNode() {
  stdDeleteElements(m_stmtList);
}

void StmtListNode::addStmt( SyntaxNode* stmt ) {
  CHECK(stmt);
  m_stmtList.push_back(stmt);
}

void StmtListNode::accept( Visitor& visitor ) {
  visitor.doStmtListNode(this);
  for (SyntaxNode* node : m_stmtList) {
    node->accept(visitor);
  }
}

SyntaxNodeCollector::SyntaxNodeCollector() {
}

SyntaxNodeCollector::~SyntaxNodeCollector() {
  stdDeleteElements(m_nodes);
}

void SyntaxNodeCollector::insert( SyntaxNode* node ) {
  CHECK(node);
  m_nodes.insert(node);
}

void SyntaxNodeCollector::remove( SyntaxNode* node ) {
  CHECK(node);
  m_nodes.erase( node );
}

void SyntaxNodeCollector::collect( SyntaxNode* node ) {
  if( node ) {
    m_nodes.erase( node );
    delete node;
  }
}

SyntaxNodeCollector g_collector;
