#include <memory>
#include <sstream>
#include <string>

#include "test/test.h"
#include "syntax_tree/ast_node_all.h"
#include "front_end/flang_parser.h"
#include "front_end/flang_scanner.h"
#include "symbol_table/symbol_table.h"
#include "exception/exception_manager.h"
#include "type_checker/type_checker.h"

namespace flang {

class TypeCheckerTest : public Test {
 protected:
  void SetUp() override {
    filename_ = "test.f";
    //scanner_.reset(new FlangScanner(&ss_));
    //parser_.reset(new FlangParser(scanner_.get(), &ast_, &filename_));
    type_checker_.reset(new TypeChecker(&symbol_table_, &except_manager_));
  }

  bool parseAndCheckType(const std::string& src) {
    std::istringstream iss(src);
    FlangScanner scanner(&iss);
    FlangParser parser(&scanner, &ast_, &filename_);
    parser.parse();
    return ast_.accept(type_checker_.get());
  }

  //std::unique_ptr<FlangScanner> scanner_;
  //std::unique_ptr<FlangParser> parser_;
  //std::istringstream ss_
  SyntaxTree ast_;
  std::string filename_;
  SymbolTable symbol_table_;
  ExceptionManager except_manager_;
  std::unique_ptr<TypeChecker> type_checker_;
};

TEST_F(TypeCheckerTest, testVisitIfNode) {
  std::string src =
      "if (true) {"
      "} else {"
      "}";
  ASSERT_TRUE(parseAndCheckType(src));
  src =
      "if (1) {"
      "} else {"
      "}";
  ASSERT_FALSE(parseAndCheckType(src));
  ASSERT_EQ(1, except_manager_.getExceptionList().size());
  for (auto& except : except_manager_.getExceptionList()) {
    LOG_INFO(except.getMessage());
  }
}

}  // namespace flang
