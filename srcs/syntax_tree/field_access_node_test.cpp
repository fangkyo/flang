#include <memory>

#include "syntax_tree/field_access_node.h"
#include "syntax_tree/primitive_node.h"
#include "test/test.h"

namespace flang {

class FieldAccessNodeTest : public Test {
};

TEST_F(FieldAccessNodeTest, testToNameNode) {
  FieldAccessNode* fa1 = new FieldAccessNode();
  fa1->setExpression(new SimpleNameNode("org"));
  fa1->setFieldName(new SimpleNameNode("flang"));
  FieldAccessNode* fa2 = new FieldAccessNode();
  fa2->setExpression(fa1);
  fa2->setFieldName(new SimpleNameNode("hello"));
  std::unique_ptr<FieldAccessNode> fa3(new FieldAccessNode());
  fa3->setExpression(fa2);
  fa3->setFieldName(new SimpleNameNode("world"));
  std::unique_ptr<NameNode> name_node(fa3->toNameNode());
  EXPECT_EQ(ASTNodeType::QUALIFIED_NAME_NODE, name_node->getNodeType());
  EXPECT_EQ("org.flang.hello.world", name_node->toString());
}

TEST_F(FieldAccessNodeTest, testThrowNameNodeCastError) {
  std::string filename = "test.f";
  location loc;
  loc.begin.filename = loc.end.filename = &filename;
  std::unique_ptr<FieldAccessNode> fa1(new FieldAccessNode());
  fa1->setLocation(loc);
  fa1->setExpression(new IntValNode(3));
  fa1->setFieldName(new SimpleNameNode("flang"));
  EXPECT_THROW(fa1->toNameNode(), NameNodeCastError*);
}

}  // namespace flang 
