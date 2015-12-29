#ifndef IMPORT_H_
#define IMPORT_H_

#include <boost/ptr_container/ptr_vector.hpp>

#include "base/check.h"
#include "syntax_tree/ast_node.h"
#include "syntax_tree/stmt_node.h"
#include "syntax_tree/name_node.h"

namespace flang {

class ImportNode : public StmtNode {
 INHERIT_AST_NODE(ImportNode, StmtNode, IMPORT_NODE)
 public:
  ImportNode() {}
  ~ImportNode() override {}

  void setPackage(NameNode* package) {
    CHECK(package);
    package_name_.reset(package);
    package_name_->setParent(this);
  }

  void setAlias(SimpleNameNode* alias) {
    CHECK(alias);
    alias_.reset(alias);
    alias_->setParent(this);
  }

  bool getChildNodes(ASTNodeList* child_nodes) override;

 private:
  std::unique_ptr<NameNode> package_name_;
  std::unique_ptr<SimpleNameNode> alias_;
};

class ImportListNode : public ASTNode {
 INHERIT_AST_NODE(ImportListNode, ASTNode, IMPORT_LIST_NODE)
 public:
  ImportListNode() {}
  virtual ~ImportListNode() {}

  void addImport(ImportNode* import);
  bool getChildNodes(ASTNodeList* child_nodes) override;

 private:
  boost::ptr_vector<ImportNode> import_list_;
};

}  // namespace flang

#endif
