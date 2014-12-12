#include "print_node.h"
#include "visitor.h"

/*********************************************
 *                 PrintNode 
 *********************************************/
void PrintNode::accept( Visitor& visitor ) {
	
	if( m_exp ) 
		m_exp->accept( visitor );
	visitor.doPrintNode( this );
}

