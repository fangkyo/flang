/* This file generates class FlangScanner, which is the lexical analyzer
 * of flang.
 */
%{
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>

#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>

#include "exception/exception.h"
#include "flang_parser.h"
#include "flang_scanner.h"
#include "syntax_tree/syntax_tree.h"

/* typedef to make the returns for the tokens shorter */
typedef flang::FlangParser::token Token;

class IntegerCastError : public Error {
 public:
  IntegerCastError(
      const char* text, const std::string& filename, uint32_t lineno) :
      Error(filename, lineno) {
    boost::format fmt(
        "%1% can't be parse to integer, out of range [%2%, %3%].");
    fmt % text % INT64_MAX % INT64_MAX;
    setMessage(fmt.str());
  }
};

class DoubleCastError : public Error {
 public:
  DoubleCastError(
      const char* text, const std::string& filename, uint32_t lineno) :
      Error(filename, lineno) {
    boost::format fmt(
        "%1% can't be parsed to double, out of range [2.2E-308, 1.8E+308].");
    fmt % text;
    setMessage(fmt.str());
  }
};

%}

%option debug
%option yylineno
%option noyywrap
%option c++
%option yyclass="FlangScanner"

integer [0-9]+
double [0-9]*.[0-9]+
op [-+*/%(){}<>.;=!,:]
identifier [a-zA-Z_][a-zA-Z0-9_]*
string \"[^"]*\"
char '.'

%%

while {
  yylval->lineno = lineno();
  return Token::WHILE;
}

if {
  yylval->lineno = lineno();
  return Token::IF;
}

else {
  yylval->lineno = lineno();
  return Token::ELSE;
}

break {
  yylval->lineno = lineno();
  return Token::BREAK;
}

def {
  yylval->lineno = lineno();
  return Token::DEF;
}

class {
  yylval->lineno = lineno();
  return Token::CLASS;
}

print {
  yylval->lineno = lineno();
  return Token::PRINT;
}

return {
  yylval->lineno = lineno();
  return Token::RETURN;
}

this {
  yylval->lineno = lineno();
  return Token::THIS;
}

new {
  yylval->lineno = lineno();
  return Token::NEW;
}

int32 {
  yylval->lineno = lineno();
  return Token::INT32_TYPE;
}

int64 {
  yylval->lineno = lineno();
  return Token::INT64_TYPE;
}

bool {
  yylval->lineno = lineno();
  return Token::BOOL_TYPE;
}

char {
  yylval->lineno = lineno();
  return Token::CHAR_TYPE;
}

string {
  yylval->lineno = lineno();
  return Token::STR_TYPE;
}

true {
  yylval->lineno = lineno();
  return Token::TRUE;
}

false {
  yylval->lineno = lineno();
  return Token::FALSE;
}

or {
  yylval->lineno = lineno();
  return Token::OR;
}

and {
  yylval->lineno = lineno();
  return Token::AND;
}

[ \n\r\t] ;

{integer} {
  try {
    yylval->int64_val = boost::lexical_cast<int64_t>(yytext);
    yylval->lineno = lineno();
  } catch (const boost::bad_lexical_cast&) {
    IntegerCastError error(yytext, filename_, lineno());
    throw error;
  }
  return Token::INT_VAL;
}

{double} {
  try {
    yylval->float_val = boost::lexical_cast<double>(yytext);
  } catch (const boost::bad_lexical_cast&) {
    DoubleCastError error(yytext, filename_, lineno());
    throw error;
  }

}

{op} {
  yylval->lineno = lineno();
  return *yytext;
}

{string} {
  yylval->str_val = new std::string(yytext + 1, yyleng - 2);
  return Token::STR_VAL;
}

{char} {
  yylval->char_val = *yytext;
  return Token::CHAR_VAL;
}

{identifier} {
  yylval->str_val = new std::string(yytext, yyleng);
  return Token::ID;
}

"<=" {
  yylval->lineno = lineno();
  return Token::LE;
}

">=" {
  yylval->lineno = lineno();
  return Token::GE;
}

"==" {
  yylval->lineno = lineno();
  return Token::EQ;
}

"!=" {
  yylval->lineno = lineno();
  return Token::NE;
}

. {
  printf("Unknown char at line %d : %c\n", lineno(), yytext[0]);
};

%%

