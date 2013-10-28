#include <cstring>
#include <iostream>

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
/*
	for( list<SyntaxNode*>::iterator iter = m_stmtList.begin();
	     iter != m_stmtList.end();
		 ++iter ){
	
		delete *iter;
	}
*/
}

void StmtListNode::addStmt( SyntaxNode* stmt ) {

	if( stmt == NULL ) 
		return;
	m_stmtList.push_back( stmt );
}

void StmtListNode::accept( Visitor& visitor ) {

	visitor.doStmtListNode(this);

	for( list<SyntaxNode*>::iterator iter = m_stmtList.begin();
	     iter != m_stmtList.end();
		 ++iter){
		(*iter)->accept( visitor );
	}
	
}


SyntaxNodeCollector::SyntaxNodeCollector() {
}

SyntaxNodeCollector::~SyntaxNodeCollector() {

    set<SyntaxNode*>::iterator iter = m_nodes.begin();
    while( iter != m_nodes.end() ){
        if( *iter )
            delete *iter;
        ++iter;
    }
}

void SyntaxNodeCollector::insert( SyntaxNode* node ) {
    if( node ) 
        m_nodes.insert(node);
}

void SyntaxNodeCollector::remove( SyntaxNode* node ) {
    if( node ) 
        m_nodes.erase( node );
}

void SyntaxNodeCollector::collect( SyntaxNode* node ) {
    if( node ) {
        m_nodes.erase( node );
        delete node;
    }
}

SyntaxNodeCollector g_collector;
