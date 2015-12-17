#include <vector>

#include "syntax_tree/ast_visitor.h"
#include "syntax_tree/ast_node.h"
#include "syntax_tree/program_node.h"

#define VISIT_IMPL(ASTNodeClass) \
    void ASTVisitor::traverse(ASTNodeClass* node) { \
      visit(node); \
      std::vector<ASTNode*> child_nodes; \
      if (node->getChildNodes(&child_nodes)) { \
        for (auto* child: child_nodes) { \
          child->accept(this); \
        } \
      } \
      endVisit(node); \
    }

namespace flang {

ASTVisitor::ASTVisitor(){
}

VISIT_IMPL(ProgramNode)


}  // namespace flang
