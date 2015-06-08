#ifndef AST_VISITOR_H_
#define AST_VISITOR_H_

#include "base/check.h"
#include "symbol_table/symbol_table.h"

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
class QualifiedNameNode;
class SimpleNameNode;

// Primitive value node
class Int32ValNode;
class Int64ValNode;
class CharValNode;
class StringValNode;
class FloatValNode;
class BoolValNode;

// Data type node
class QualifiedTypeNode;
class ArrayTypeNode;

#define VISIT_METHOD(ASTNodeClass) \
    virtual void start(ASTNodeClass* ast_node) { \
      startBase(ast_node); \
      if (next_) { \
        next_->start(ast_node); \
      } \
    } \
    virtual void startBase(ASTNodeClass*) {} \
    virtual void finish(ASTNodeClass* ast_node) { \
      finishBase(ast_node); \
      if (next_) { \
        next_->finish(ast_node); \
      } \
    } \
    virtual void finishBase(ASTNodeClass*) {} \

class ASTVisitor {
 public:
  ASTVisitor() : next_(nullptr), previous_(nullptr), symbol_table_(nullptr) {}
  virtual ~ASTVisitor() {}

  VISIT_METHOD(ProgramNode)
  VISIT_METHOD(PrintNode)
  VISIT_METHOD(VarDeclarationNode)
  VISIT_METHOD(VarDeclarationFragmentNode)
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
  VISIT_METHOD(SimpleNameNode)
  VISIT_METHOD(QualifiedNameNode)
  VISIT_METHOD(Int32ValNode)
  VISIT_METHOD(Int64ValNode)
  VISIT_METHOD(CharValNode)
  VISIT_METHOD(StringValNode)
  VISIT_METHOD(BoolValNode)
  VISIT_METHOD(FloatValNode)
  VISIT_METHOD(QualifiedTypeNode)
  VISIT_METHOD(ArrayTypeNode)

  ASTVisitor* getNext() { return next_; }

  void setNext(ASTVisitor* next) {
    CHECK(next);
    next_ = next;
    next_->setPrevious(this);
  }

  ASTVisitor* getPrevious() { return previous_; }

  void setSymbolTable(SymbolTable* symbol_table) {
    symbol_table_ = symbol_table;
  }

  SymbolTable* getSymbolTable() {
    return symbol_table_;
  }

 protected:
  void setPrevious(ASTVisitor* previous) { previous_ = previous; }

  ASTVisitor* next_;
  ASTVisitor* previous_;

  SymbolTable* symbol_table_;
};

}  // namespace flang

#endif
