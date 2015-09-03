#ifndef AST_VISITOR_H_
#define AST_VISITOR_H_

#include <vector>

#include <boost/ptr_container/ptr_vector.hpp>

#include "base/check.h"
#include "exception/exception.h"
// #include "symbol_table/symbol_table.h"

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
class ReferenceNode;

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

/**
 * @brief This struct is used for passing inherit attributes between visitor
 * functions.
 */
struct ASTVisitorContext {
};

#define VISIT_METHOD(ASTNodeClass) \
    virtual void visit(ASTNodeClass*) {} \
    virtual void endVisit(ASTNodeClass*) {} \

class ASTVisitor {
 public:
  ASTVisitor();
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
  VISIT_METHOD(ReferenceNode)

  // void setSymbolTable(SymbolTable* symbol_table) {
    // symbol_table_ = symbol_table;
  // }

  // SymbolTable* getSymbolTable() {
    // return symbol_table_;
  // }

  boost::ptr_vector<Exception>& getException() {
    return exceptions_;
  }

  void addException(Exception* e) {
    exceptions_.push_back(e);
  }

 protected:
  // SymbolTable* symbol_table_;
  boost::ptr_vector<Exception> exceptions_;
};


#define COMPOSITE_VISIT(ASTNodeClass) \
    void visit(ASTNodeClass* node) { \
      CHECK(node); \
      for (auto* visitor : visitors_) { \
        visitor->visit(node); \
      } \
    }  \
    void endVisit(ASTNodeClass* node) { \
      CHECK(node); \
      for (auto* visitor : visitors_) { \
        visitor->endVisit(node); \
      } \
    }  \

class CompositeVisitor : public ASTVisitor {
 public:
  COMPOSITE_VISIT(ReferenceNode)
  void addVisitor(ASTVisitor* visitor);

 private:
  std::vector<ASTVisitor*> visitors_;
};

}  // namespace flang

#endif
