#ifndef NAME_NODE_H_
#define NAME_NODE_H_

#include <memory>
#include <string>
#include <vector>

#include "syntax_tree/exp_node.h"

namespace flang{

// Name:
//     Name.SimpleName
class NameNode : public ExpNode {
 INHERIT_AST_NODE(NameNode, ExpNode)

 public:
  ~NameNode() override {}
  virtual std::string getFullName() = 0;
  virtual std::string getName() const = 0;
  static const char SEPARATOR = '$';

 protected:
  NameNode(ASTNode::ASTNodeType node_type) : ExpNode(node_type) {}
};

class SimpleNameNode : public NameNode {
 INHERIT_AST_NODE(SimpleNameNode, NameNode)

 public:
  SimpleNameNode(const std::string name);
  ~SimpleNameNode() override {}

  void setName(const std::string& name) { name_ = name; }
  std::string getName() const override { return name_; }
  std::string getFullName() override { return name_; }

 private:
  std::string name_;
};

// Name.SimpleName
class QualifiedNameNode : public NameNode {
 INHERIT_AST_NODE(QualifiedNameNode, NameNode)

 public:
  QualifiedNameNode(NameNode* qualifier, SimpleNameNode* name);
  ~QualifiedNameNode() override {}

  std::string getName() const override { return ""; }

  void setQualifier(NameNode* qualifier) { qualifier_.reset(qualifier); }
  NameNode* getQualifier() { return qualifier_.get(); }

  std::string getFullName() override;

 private:
  std::unique_ptr<NameNode> qualifier_;
  std::unique_ptr<SimpleNameNode> name_;
};

}  // namespace flang

#endif
