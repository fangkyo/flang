#ifndef IMPORT_H_
#define IMPORT_H_

#include <boost/ptr_container/ptr_vector.hpp>

#include "syntax_tree/ast_node.h"
#include "syntax_tree/stmt_node.h"
#include "syntax_tree/name_node.h"

namespace flang {

class ImportNode : public StmtNode {
 INHERIT_AST_NODE(ImportNode, StmtNode)
 public:
  ImportNode() : StmtNode(ASTNode::IMPORT_NODE) {}
  ~ImportNode() override {}

  void setPackage(NameNode* package) {
    package_name_.reset(package);
  }

  void setAlias(SimpleNameNode* alias) {
    alias_.reset(alias);
  }

 private:
  std::unique_ptr<NameNode> package_name_;
  std::unique_ptr<SimpleNameNode> alias_;
};

class ImportListNode : public ASTNode {
 INHERIT_AST_NODE(ImportListNode, ASTNode)
 public:
  ImportListNode() : ASTNode(ASTNode::IMPORT_LIST_NODE) {}
  virtual ~ImportListNode() {}

  void addImport(ImportNode* import);

 private:
  boost::ptr_vector<ImportNode> import_list_;
};

}  // namespace flang

#endif
