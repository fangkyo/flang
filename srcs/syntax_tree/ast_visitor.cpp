#include "syntax_tree/ast_visitor.h"

namespace flang {

ASTVisitor::ASTVisitor() :
  next_(nullptr), previous_(nullptr), symbol_table_(nullptr) {

}


void ASTVisitor::setNext(ASTVisitor* next) {
  CHECK(next);
  next_ = next;
  next_->setPrevious(this);
}

}  // namespace flang
