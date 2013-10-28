#ifndef VISITOR_H
#define VISITOR_H

#include "syntax_tree.h"
#include "exp_node.h"
#include "print_node.h"
#include "ctrl_node.h"
#include "func_node.h"
#include "class_node.h"
#include "declare_node.h"

class Visitor{
	public:
		virtual void doStmtListNode( StmtListNode* node ) = 0;
		virtual void doPrintNode( PrintNode* node ) = 0;
		virtual void doDeclareNode( DeclareNode* node ) = 0;
		virtual void doOpNode( OpNode* node ) = 0;
		virtual void doVarNode( VarNode* node ) = 0;
		virtual void doVarRefNode( VarRefNode* node ) = 0;

		virtual void doAndNode( AndNode* node ) = 0;

/*
		virtual void doOrNode( OrNode* node ) = 0;
		virtual void doNotNode( NotNode* node ) = 0;
*/
		virtual void doEqNode( EqNode* node ) = 0;
/*		virtual void doNeNode( NeNode* node ) = 0;
		virtual void doGtNode( GtNode* node ) = 0;
		virtual void doGeNode( GeNode* node ) = 0;
*/

		virtual void doLtNode( LtNode* node ) = 0;
/*        
		virtual void doLeNode( LeNode* node ) = 0;
*/
        virtual void doAddNode( AddNode* node ) = 0;
        virtual void doSubNode( SubNode* node ) = 0;
        virtual void doMulNode( MulNode* node ) = 0;
        virtual void doDivNode( DivNode* node ) = 0;
		virtual void doAssignNode( AssignNode* node ) = 0;

        virtual void doIfNode( IfNode* node ) = 0;
        virtual void doWhileNode( WhileNode* node ) = 0;
        virtual void doBreakNode( BreakNode* node ) = 0;
        virtual void doGlobalFuncNode( GlobalFuncNode* node ) = 0; 
        virtual void doClassFuncNode( ClassFuncNode* node ) = 0;
        virtual void doReturnNode( ReturnNode* node ) = 0;
        virtual void doCallNode( CallNode* node ) = 0;
        virtual void doClassNode( ClassNode* node ) = 0;
        virtual void doNewNode( NewNode* node ) = 0;
        virtual void doClassTypeNode( ClassTypeNode* node ) = 0;

};

#endif
