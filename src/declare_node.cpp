#include "declare_node.h"
#include "visitor.h"

/*********************************************
 *                 DeclareNode 
 *********************************************/
DeclareNode::~DeclareNode() {

}

void DeclareNode::accept( Visitor& visitor ){
	visitor.doDeclareNode(this);
}

VarNode* DeclareNode::findVar( const string& varName ){
    
    for( int i=0; i<m_varList.size(); ++i ) {
        if( m_varList[i]->getVarNode()->getName() == varName ) 
            return m_varList[i]->getVarNode();
    }
    return NULL;
}   

void DeclareNode::setVarClass( ClassNode* clazz ){
    for( int i=0; i<m_varList.size(); ++i ) {
        m_varList[i]->getVarNode()->setClass( clazz );
    }

}
