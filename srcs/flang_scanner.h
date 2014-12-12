#ifndef FLANG_SCANNER_H_
#define FLANG_SCANNER_H_

#include <istream>

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

// Because we create our own scanner class instead of yyFlexLexer by using
// %option yyclass="FLangScanner" in flang_scanner.l, we should set the
// FlangScanner::yylex() as the declared function for the yylex() implementation
// in the generated file flang_scanner.cpp. The cpp file also provides a dummy
// implementation for yyFlexLexer::yylex() in addition to the one that does the
// real work.
// flang_scanner.cpp:
// int yyFlexLexer::yylex() {
//   // Nothing to do
// }
//
// YY_DECL {
//   // Do the real work
// }
//
#undef YY_DECL
#define YY_DECL int flang::FlangScanner::yylex()

#include "flang_parser.h"

namespace flang {

class FlangScanner : public yyFlexLexer{
 public:
  FlangScanner(std::istream *in)
      : yyFlexLexer(in), yylval( nullptr ) {}

  // The scan function which is passed in the value struct given by FlangParser
  // and defined by %union section in flang_parser.y.
  // Actually it's the yylval in C verion scanner.
  int yylex(FlangParser::semantic_type *lval) {
    yylval = lval;
    return( yylex() );
  }

 private:
  // Hide this one from public view
  int yylex();
  // yyval ptr
  FlangParser::semantic_type *yylval;
};

}  // namespace flang

#endif
