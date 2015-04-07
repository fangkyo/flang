#include <cstring>
#include <iostream>

#include "ast_visitor/ast_visitor.h"
#include "base/check.h"
#include "base/utils.h"
#include "syntax_tree/syntax_tree.h"

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

void SyntaxTree::accept(ASTVisitor* visitor) {
  visitor->doProgramNode(root_.get());
}

//SyntaxNodeCollector::SyntaxNodeCollector() {
//}

//SyntaxNodeCollector::~SyntaxNodeCollector() {
  //stdDeleteElements(m_nodes);
//}

//void SyntaxNodeCollector::insert( SyntaxNode* node ) {
  //CHECK(node);
  //m_nodes.insert(node);
//}

//void SyntaxNodeCollector::remove( SyntaxNode* node ) {
  //CHECK(node);
  //m_nodes.erase( node );
//}

//void SyntaxNodeCollector::collect( SyntaxNode* node ) {
  //if( node ) {
    //m_nodes.erase( node );
    //delete node;
  //}
//}

//SyntaxNodeCollector g_collector;
