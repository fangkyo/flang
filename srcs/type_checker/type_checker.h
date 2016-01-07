#ifndef TYPE_CHECKER_TYPE_CHECKER_H_
#define TYPE_CHECKER_TYPE_CHECKER_H_

#include <log4cxx/logger.h>

#include "syntax_tree/ast_visitor.h"

namespace flang {

class TypeChecker : public ASTVisitor {
 public:
  bool endVisit(IfNode* node) override;
  bool endVisit(BinaryExpNode* node) override;

 private:
  static log4cxx::LoggerPtr logger_;
};

}  // namespace flang

#endif
