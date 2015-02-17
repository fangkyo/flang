#ifndef SYNTAX_TREE_AST_VISITOR_H_
#define SYNTAX_TREE_AST_VISITOR_H_

#include "syntax_tree/syntax_tree.h"
#include "syntax_tree/exp_node.h"
#include "syntax_tree/print_node.h"
#include "syntax_tree/ctrl_node.h"
#include "syntax_tree/func_node.h"
#include "syntax_tree/class_node.h"
#include "syntax_tree/declare_node.h"
#include "syntax_tree/program_node.h"

namespace flang {

class ASTVisitor {
 public:
  virtual ~ASTVisitor() {}
  virtual void doProgramNode(ProgramNode* node) = 0;
  virtual void doStmtListNode(StmtListNode* node) = 0;
  virtual void doPrintNode(PrintNode* node) = 0;
  virtual void doDeclareNode(DeclareNode* node) = 0;
  virtual void doOpNode(OpNode* node) = 0;
  virtual void doVarNode(VarNode* node) = 0;
  virtual void doVarRefNode(VarRefNode* node) = 0;
  virtual void doAndNode(AndNode* node) = 0;
  virtual void doEqNode(EqNode* node) = 0;
  virtual void doLtNode(LtNode* node) = 0;
  virtual void doAddNode(AddNode* node) = 0;
  virtual void doSubNode(SubNode* node) = 0;
  virtual void doMulNode(MulNode* node) = 0;
  virtual void doDivNode(DivNode* node) = 0;
  virtual void doAssignNode(AssignNode* node) = 0;
  virtual void doIfNode(IfNode* node) = 0;
  virtual void doWhileNode(WhileNode* node) = 0;
  virtual void doBreakNode(BreakNode* node) = 0;
  virtual void doGlobalFuncNode(GlobalFuncNode* node) = 0;
  virtual void doClassFuncNode(ClassFuncNode* node) = 0;
  virtual void doReturnNode(ReturnNode* node) = 0;
  virtual void doCallNode(CallNode* node) = 0;
  virtual void doClassNode(ClassNode* node) = 0;
  virtual void doNewNode(NewNode* node) = 0;
  virtual void doClassTypeNode(ClassTypeNode* node) = 0;
};

} // namespace flang

#endif
