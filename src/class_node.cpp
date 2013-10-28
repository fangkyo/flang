#include <unordered_map>

#include "class_node.h"
#include "visitor.h"
#include "error.h"

using namespace std;

ClassNode::~ClassNode() {

}

void ClassNode::setParent( ClassNode* parent ) {
    if( NULL == parent ) {
        m_parentName.clear();
    }
    
    m_parent = parent;
}

void ClassNode::addVarDeclare( DeclareNode* declare ) {

    if( NULL != declare )
        m_varList.push_back( declare );
}

void ClassNode::addFuncion( ClassFuncNode* func ) {
    if( NULL != func ){
        // add function to the function list
        m_funcList.push_back( func );
    }
}

void ClassNode::accept( Visitor& visitor ){

    visitor.doClassNode( this );

}


void ClassNode::acceptVars( Visitor& visitor){

    for( int i=0; i < m_varList.size(); ++i ){
        if( m_varList[i] ) {
            
            // set every node 
            m_varList[i]->setVarClass( this );
            m_varList[i]->accept( visitor );
        }
    }

}


void ClassNode::acceptFuncs( Visitor& visitor, ScopeManager& scopeManager, ErrorEngine& errorEngine ){

    unordered_map<string, FuncNode*> funcMap;
    unordered_map<string, FuncNode*>::iterator iter;

    for( int i=0; i < m_funcList.size(); ++i ) {

        if( m_funcList[i] ){
            
            iter = funcMap.find( m_funcList[i]->getName() );
            if( iter != funcMap.end() ){
                FuncRedefinedError error( iter->second, m_funcList[i] );
                errorEngine.emitError( &error );
            }else{
                funcMap.insert( make_pair( m_funcList[i]->getName(), m_funcList[i] ) );
            }

            m_funcList[i]->accept( visitor );
        }
    }
   
}

ClassFuncNode* ClassNode::findMemberFunc( const string& funcName, vector<DataTypeNode*>& paramsType ){
    
    for( int i=0; i<m_funcList.size(); ++i ){

        if( m_funcList[i] )
            if( m_funcList[i]->equals( funcName, paramsType ) )
                return m_funcList[i];
    }
    
    if( m_parent ) 
        return m_parent->findMemberFunc( funcName, paramsType );
    else
        return NULL;

}

ClassFuncNode* ClassNode::findMemberFunc( const string& funcName ){

    for( int i=0; i<m_funcList.size(); ++i ){
        if( m_funcList[i] && m_funcList[i]->getName() == funcName )
            return m_funcList[i];
    }
    return NULL;
}

VarNode*  ClassNode::findMemberVar( const string& varName ){

    VarNode* varNode = NULL;

    for( int i=0; i<m_varList.size(); ++i ) {
        varNode = m_varList[i]->findVar( varName );
        if( varNode )
            return varNode;
    }

    if( m_parent )
        return m_parent->findMemberVar( varName );
    else
        return NULL;
}
