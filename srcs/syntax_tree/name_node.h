#ifndef NAME_NODE_H_
#define NAME_NODE_H_

#include <memory>
#include <string>
#include <vector>

#include <boost/ptr_container/ptr_vector.hpp>

#include "base/check.h"
#include "syntax_tree/exp_node.h"

namespace flang{

// Name:
//     Name.SimpleName
class NameNode : public ExpNode {
 INHERIT_AST_NODE(NameNode, ExpNode, NAME_NODE)

 public:
  ~NameNode() override {}
  virtual std::string toString() const = 0;

 protected:
  NameNode() {}
};

class SimpleNameNode : public NameNode {
 INHERIT_AST_NODE(SimpleNameNode, NameNode, SIMPLE_NAME_NODE)

 public:
  SimpleNameNode(const std::string name);
  ~SimpleNameNode() override {}

  void setName(const std::string& name) { name_ = name; }
  std::string toString() const override { return name_; }

 private:
  std::string name_;
};

// Name.SimpleName
class QualifiedNameNode : public NameNode {
 INHERIT_AST_NODE(QualifiedNameNode, NameNode, QUALIFIED_NAME_NODE)

 public:
  // QualifiedNameNode(NameNode* qualifier, SimpleNameNode* name);
  QualifiedNameNode() {}
  ~QualifiedNameNode() override {}
  static const char SEPARATOR = '.';

  std::string toString() const override;

  // void setQualifier(NameNode* qualifier) {
    // CHECK(qualifier);
    // qualifier_.reset(qualifier);
    // qualifier_->setParent(this);
  // }
  // NameNode* getQualifier() { return qualifier_.get(); }

  void addSimpleName(SimpleNameNode* name) {
    CHECK(name);
    name_list_.push_back(name);
  }

  const boost::ptr_vector<SimpleNameNode>& getSimpleNameList() {
    return name_list_;
  }

  bool getChildNodes(ASTNodeList* child_nodes) override;

 private:
  boost::ptr_vector<SimpleNameNode> name_list_;
};

}  // namespace flang

#endif
