#include <iostream>

#include "ast_visitor/ast_visitor.h"
#include "base/check.h"
#include "syntax_tree/syntax_tree.h"

using namespace std;

namespace flang {

// static
ProgramNode* SyntaxTree::CreateProgramNode() {
  return new ProgramNode();
}

void SyntaxTree::accept(ASTVisitor* visitor) {
  visitor->doProgramNode(root_.get());
}

}  // namespace flang
