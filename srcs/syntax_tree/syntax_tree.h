#ifndef SYNTAX_TREE_H_
#define SYNTAX_TREE_H_

#include "syntax_tree/ast_node.h"

namespace flang {

// Abstract syntax tree visitor
// class ASTVisitor;

// This class is abstract syntax tree node, which is the baseclass
// for all the concret syntax tree nodes.
class SyntaxTree {
 public:
  SyntaxTree() {}
  bool accept(ASTVisitor*);
  void setRoot(ASTNode* root) { root_.reset(root); }
  ASTNode* getRoot() { return root_.get(); }

 private:
  std::unique_ptr<ASTNode> root_;
};

}  // namespace flang

#endif
