#ifndef TYPE_CHECKER_TYPE_CHECKER_H_
#define TYPE_CHECKER_TYPE_CHECKER_H_

#include <log4cxx/logger.h>

#include "syntax_tree/ast_visitor.h"

namespace flang {

class SymbolTable;
class Exception;
class ExceptionManager;

class TypeChecker : public ASTVisitor {
 public:
  TypeChecker(SymbolTable* symbol_table, ExceptionManager* except_manager);

  bool visit(BoolValNode* node) override;
  bool visit(IntValNode* node) override;
  bool visit(StringValNode* node) override;
  bool visit(DoubleValNode* node) override;
  bool visit(CharValNode* node) override;

  bool endVisit(IfNode* node) override;
  bool endVisit(BinaryExpNode* node) override;
  bool endVisit(FieldAccessNode* node) override;

  SymbolTable* getSymbolTable() const {
    return symbol_table_;
  }

  ExceptionManager* getExceptionManager() const {
    return except_manager_;
  }
  void addException(Exception* e);

 private:
  SymbolTable* symbol_table_;
  ExceptionManager* except_manager_;
  static log4cxx::LoggerPtr logger_;
};

}  // namespace flang

#endif
