#include <sstream>

#include "func_node.h"
#include "visitor.h"

using namespace std;


void GlobalFuncNode::addParam(const VarNode& param ) {
    m_paramList.push_back( param );
}

void GlobalFuncNode::accept( Visitor& visitor ) {
    visitor.doGlobalFuncNode( this );
}

bool GlobalFuncNode::matchParamsType( vector<DataTypeNode*>& paramsType ){
    if( paramsType.size() != m_paramList.size() )
        return false;
    
    for(size_t i=0; i< paramsType.size(); ++i ) {
        
        if( paramsType[i] == NULL && m_paramList[i].getDataTypeNode() == NULL )
            continue;
        else if( paramsType[i] == NULL || m_paramList[i].getDataTypeNode() == NULL )
            return false;
        else if( ! paramsType[i]->isEqual( m_paramList[i].getDataTypeNode() ) )
            return false;
    }

    return true;
}

bool GlobalFuncNode::equals( const string& name, vector<DataTypeNode*>& paramsType ){
    /*
    if( m_name != name )
        return false;
    return matchParamsType( paramsType );
    */
    return true;
}

bool GlobalFuncNode::equals( const FuncNode& funcNode ){
    return true;
}

void GlobalFuncNode::getParamsType( vector<DataTypeNode*>& paramsType ){
    
    paramsType.clear();
    for(size_t i=0; i< m_paramList.size(); ++i ){
        paramsType.push_back( m_paramList[i].getDataTypeNode() );
    }
}


string GlobalFuncNode::toString() {
    stringstream strStream;
    strStream << m_retType->toString() << " ( ";
    vector<DataTypeNode*> paramsType;
    getParamsType( paramsType );

    if( paramsType.size() > 0 ){
        
        strStream << paramsType[0]->toString();
        for(size_t i=1; i< paramsType.size(); ++i )
            strStream << ", "
                      << paramsType[i]->toString();
    }

    strStream << " )";
    return strStream.str();
}


void ClassFuncNode::accept( Visitor& visitor ){
    visitor.doClassFuncNode( this );
}

bool ClassFuncNode::equals( const FuncNode& funcNode ){
    return true;
}



DataTypeNode* ReturnNode::getRetType() {
    if( m_exp == NULL )
        return VOID_TYPE_NODE;
    else
        return m_exp->getDataTypeNode();
}

void ReturnNode::accept( Visitor& visitor ) {

    if( m_exp )
        m_exp->accept( visitor );
    visitor.doReturnNode(this);
}


CallNode::~CallNode() {

}

void CallNode::addParam( ExpNode* param ) {
    if( NULL == param )
        return;
    m_paramList.push_back( param );
}

void CallNode::accept( Visitor& visitor ){
    
    for(size_t i=0; i<m_paramList.size(); ++i )
        if( m_paramList[i] )
            m_paramList[i]->accept( visitor );

    visitor.doCallNode( this );
}

string CallNode::toString() {

   stringstream strStream;
   strStream << m_funcName ;
   strStream << "(";
   if( m_paramList.size() > 0 ) {
        strStream << " " << m_paramList[0]->toString();
        for(size_t i=1; i< m_paramList.size(); ++i )
            if( m_paramList[i] ){
                strStream << ", ";
                strStream << m_paramList[i]->toString();
            }
        strStream << " ";
   }  
   strStream << ")";

   return strStream.str();

}

void CallNode::getParamsType( vector<DataTypeNode*>& paramsType ){

    for(size_t i=0; i < m_paramList.size(); ++i )
        paramsType.push_back( m_paramList[i]->getDataTypeNode() );

}
/*
void MemberCallNode::accept( Visitor& visitor ) {
    visitor.doMemberCallNode( this );
}

void ThisCallNode::accept( Visitor& visitor ) {
    visitor.doThisCallNode( this );

}*/
