#ifndef CODE_GEN_H
#define CODE_GEN_H

#include <vector>

#include "code/code.h"
#include "syntax_tree/ast_visitor.h"

#define DEFAULT_REG_NUM 8

#define EIP 0
#define EBP 1
#define ESP 2

class CodeGenEngine {
 protected:
  int m_regIdx;
  vector<Addr*> m_regs;
  int m_offset;

 public:
  CodeGenEngine(int regNum = DEFAULT_REG_NUM);
  void emitCode(Code& code) {}
  void newTmp(Addr& addr, int size);
  void useTmp(Addr& addr, int size);
  void clearTmp();
  void incRegIdx();
};

class CodeGenVisitor : public ASTVisitor {
 public:
  virtual void doStmtListNode(StmtListNode* node) {}
  virtual void doPrintNode(PrintNode* node) {}
  virtual void doDeclareNode(DeclareNode* node) {}
  virtual void doOpNode(OpNode* node) {}
  virtual void doVarNode(VarNode* node) {}
  virtual void doVarRefNode(VarRefNode* node) {}

  virtual void doAndNode(AndNode* node) {}

  virtual void doEqNode(EqNode* node) {}
  virtual void doLtNode(LtNode* node) {}

  virtual void doAddNode(AddNode* node) {}
  virtual void doSubNode(SubNode* node) {}
  virtual void doMulNode(MulNode* node) {}
  virtual void doDivNode(DivNode* node) {}
  virtual void doAssignNode(AssignNode* node) {}

  virtual void doIfNode(IfNode* node) {}
  virtual void doWhileNode(WhileNode* node) {}
  virtual void doBreakNode(BreakNode* node) {}
  virtual void doGlobalFuncNode(GlobalFuncNode* node) {}
  virtual void doClassFuncNode(ClassFuncNode* node) {}
  virtual void doReturnNode(ReturnNode* node) {}
  virtual void doCallNode(CallNode* node) {}
  virtual void doClassNode(ClassNode* node) {}
  virtual void doNewNode(NewNode* node) {}
  virtual void doClassTypeNode(ClassTypeNode* node) {}
};

#endif
