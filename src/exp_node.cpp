#include <iostream>

#include "exp_node.h"
#include "visitor.h"

using namespace std;

/*********************************************
 *                 ExpNode 
 *********************************************/

bool ExpNode::matchType( ExpNode* expNode ) { 
   if( NULL == expNode )
       return false;
   return m_dataTypeNode->isEqual(expNode->getDataTypeNode()); 
}

bool ExpNode::matchType( DataTypeNode* dtypeNode ){
    if( NULL == dtypeNode )
        return false;
    return m_dataTypeNode->isEqual( dtypeNode );

}

void ExpNode::accept( Visitor& visitor ){
	
}

/*********************************************
 *                 VarNode 
 *********************************************/
void VarNode::accept( Visitor& visitor) {
	visitor.doVarNode(this);

}

void VarRefNode::accept( Visitor& visitor) {
	visitor.doVarRefNode(this);

}


/*********************************************
 *                  OpNode 
 *********************************************/
void OpNode::accept( Visitor& visitor ){
	
	if( m_leftOpnd )
		m_leftOpnd->accept( visitor );
	if( m_rightOpnd)
		m_rightOpnd->accept( visitor );
	
	visitor.doOpNode( this );
}

const char* OpNode::getOpStr(){

    static const char* opStrs[] = {
        "+","-","*","/","==", "!=", ">", ">=", "<", "<=", "and","or", "!"
    };

    return opStrs[m_op];
    
}

string OpNode::toString() {
    string retStr;

    retStr.append( "(" );
    if( hasLeftOpnd() ) 
        retStr.append( m_leftOpnd->toString() );
    
    retStr.append( " " );
    retStr.append( getOpStr() );
    retStr.append( " " );

    if( hasRightOpnd() )
        retStr.append( m_rightOpnd->toString() );
    retStr.append( ")" );
    return retStr;
}

/*********************************************
 *                 AssignNode 
 *********************************************/
void AssignNode::accept( Visitor& visitor ){
    
    if( m_var )
	    m_var->accept( visitor );
    if( m_exp )
	    m_exp->accept( visitor );

	visitor.doAssignNode(this);
}

void AddNode::accept( Visitor& visitor) {

    assert( m_leftOpnd );
    assert( m_rightOpnd );

    m_leftOpnd->accept( visitor );
    m_rightOpnd->accept( visitor );

	visitor.doAddNode(this);

}


void SubNode::accept( Visitor& visitor ){

    assert( m_leftOpnd );
    assert( m_rightOpnd );

    m_leftOpnd->accept( visitor );
    m_rightOpnd->accept( visitor );

	visitor.doSubNode(this);
}

void MulNode::accept( Visitor& visitor ){

    assert( m_leftOpnd );
    assert( m_rightOpnd );

    m_leftOpnd->accept( visitor );
    m_rightOpnd->accept( visitor );

	visitor.doMulNode(this);
}
void DivNode::accept( Visitor& visitor ){

    assert( m_leftOpnd );
    assert( m_rightOpnd );

    m_leftOpnd->accept( visitor );
    m_rightOpnd->accept( visitor );

	visitor.doDivNode(this);
}


void AndNode::accept( Visitor& visitor ){

    assert( m_leftOpnd );
    assert( m_rightOpnd );
    
    m_leftOpnd->accept( visitor );
    m_rightOpnd->accept( visitor );

    visitor.doAndNode( this );

}

NewNode::~NewNode() {
   /* if( getDataTypeNode() && ! getDataTypeNode()->isSingleton()) 
        delete getDataTypeNode();
   */
}


void NewNode::accept( Visitor& visitor ) {
    visitor.doNewNode( this );
}
