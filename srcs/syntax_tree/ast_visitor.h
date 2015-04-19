#ifndef VISITOR_H_
#define VISITOR_H_

namespace flang {

class ProgramNode;
class PrintNode;
class VarDeclarationNode;
class VarDeclarationFragmentNode;
class SimpleNodeNode;
class QualifiedNodeNode;
class AssignNode;
class IfNode;
class WhileNode;
class BreakNode;
class FuncNode;
class ClassNode;
class ReturnNode;
class CallNode;
class NewNode;
class UnaryExpNode;
class BinaryExpNode;
class BlockNode;

#define VISIT_METHOD(ASTNodeClass) \
    virtual bool beforeVisit(ASTNodeClass*) { return true; } \
    virtual bool visit(ASTNodeClass*) { return true; } \
    virtual bool afterVisit(ASTNodeClass*) { return true; }

class ASTVisitor {
 public:
  virtual ~ASTVisitor() {}

  VISIT_METHOD(ProgramNode)
  VISIT_METHOD(PrintNode)
  VISIT_METHOD(VarDeclarationNode)
  VISIT_METHOD(SimpleNodeNode)
  VISIT_METHOD(QualifiedNodeNode)
  VISIT_METHOD(AssignNode)
  VISIT_METHOD(IfNode)
  VISIT_METHOD(WhileNode)
  VISIT_METHOD(BreakNode)
  VISIT_METHOD(FuncNode)
  VISIT_METHOD(ClassNode)
  VISIT_METHOD(ReturnNode)
  VISIT_METHOD(CallNode)
  VISIT_METHOD(NewNode)
  VISIT_METHOD(BinaryExpNode)
  VISIT_METHOD(UnaryExpNode)
  VISIT_METHOD(BlockNode)

  virtual void doProgramNode(ProgramNode*) {};
  virtual void doPrintNode(PrintNode*) {};
  virtual void doDeclareNode(VarDeclarationNode*) {};
  virtual void doUnaryExpNode(UnaryExpNode*) {};
  virtual void doBinaryExpNode(BinaryExpNode*) {};
  virtual void doAssignNode(AssignNode*) {};
  virtual void doIfNode(IfNode*) {};
  virtual void doWhileNode(WhileNode*) {};
  virtual void doBreakNode(BreakNode*) {};
  virtual void doFuncNode(FuncNode*);
  virtual void doReturnNode(ReturnNode*) {};
  virtual void doCallNode(CallNode*) {};
  virtual void doClassNode(ClassNode*) {};
  virtual void doNewNode(NewNode*) {};
};

}  // namespace flang

#endif
