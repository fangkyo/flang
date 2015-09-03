#ifndef SYNTAX_TREE_REFERENCE_NODE_H_
#define SYNTAX_TREE_REFERENCE_NODE_H_

#include <memory>

#include <boost/ptr_container/ptr_vector.hpp>

#include "syntax_tree/exp_node.h"

namespace flang {

/**
 * @brief Reference node represents a reference or an invocation.
 *
 * reference :
 *   | reference '.' name
 *   | reference '.' call
 *   | name
 *   | call
 */
class ReferenceNode : public ExpNode {
 public:
  ReferenceNode() : ExpNode(ASTNode::REFERENCE_NODE) {}

  void accept(ASTVisitor* visitor) override;
  void addChildNode(ASTNode* child);

 private:
  boost::ptr_vector<ASTNode> child_nodes_;
};

}  // namespace

#endif

