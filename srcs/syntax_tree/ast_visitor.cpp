#include "syntax_tree/ast_visitor.h"

namespace flang {

ASTVisitor::ASTVisitor() // : symbol_table_(nullptr) {
{
}

void CompositeVisitor::addVisitor(ASTVisitor* visitor) {
  CHECK(visitor);
  visitors_.push_back(visitor);
}

}  // namespace flang
