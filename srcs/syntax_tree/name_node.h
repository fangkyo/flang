#ifndef NAME_NODE_H_
#define NAME_NODE_H_

#include <memory>
#include <string>

#include "syntax_tree/exp_node.h"

namespace flang{

class NameNode : public ExpNode {
 public:
  ~NameNode() override {}
 protected:
  NameNode(ASTNode::ASTNodeType node_type) : ExpNode(node_type) {}
};

class SimpleNameNode : public NameNode {
  public:
   SimpleNameNode(const std::string name);
   ~SimpleNameNode() override {}

   void setName(const std::string& name) { name_ = name; }
   const std::string& getName() { return name_; }

  private:
   std::string name_;
};

// QualifiedName.SimpleName
class QualifiedNameNode : public NameNode {
 public:
  QualifiedNameNode(NameNode* qualifier, SimpleNameNode* name);
  ~QualifiedNameNode() override {}

  void accept(ASTVisitor* visitor) override;

  void setName(SimpleNameNode* name) { name_.reset(name); }
  SimpleNameNode* getName() { return name_.get(); }

  void setQualifier(NameNode* qualifier) { qualifier_.reset(qualifier); }
  NameNode* getQualifier() { return qualifier_.get(); }
 private:
  std::unique_ptr<NameNode> qualifier_;
  std::unique_ptr<SimpleNameNode> name_;
};

class VarNode : public ExpNode {
 public:
  VarNode(const std::string& name);
  ~VarNode() override {}

  void accept(ASTVisitor* visitor) override;

  const std::string& name() { return name_; }
  void setName(const std::string& name) { name_= name; }

 private:
  std::string name_;
};

}  // namespace flang

#endif
