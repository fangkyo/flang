#ifndef TYPE_CHECKER_H_
#define TYPE_CHECKer_H_

#include <log4cxx/logger.h>

#include "syntax_tree/ast_visitor.h"
#include "syntax_tree/syntax_tree.h"

namespace flang {

class TypeChecker : public ASTVisitor {
 public:

  bool visit(BinaryExpNode*) override;

  void doPrintNode(PrintNode* node) override;

  void doAssignNode(AssignNode* node) override;

  void doIfNode(IfNode* node) override;

  void doWhileNode(WhileNode* node) override;

  void doBreakNode(BreakNode* node) override;

  void doReturnNode(ReturnNode* node) override;

  void doCallNode(CallNode* node) override;

  void doClassNode(ClassNode* node) override;

  void doNewNode(NewNode* node) override;

 private:
  static log4cxx::LoggerPtr logger_;
};

}  // namespace flang

#endif
