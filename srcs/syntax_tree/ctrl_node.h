#ifndef CTRL_NODE_H
#define CTRL_NODE_H

#include <cassert>

#include "syntax_tree.h"
#include "exp_node.h"

class IfNode : public SyntaxNode {

    public:
        ExpNode*  m_test;
        SyntaxNode*  m_if;
        SyntaxNode*  m_else;
        
        IfNode( ExpNode* testPart, SyntaxNode* ifPart = NULL, SyntaxNode* elsePart = NULL ) 
        : m_test( testPart ), m_if( ifPart), m_else( elsePart )
        { assert( testPart );  }

        void setTest( ExpNode* testPart )    { assert( testPart ); m_test = testPart; }
        void setIf( SyntaxNode* ifPart )     { m_if = ifPart;  }
        void setElse( SyntaxNode* elsePart ) { m_else = elsePart; }

        ExpNode* getTest()    { return m_test; }
        SyntaxNode* getIf()   { return m_if; }
        SyntaxNode* getElse() { return m_else; }

        void accept( Visitor& visitor );

};

class WhileNode : public SyntaxNode {
    public: 
        ExpNode* m_test;
        SyntaxNode* m_body;

        WhileNode( ExpNode* test , SyntaxNode* body = NULL ) 
        : m_test( test ), m_body( body ) { 
            assert(m_test); 
        }

        void setTest( ExpNode* testPart )    { assert( testPart ); m_test = testPart; }
        ExpNode* getTest()    { return m_test; }

        void setBody( SyntaxNode* body )     { m_body = body;  }
        SyntaxNode* getBody() { return m_body; }

        void accept( Visitor& visitor );
};


class BreakNode : public SyntaxNode {
    private:
        WhileNode* m_while;
    public:
        BreakNode() : m_while( NULL ) {}

        void setWhileNode( WhileNode* whileNode ) { m_while = whileNode; }
        WhileNode* getWhileNode() { return m_while; }

        void accept( Visitor& visitor );
};


#endif
