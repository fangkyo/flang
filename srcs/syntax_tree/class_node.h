#ifndef CLASS_NODE_H
#define CLASS_NODE_H

#include <memory>
#include <string>

#include <boost/ptr_container/ptr_vector.hpp>

#include "syntax_tree/exp_node.h"
#include "syntax_tree/name_node.h"

namespace flang {

class ConstructorNode : public StmtNode {
 INHERIT_AST_NODE(ConstructorNode, StmtNode)

 public:
  ConstructorNode() : StmtNode(ASTNode::CONSTRUCTOR_NODE) {}
  virtual ~ConstructorNode() {}
};

class DestructorNode : public StmtNode {
 INHERIT_AST_NODE(DestructorNode, StmtNode)

 public:
  DestructorNode() : StmtNode(ASTNode::DESTRUCTOR_NODE) {}
  virtual ~DestructorNode() {}
};

class ClassBodyNode : public ASTNode {
 INHERIT_AST_NODE(ClassBodyNode, ASTNode)
 public:
  ClassBodyNode() : ASTNode(ASTNode::CLASS_BODY_NODE) {}
  ~ClassBodyNode() override {}

  void addDeclaration(StmtNode* decl);
  bool getChildNodes(ASTNodeList* child_nodes) override;

 private:
  boost::ptr_vector<ASTNode> decl_list_;
};

class ClassNode : public StmtNode {
 INHERIT_AST_NODE(ClassNode, StmtNode)

public:
  ClassNode() : StmtNode(ASTNode::CLASS_NODE) {}
  ~ClassNode() override {}

  void setName(const std::string &name) { name_ = name; }
  const std::string &getName() { return name_; }

  void setSuperClass(NameNode* super_class) { super_class_.reset(super_class); }
  NameNode* getSuperClass() { return super_class_.get(); }

  void setBody(ClassBodyNode* body) {
    body_.reset(body);
  }
  ClassBodyNode* getBody() {
    return body_.get();
  }
  void addBodyDecl(StmtNode* declaration);
  bool hasSuperClass() { return super_class_ == nullptr; }
  bool getChildNodes(ASTNodeList* child_nodes) override;

 private:
  std::string name_;
  std::unique_ptr<NameNode> super_class_;
  std::unique_ptr<ClassBodyNode> body_;
};

}  // namespace flang

#endif
