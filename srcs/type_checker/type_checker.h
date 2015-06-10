#ifndef TYPE_CHECKER_H_
#define TYPE_CHECKer_H_

#include <log4cxx/logger.h>

#include "syntax_tree/ast_visitor.h"
#include "syntax_tree/syntax_tree.h"

namespace flang {

class TypeChecker : public ASTVisitor {
 public:
  void finishBase(BinaryExpNode* node);
  void finishBase(PrintNode* node);
  void finishBase(AssignNode* node);
  void finishBase(IfNode* node);
  void finishBase(WhileNode* node);
  void finishBase(BreakNode* node);
  void finishBase(ReturnNode* node);
  void finishBase(CallNode* node);
  void finishBase(ClassNode* node);
  void finishBase(NewNode* node);

 private:
  static log4cxx::LoggerPtr logger_;
};

}  // namespace flang

#endif
