#ifndef AST_NODE_H_
#define AST_NODE_H_

#include <cstdint>
#include <cstring>
#include <vector>

#include "front_end/location.hh"
#include "syntax_tree/ast_visitor.h"
#include "syntax_tree/ast_node.pb.h"
#include "symbol_table/data_type.h"

namespace flang {

#define INHERIT_AST_NODE(Derived, Base, NodeType) \
    public: \
     Base* toBaseNode() { return dynamic_cast<Base*>(this); } \
     bool accept(ASTVisitor* visitor) override { \
       return traverse<Derived>(visitor); \
     } \
     ASTNodeType getNodeType() const override { \
       return NodeType; \
     }

class Symbol;

struct ASTAttribute {
  ASTAttribute() : symbol(nullptr) {
  }

  Symbol* symbol;
  DataType* data_type;
  ASTValue value;
};

/** @breif Abstract syntax tree node. */
class ASTNode {
 public:
  ASTNode() : parent_(nullptr) {}

  virtual ~ASTNode() {}
  virtual bool accept(ASTVisitor* visitor) {
    return traverse<ASTNode>(visitor);
  }
  // @brief Transfer 'this' pointer to base class pointer type.
  //
  // @return Base class type this pointer. Return nullptr if this class
  //     doesn't inherit any class.
  ASTNode* toBaseNode() { return nullptr; }

 protected:
  /**
   * @brief Traverse this ast node.
   *
   * 1. Call visitor.visit() on this node over the inheritance hierarchy.
   * 2. Traverse the child nodes.
   * 3. Call visitor.endVisit() on this node.
   *
   * @return Return whether traverse this node successfully.
   */
  template <typename Derived>
  bool traverse(ASTVisitor* visitor) {
    Derived* derived = dynamic_cast<Derived*>(this);
    if (!ASTNode::visitFromTop(visitor, derived)) {
      return false;
    }
    ASTNodeList child_nodes;
    if (getChildNodes(&child_nodes)) {
      for (auto* child : child_nodes) {
        if(!child->accept(visitor)) {
          return false;
        }
      }
    }
    return ASTNode::endVisitFromTop(visitor, derived);
  }

  template <typename Derived>
  static bool visitFromTop(ASTVisitor* visitor, Derived* derived) {
    if (visitor->isVisitFromTop()) {
      auto* base = derived->toBaseNode();
      if (base) {
        if (!visitFromTop(visitor, base)) {
          return false;
        }
      }
    }
    return visitor->visit(derived);
  }

  template <typename Derived>
  static bool endVisitFromTop(ASTVisitor* visitor, Derived* derived) {
    if (visitor->isEndVisitFromTop()) {
      auto* base = derived->toBaseNode();
      if (base) {
        if (!endVisitFromTop(visitor, base)) {
          return false;
        }
      }
    }
    return visitor->endVisit(derived);
  }

 public:
  virtual ASTNodeType getNodeType() const = 0;
  std::string getNodeTypeName() const {
    return ASTNodeType_Name(getNodeType());
  }
  /**
   * @brief Get this pointer as an implementation of ASTNode interface.
   * @return T pointer if this instance's type is T. Otherwise check error.
   */
  template <typename T>
  T* getImpl() const {
    T* impl = dynamic_cast<T*>(const_cast<ASTNode*>(this));
    CHECK_MSG(impl, getNodeTypeName().c_str());
    return impl;
  }

  void setParent(ASTNode* parent) { parent_ = parent; }
  ASTNode* getParent() const { return parent_; }

  //void setSymbol(Symbol* symbol) { symbol_.reset(symbol); }
  //Symbol* getSymbol() const { return symbol_.get(); }

  void setLocation(const location& loc) { location_ = loc; }
  const location& getLocation() { return location_; }

  typedef std::vector<ASTNode*> ASTNodeList;

  /**
   * @brief Get the child ast nodes.
   *
   * @return true if has children. Otherwise return false.
   */
  virtual bool getChildNodes(ASTNodeList*) { return false; };

  virtual std::string toString() const { return getNodeTypeName(); }

  void setSymbol(Symbol* symbol) {
    CHECK(symbol);
    symbol_ = symbol;
  }
  Symbol* getSymbol() const {
    return symbol_;
  }

  ASTAttribute& getAttr() {
    return attr_;
  }

  const ASTAttribute& getAttr() const {
    return attr_;
  }

 protected:
  /** Parent ast node. */
  ASTNode* parent_;
  /** The location of this AST node in the source file. */
  location location_;
  Symbol* symbol_;
  ASTAttribute attr_;
};

}  // namespace flang



#endif
