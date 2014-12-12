#include "ctrl_node.h"
#include "visitor.h"

void IfNode::accept( Visitor& visitor ){

    visitor.doIfNode( this );
}





void WhileNode::accept( Visitor& visitor ){

   visitor.doWhileNode( this );
}

void BreakNode::accept( Visitor& visitor ){

   visitor.doBreakNode( this );
}
