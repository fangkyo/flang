#include <iostream>

#include "base/check.h"
#include "syntax_tree/ast_visitor.h"
#include "syntax_tree/syntax_tree.h"

namespace flang {

bool SyntaxTree::accept(ASTVisitor* visitor) {
  CHECK(root_.get());
  return root_->accept(visitor);
}

}  // namespace flang
