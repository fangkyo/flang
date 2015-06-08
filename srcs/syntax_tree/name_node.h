#ifndef NAME_NODE_H_
#define NAME_NODE_H_

#include <memory>
#include <string>
#include <vector>

#include "syntax_tree/exp_node.h"

namespace flang{

class NameNode : public ExpNode {
 public:
  ~NameNode() override {}
  virtual std::string getFullyQualifiedName() = 0;
  virtual void getNames(std::vector<const std::string*>*) = 0;
  virtual void getQualifiers(std::vector<const std::string*>* qualifiers) = 0;

 protected:
  NameNode(ASTNode::ASTNodeType node_type) : ExpNode(node_type) {}
};

class SimpleNameNode : public NameNode {
 public:
  SimpleNameNode(const std::string name);
  ~SimpleNameNode() override {}

  void setName(const std::string& name) { name_ = name; }
  const std::string& getName() { return name_; }


  std::string getFullyQualifiedName() override { return name_; }

  void getNames(std::vector<const std::string*>* names) override {
    names->push_back(&name_);
  }
  void getQualifiers(std::vector<const std::string*>* qualifiers) override {}

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

  std::string getFullyQualifiedName() override;

  void getQualifiers(std::vector<const std::string*>* qualifiers) override;
  void getNames(std::vector<const std::string*>* names) override;

 private:
  std::unique_ptr<NameNode> qualifier_;
  std::unique_ptr<SimpleNameNode> name_;
};

}  // namespace flang

#endif
