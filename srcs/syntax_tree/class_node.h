#ifndef CLASS_NODE_H
#define CLASS_NODE_H

#include <memory>
#include <string>

#include <boost/ptr_container/ptr_vector.hpp>

#include "syntax_tree/exp_node.h"
#include "syntax_tree/name_node.h"
#include "syntax_tree/func_node.h"

namespace flang {

class ConstructorNode : public FuncNode {
 INHERIT_AST_NODE(ConstructorNode, FuncNode, CONSTRUCTOR_NODE)

 public:
  ConstructorNode() {}
  virtual ~ConstructorNode() {}
};

class DestructorNode : public FuncNode {
 INHERIT_AST_NODE(DestructorNode, StmtNode, DESTRUCTOR_NODE)

 public:
  DestructorNode() {}
  virtual ~DestructorNode() {}
};

class ClassBodyNode : public ASTNode {
 INHERIT_AST_NODE(ClassBodyNode, ASTNode, CLASS_BODY_NODE)
 public:
  ClassBodyNode() {}
  ~ClassBodyNode() override {}

  void addDeclaration(StmtNode* decl);
  bool getChildNodes(ASTNodeList* child_nodes) override;

 private:
  boost::ptr_vector<ASTNode> decl_list_;
};

class ClassNode : public StmtNode {
 INHERIT_AST_NODE(ClassNode, StmtNode, CLASS_NODE)

public:
  ClassNode() {}
  ~ClassNode() override {}

  void setName(const std::string &name) {
    CHECK(name.length());
    name_ = name;
  }
  const std::string &getName() { return name_; }

  void setSuperClass(NameNode* super_class) {
    CHECK(super_class);
    super_class_.reset(super_class);
  }
  NameNode* getSuperClass() { return super_class_.get(); }

  void setBody(ClassBodyNode* body) {
    CHECK(body);
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
