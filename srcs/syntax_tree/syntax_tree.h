#ifndef SYNTAX_TREE_H_
#define SYNTAX_TREE_H_

#include "syntax_tree/exp_node.h"
#include "syntax_tree/print_node.h"
#include "syntax_tree/ctrl_node.h"
#include "syntax_tree/func_node.h"
#include "syntax_tree/class_node.h"
#include "syntax_tree/var_declaration_node.h"
#include "syntax_tree/program_node.h"

namespace flang {

// Abstract syntax tree visitor
class ASTVisitor;

// This class is abstract syntax tree node, which is the baseclass
// for all the concret syntax tree nodes.
class SyntaxTree {
 public:
  SyntaxTree() {}
  void accept(ASTVisitor*);

  // ASTNode factory methods
  static ProgramNode* CreateProgramNode();
 private:
  std::unique_ptr<ProgramNode> root_;
};

}  // namespace flang

#endif
