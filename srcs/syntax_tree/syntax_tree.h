#ifndef SYNTAX_TREE_H_
#define SYNTAX_TREE_H_

#include "syntax_tree/exp_node.h"
#include "syntax_tree/name_node.h"
#include "syntax_tree/print_node.h"
#include "syntax_tree/ctrl_node.h"
#include "syntax_tree/func_node.h"
#include "syntax_tree/class_node.h"
#include "syntax_tree/var_decl_node.h"
#include "syntax_tree/stmt_node.h"
#include "syntax_tree/assign_node.h"
#include "syntax_tree/binary_exp_node.h"
#include "syntax_tree/unary_exp_node.h"
#include "syntax_tree/data_type_node.h"
#include "syntax_tree/program_node.h"
#include "syntax_tree/primitive_node.h"
#include "syntax_tree/new_node.h"
#include "syntax_tree/block_node.h"
#include "syntax_tree/reference_node.h"

namespace flang {

// Abstract syntax tree visitor
class ASTVisitor;

// This class is abstract syntax tree node, which is the baseclass
// for all the concret syntax tree nodes.
class SyntaxTree {
 public:
  SyntaxTree() {}
  void accept(ASTVisitor*);
  void setRoot(ProgramNode* root) { root_.reset(root); }
  ProgramNode* getRoot() { return root_.get(); }

 private:
  std::unique_ptr<ProgramNode> root_;
};

}  // namespace flang

#endif
