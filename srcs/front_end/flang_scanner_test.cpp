#include <sstream>
#include <exception>

#include "exception/exception_manager.h"
#include "front_end/flang_scanner.h"
#include "test/test.h"

namespace flang {

class FlangScannerTest : public Test {
};

TEST_F(FlangScannerTest, testScanID) {
  std::istringstream is_stream("aaa bbb \n ccc ddd");
  FlangScanner scanner(&is_stream);
  FlangParser::semantic_type yylval;
  FlangParser::location_type yylloc;
  ASSERT_EQ(FlangParser::token_type::ID, scanner.yylex(&yylval, &yylloc));
  delete yylval.str_val;
  position begin1(nullptr, 1, 1);
  EXPECT_EQ(begin1, yylloc.begin);
  position end1(nullptr, 1, 4);
  EXPECT_EQ(end1, yylloc.end);

  ASSERT_EQ(FlangParser::token_type::ID, scanner.yylex(&yylval, &yylloc));
  EXPECT_EQ("bbb", *yylval.str_val);
  delete yylval.str_val;
  position begin2(nullptr, 1, 5);
  EXPECT_EQ(begin2, yylloc.begin);
  position end2(nullptr, 1, 8);
  EXPECT_EQ(end2, yylloc.end);

  ASSERT_EQ(FlangParser::token_type::ID, scanner.yylex(&yylval, &yylloc));
  EXPECT_EQ("ccc", *yylval.str_val);
  delete yylval.str_val;
  position begin3(nullptr, 2, 2);
  EXPECT_EQ(begin3, yylloc.begin);
  position end3(nullptr, 2, 5);
  EXPECT_EQ(end3, yylloc.end);

  ASSERT_EQ(FlangParser::token_type::ID, scanner.yylex(&yylval, &yylloc));
  EXPECT_EQ("ddd", *yylval.str_val);
  delete yylval.str_val;
  position begin4(nullptr, 2, 6);
  EXPECT_EQ(begin4, yylloc.begin);
  position end4(nullptr, 2, 9);
  EXPECT_EQ(end4, yylloc.end);
}

TEST_F(FlangScannerTest, testScanInteger) {
  std::istringstream is_stream(
      "1123   43435345435349999999999999");
  FlangScanner scanner(&is_stream);
  FlangParser::semantic_type yylval;
  std::string filename = "hello.txt";
  FlangParser::location_type yylloc(&filename);

  ASSERT_EQ(FlangParser::token_type::INT_VAL, scanner.yylex(&yylval, &yylloc));
  EXPECT_EQ(1123L, yylval.int_val);
  position begin1(&filename, 1, 1);
  EXPECT_EQ(begin1, yylloc.begin);
  position end1(&filename, 1, 5);
  EXPECT_EQ(end1, yylloc.end);

  EXPECT_THROW(scanner.yylex(&yylval, &yylloc), IntegerCastError*);
}

TEST_F(FlangScannerTest, testScanDouble) {
  std::istringstream is_stream("3.8");
  FlangScanner scanner(&is_stream);
  FlangParser::semantic_type yylval;
  std::string filename = "hello.txt";
  FlangParser::location_type yylloc(&filename);

  EXPECT_EQ(FlangParser::token_type::DOUBLE_VAL, scanner.yylex(&yylval, &yylloc));
  EXPECT_EQ(3.8, yylval.double_val);
}
}  // namespace flang
