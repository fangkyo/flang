#ifndef VISITOR_H_
#define VISITOR_H_

namespace flang {

class ProgramNode;
class StmtListNode;
class PrintNode;
class DeclareNode;
class VarNode;
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
class UnaryExpNode;
class BinaryExpNode;

#define VISIT_METHOD(ASTNodeClass) \
    virtual bool beforeVisit(ASTNodeClass*) { return true; } \
    virtual bool visit(ASTNodeClass*) { return true; } \
    virtual bool afterVisit(ASTNodeClass*) { return true; }

class ASTVisitor {
 public:
  virtual ~ASTVisitor() {}

  VISIT_METHOD(ProgramNode)
  VISIT_METHOD(PrintNode)
  VISIT_METHOD(DeclareNode)

  virtual void doProgramNode(ProgramNode*) {};
  virtual void doPrintNode(PrintNode*) {};
  virtual void doDeclareNode(DeclareNode*) {};
  virtual void doUnaryExpNode(UnaryExpNode*) {};
  virtual void doBinaryExpNode(BinaryExpNode*) {};
  virtual void doVarNode(VarNode*) {};
  virtual void doAssignNode(AssignNode*) {};
  virtual void doIfNode(IfNode*) {};
  virtual void doWhileNode(WhileNode*) {};
  virtual void doBreakNode(BreakNode*) {};
  virtual void doFuncNode(FuncNode*);
  virtual void doReturnNode(ReturnNode*) {};
  virtual void doCallNode(CallNode*) {};
  virtual void doClassNode(ClassNode*) {};
  virtual void doNewNode(NewNode*) {};
  virtual void doClassTypeNode(ClassTypeNode*) {};
};

}  // namespace flang

#endif
