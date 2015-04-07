#ifndef VISITOR_H_
#define VISITOR_H_

#include "syntax_tree/syntax_tree.h"
#include "syntax_tree/exp_node.h"
#include "syntax_tree/print_node.h"
#include "syntax_tree/ctrl_node.h"
#include "syntax_tree/func_node.h"
#include "syntax_tree/class_node.h"
#include "syntax_tree/declare_node.h"

namespace flang {

class ASTVisitor {
 public:
  virtual ~ASTVisitor() {}
  virtual void doStmtListNode(StmtListNode* node) {};
  virtual void doPrintNode(PrintNode* node) {};
  virtual void doDeclareNode(DeclareNode* node) = {};
  virtual void doOpNode(OpNode* node) {};
  virtual void doVarNode(VarNode* node) {};
  virtual void doVarRefNode(VarRefNode* node) {};
  virtual void doAndNode(AndNode* node) {};
  virtual void doEqNode(EqNode* node) {};
  virtual void doLtNode(LtNode* node) {};
  virtual void doAddNode(AddNode* node) {};
  virtual void doSubNode(SubNode* node) {};
  virtual void doMulNode(MulNode* node) {};
  virtual void doDivNode(DivNode* node) {};
  virtual void doAssignNode(AssignNode* node) {};
  virtual void doIfNode(IfNode* node) {};
  virtual void doWhileNode(WhileNode* node) {};
  virtual void doBreakNode(BreakNode* node) {};
  virtual void doGlobalFuncNode(GlobalFuncNode* node) {};
  virtual void doClassFuncNode(ClassFuncNode* node) {};
  virtual void doReturnNode(ReturnNode* node) {};
  virtual void doCallNode(CallNode* node) {};
  virtual void doClassNode(ClassNode* node) {};
  virtual void doNewNode(NewNode* node) {};
  virtual void doClassTypeNode(ClassTypeNode* node) {};
};

}  // namespace flang

#endif
