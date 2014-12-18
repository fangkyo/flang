#ifndef TYPE_CHECK_VISiTOR_H
#define TYPE_CHECK_VISITOR_H

#include <list>
#include <log4cxx/logger.h>

#include "syntax_tree/syntax_tree.h"
#include "scope.h"
#include "visitor.h"
#include "error.h"

using namespace std;
using namespace log4cxx;

class TypeCheckVisitor : public Visitor,
                         public ErrorEngine,
                         public ScopeManager {
 private:
  static LoggerPtr logger_;

 public:
  void doStmtListNode(StmtListNode* node);

  void doDeclareNode(DeclareNode* node);

  void doPrintNode(PrintNode* node);

  void doOpNode(OpNode* node);

  void doVarNode(VarNode* node);

  void doVarRefNode(VarRefNode* node);

  void doAndNode(AndNode* node);

  void doLtNode(LtNode* node);

  void doEqNode(EqNode* node);

  void doAddNode(AddNode* node);

  void doSubNode(SubNode* node);

  void doMulNode(MulNode* node);

  void doDivNode(DivNode* node);

  void doAssignNode(AssignNode* node);

  void doIfNode(IfNode* node);

  void doWhileNode(WhileNode* node);

  void doBreakNode(BreakNode* node);

  void doGlobalFuncNode(GlobalFuncNode* node);

  void doClassFuncNode(ClassFuncNode* node);

  void doReturnNode(ReturnNode* node);

  void doCallNode(CallNode* node);

  void doClassNode(ClassNode* node);

  void doNewNode(NewNode* node);

  void doClassTypeNode(ClassTypeNode* node);

 protected:
  void doBoolOpNode(OpNode* node);

  void doIntOpNode(OpNode* node);

  void doFuncNodePart(FuncNode* node);
};

/*
        void doOrNode( OrNode* node );

        void doNotNode( NotNode* node );

        void doNeNode( NeNode* node );

        void doGtNode( GtNode* node );

        void doGeNode( GeNode* node );

    void doLeNode( LeNode* node );

*/
#endif
