#ifndef TYPE_CHECKER_H_
#define TYPE_CHECKer_H_

#include <log4cxx/logger.h>

#include "syntax_tree/ast_visitor.h"
#include "syntax_tree/syntax_tree.h"

namespace flang {

class TypeChecker : public ASTVisitor {
 public:
  void finishBase(BinaryExpNode* node) override;
  void finishBase(PrintNode* node) override;
  void finishBase(AssignNode* node) override;
  void finishBase(IfNode* node) override;
  void finishBase(WhileNode* node) override;
  void finishBase(BreakNode* node) override;
  void finishBase(ReturnNode* node) override;
  void finishBase(CallNode* node) override;
  void finishBase(ClassNode* node) override;
  void finishBase(NewNode* node) override;

 private:
  static log4cxx::LoggerPtr logger_;
};

}  // namespace flang

#endif
