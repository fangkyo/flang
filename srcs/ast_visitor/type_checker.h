#ifndef TYPE_CHECKER_H_
#define TYPE_CHECKer_H_

#include <log4cxx/logger.h>

#include "ast_visitor/ast_visitor.h"
#include "syntax_tree/syntax_tree.h"

using namespace std;
using namespace log4cxx;

namespace flang {

class TypeChecker : public ASTVisitor {
 public:
  void doStmtListNode(StmtListNode* node) override;

  void doDeclareNode(DeclareNode* node) override;

  void doPrintNode(PrintNode* node) override;

  void doOpNode(OpNode* node) override;

  void doVarNode(VarNode* node) override;

  void doVarRefNode(VarRefNode* node) override;

  void doAndNode(AndNode* node) override;

  void doLtNode(LtNode* node) override;

  void doEqNode(EqNode* node) override;

  void doAddNode(AddNode* node) override;

  void doSubNode(SubNode* node) override;

  void doMulNode(MulNode* node) override;

  void doDivNode(DivNode* node) override;

  void doAssignNode(AssignNode* node) override;

  void doIfNode(IfNode* node) override;

  void doWhileNode(WhileNode* node) override;

  void doBreakNode(BreakNode* node) override;

  void doGlobalFuncNode(GlobalFuncNode* node) override;

  void doClassFuncNode(ClassFuncNode* node) override;

  void doReturnNode(ReturnNode* node) override;

  void doCallNode(CallNode* node) override;

  void doClassNode(ClassNode* node) override;

  void doNewNode(NewNode* node) override;

  void doClassTypeNode(ClassTypeNode* node) override;

 protected:
  void doBoolOpNode(OpNode* node);
  void doIntOpNode(OpNode* node);
  void doFuncNodePart(FuncNode* node);

 private:
  static LoggerPtr logger_;
};

}  // namespace flang 

#endif
