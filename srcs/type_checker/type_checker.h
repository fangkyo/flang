#ifndef TYPE_CHECKER_H_
#define TYPE_CHECKer_H_

#include <log4cxx/logger.h>

#include "syntax_tree/ast_visitor.h"
#include "syntax_tree/syntax_tree.h"

namespace flang {

class TypeChecker : public ASTVisitor {
 public:
  void startBase()

 private:
  static log4cxx::LoggerPtr logger_;
};

}  // namespace flang

#endif
