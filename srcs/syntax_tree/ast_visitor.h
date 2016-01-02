#ifndef SYNTAX_TREE_AST_VISITOR_H_
#define SYNTAX_TREE_AST_VISITOR_H_

#include <vector>

#include <boost/ptr_container/ptr_vector.hpp>

#include "base/check.h"
#include "exception/exception.h"

namespace flang {

class ASTNode;
class StmtNode;
class StmtListNode;
class ProgramNode;
class PrintNode;
class ExpNode;
class VarDeclNode;
class VarDeclFragmentNode;
class AssignNode;
class IfNode;
class WhileNode;
class BreakNode;
class ContinueNode;
class FuncNode;
class ParamListNode;
class ParamDeclListNode;
class ClassNode;
class ClassBodyNode;
class ConstructorNode;
class DestructorNode;
class ReturnNode;
class CallNode;
class NewNode;
class UnaryExpNode;
class BinaryExpNode;
class BlockNode;
class NameNode;
class QualifiedNameNode;
class SimpleNameNode;
class ImportNode;
class ImportListNode;
class FieldAccessNode;

// Primitive value node
class IntValNode;
class CharValNode;
class StringValNode;
class BoolValNode;
class DoubleValNode;

// Type node
class TypeNode;
class Int32TypeNode;
class Int64TypeNode;
class StringTypeNode;
class CharTypeNode;
class BoolTypeNode;
class DoubleTypeNode;
class VoidTypeNode;
class UserDefTypeNode;



#define VISIT_METHOD(ASTNodeClass) \
    virtual bool visit(ASTNodeClass*) { return true; } \
    virtual bool endVisit(ASTNodeClass*) { return true; }

class ASTVisitor {
 public:
  ASTVisitor();
  virtual ~ASTVisitor() {}

  VISIT_METHOD(ASTNode)
  VISIT_METHOD(StmtNode)
  VISIT_METHOD(StmtListNode)
  VISIT_METHOD(ProgramNode)
  VISIT_METHOD(PrintNode)
  VISIT_METHOD(VarDeclNode)
  VISIT_METHOD(VarDeclFragmentNode)
  VISIT_METHOD(AssignNode)
  VISIT_METHOD(IfNode)
  VISIT_METHOD(WhileNode)
  VISIT_METHOD(BreakNode)
  VISIT_METHOD(ContinueNode)
  VISIT_METHOD(FuncNode)
  VISIT_METHOD(ClassNode)
  VISIT_METHOD(ReturnNode)
  VISIT_METHOD(CallNode)
  VISIT_METHOD(NewNode)
  VISIT_METHOD(ExpNode)
  VISIT_METHOD(BinaryExpNode)
  VISIT_METHOD(UnaryExpNode)
  VISIT_METHOD(BlockNode)
  VISIT_METHOD(SimpleNameNode)
  VISIT_METHOD(QualifiedNameNode)
  VISIT_METHOD(IntValNode)
  VISIT_METHOD(CharValNode)
  VISIT_METHOD(StringValNode)
  VISIT_METHOD(BoolValNode)
  VISIT_METHOD(DoubleValNode)
  VISIT_METHOD(ImportNode)
  VISIT_METHOD(ImportListNode)
  VISIT_METHOD(ConstructorNode)
  VISIT_METHOD(DestructorNode)
  VISIT_METHOD(ClassBodyNode)
  VISIT_METHOD(ParamListNode)
  VISIT_METHOD(ParamDeclListNode)
  VISIT_METHOD(FieldAccessNode)
  VISIT_METHOD(TypeNode)
  VISIT_METHOD(Int32TypeNode)
  VISIT_METHOD(Int64TypeNode)
  VISIT_METHOD(StringTypeNode)
  VISIT_METHOD(CharTypeNode)
  VISIT_METHOD(BoolTypeNode)
  VISIT_METHOD(DoubleTypeNode)
  VISIT_METHOD(VoidTypeNode)
  VISIT_METHOD(UserDefTypeNode)

  //void setSymbolTable(SymbolTable* symbol_table) {
    //symbol_table_ = symbol_table;
  //}

  //SymbolTable* getSymbolTable() {
    //return symbol_table_;
  //}

  boost::ptr_vector<Exception>& getException() {
    return exceptions_;
  }

  void emitException(Exception* e) {
    exceptions_.push_back(e);
  }

  bool isVisitFromTop() const {
    return visit_from_top_;
  }
  void setVisitFromTop(bool value) {
    visit_from_top_ = value;
  }

  bool isEndVisitFromTop() const {
    return end_visit_from_top_;
  }
  void setEndVisitFromTop(bool value) {
    end_visit_from_top_ = value;
  }

 protected:
  bool visit_from_top_;
  bool end_visit_from_top_;

  boost::ptr_vector<Exception> exceptions_;
};

}  // namespace flang

#endif
