#ifndef VISITOR_H_
#define VISITOR_H_

namespace flang {

class ProgramNode;
class StmtListNode;
class PrintNode;
class DeclareNode;
class VarNode;
class VarRefNode;
class AndNode;
class LtNode;
class EqNode;
class LtNode;
class AddNode;
class SubNode;
class MulNode;
class DivNode;
class AssignNode;
class IfNode;
class WhileNode;
class BreakNode;
class FuncNode;
class ClassNode;
class ReturnNode;
class CallNode;
class ClassNode;
class NewNode;
class ClassTypeNode;
class OpNode;
class UnaryExpNode;
class BinaryExpNode;

class ASTVisitor {
 public:
  virtual ~ASTVisitor() {}
  virtual void doProgramNode(ProgramNode*) {};
  virtual void doStmtListNode(StmtListNode*) {};
  virtual void doPrintNode(PrintNode*) {};
  virtual void doDeclareNode(DeclareNode*) {};
  virtual void doOpNode(OpNode*) {};
  virtual void doUnaryExpNode(UnaryExpNode*) {};
  virtual void doBinaryExpNode(BinaryExpNode*) {};
  virtual void doVarNode(VarNode*) {};
  virtual void doVarRefNode(VarRefNode*) {};
  virtual void doAndNode(AndNode*) {};
  virtual void doEqNode(EqNode*) {};
  virtual void doLtNode(LtNode*) {};
  virtual void doAddNode(AddNode*) {};
  virtual void doSubNode(SubNode*) {};
  virtual void doMulNode(MulNode*) {};
  virtual void doDivNode(DivNode*) {};
  virtual void doAssignNode(AssignNode*) {};
  virtual void doIfNode(IfNode*) {};
  virtual void doWhileNode(WhileNode*) {};
  virtual void doBreakNode(BreakNode*) {};
  // virtual void doGlobalFuncNode(GlobalFuncNode*) {};
  // virtual void doClassFuncNode(ClassFuncNode*) {};
  virtual void doFuncNode(FuncNode*);
  virtual void doReturnNode(ReturnNode*) {};
  virtual void doCallNode(CallNode*) {};
  virtual void doClassNode(ClassNode*) {};
  virtual void doNewNode(NewNode*) {};
  virtual void doClassTypeNode(ClassTypeNode*) {};
};

}  // namespace flang

#endif
