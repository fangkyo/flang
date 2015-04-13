#include <iostream>

#include "syntax_tree/ast_visitor.h"
#include "syntax_tree/syntax_tree.h"

namespace flang {

void SyntaxTree::accept(ASTVisitor* visitor) {
  root_->accept(visitor);
}

}  // namespace flang
