#include <sstream>

#include "flang_scanner.h"
#include "test/test.h"

namespace flang {

class FlangScannerTest : public Test {
};

TEST_F(FlangScannerTest, testScanID) {
  std::istringstream is_stream("aaa bbb");
  FlangScanner scanner(&is_stream);
  FlangParser::semantic_type yylval;
  FlangParser::location_type yylloc;
  yylloc.step();
  ASSERT_EQ(FlangParser::token_type::ID, scanner.yylex(&yylval, &yylloc));
  delete yylval.str_val;
  position begin(nullptr, 1, 3);
  EXPECT_EQ(begin, yylloc.begin);

}

}  // namespace flang
