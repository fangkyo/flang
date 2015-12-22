#ifndef AST_VISITOR_H_
#define AST_VISITOR_H_

#include <vector>

#include <boost/ptr_container/ptr_vector.hpp>

#include "base/check.h"
#include "exception/exception.h"

namespace flang {

class ASTNode;
class ProgramNode;
class PrintNode;
class VarDeclNode;
class VarDeclFragmentNode;
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
class QualifiedNameNode;
class SimpleNameNode;
class ReferenceNode;

// Primitive value node
class Int32ValNode;
class Int64ValNode;
class CharValNode;
class StringValNode;
class BoolValNode;
class DoubleValNode;

// Data type node
class QualifiedTypeNode;
class ArrayTypeNode;
class ContinueNode;

/**
 * @brief This struct is used for passing inherit attributes between visitor
 * functions.
 */
struct ASTVisitorContext {
};

#define VISIT_METHOD(ASTNodeClass) \
    virtual bool visit(ASTNodeClass*) { return true; } \
    virtual bool endVisit(ASTNodeClass*) { return true; }

class ASTVisitor {
 public:
  ASTVisitor();
  virtual ~ASTVisitor() {}

  VISIT_METHOD(ASTNode)
  VISIT_METHOD(ProgramNode)
  //VISIT_METHOD(PrintNode)
  //VISIT_METHOD(VarDeclNode)
  //VISIT_METHOD(VarDeclFragmentNode)
  //VISIT_METHOD(SimpleNodeNode)
  //VISIT_METHOD(QualifiedNodeNode)
  //VISIT_METHOD(AssignNode)
  //VISIT_METHOD(IfNode)
  //VISIT_METHOD(WhileNode)
  //VISIT_METHOD(BreakNode)
  //VISIT_METHOD(FuncNode)
  //VISIT_METHOD(ClassNode)
  //VISIT_METHOD(ReturnNode)
  //VISIT_METHOD(CallNode)
  //VISIT_METHOD(NewNode)
  //VISIT_METHOD(BinaryExpNode)
  //VISIT_METHOD(UnaryExpNode)
  //VISIT_METHOD(BlockNode)
  //VISIT_METHOD(SimpleNameNode)
  //VISIT_METHOD(QualifiedNameNode)
  //VISIT_METHOD(Int32ValNode)
  //VISIT_METHOD(Int64ValNode)
  //VISIT_METHOD(CharValNode)
  //VISIT_METHOD(StringValNode)
  //VISIT_METHOD(BoolValNode)
  //VISIT_METHOD(DoubleValNode)
  //VISIT_METHOD(QualifiedTypeNode)
  //VISIT_METHOD(ArrayTypeNode)
  //VISIT_METHOD(ReferenceNode)
  //VISIT_METHOD(ContinueNode)

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

  //void resetContext(ASTVisitorContext* context) {
    //context_.reset(context);
  //}

  bool isVisitFromTop() {
    return visit_from_top_;
  }

  bool isEndVisitFromTop() {
    return end_visit_from_top_;
  }

 protected:
  bool visit_from_top_;
  bool end_visit_from_top_;

  boost::ptr_vector<Exception> exceptions_;
};

}  // namespace flang

#endif
