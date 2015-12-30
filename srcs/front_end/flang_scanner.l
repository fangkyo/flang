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

#include "exception/exception_manager.h"
#include "front_end/flang_parser.h"
#include "front_end/flang_scanner.h"
#include "syntax_tree/syntax_tree.h"

/* typedef to make the returns for the tokens shorter */
typedef flang::FlangParser::token Token;

// static
log4cxx::LoggerPtr flang::FlangScanner::logger_(log4cxx::Logger::getLogger("flang.scanner"));


void flang::FlangScanner::LexerError(const char* msg) {
  throw new flang::FlexError(msg, *loc_);
}


/* The following paragraph suffices to track locations accurately. Each time
 * yylex is invoked, the begin position is moved onto the end position. */
#define YY_USER_ACTION \
  yylloc->columns(yyleng); \
  this->loc_ = yylloc;

%}

%option debug
%option yylineno
%option noyywrap
%option c++
%option batch
%option stack
%option yyclass="FlangScanner"

integer [0-9]+
double [0-9]*\.[0-9]+
op [-+*/%(){}<>.;=!,:$~]
identifier [a-zA-Z_][a-zA-Z0-9_]*
string \"[^"]*\"
char '.'

%%

%{
  // Code to place at the beginning of yylex().
  // Reset location.
  yylloc->step();
%}


while {
  return Token::WHILE;
}

if {
  return Token::IF;
}

else {
  return Token::ELSE;
}

break {
  return Token::BREAK;
}

continue {
  return Token::CONTINUE;
}

def {
  return Token::DEF;
}

class {
  return Token::CLASS;
}

print {
  return Token::PRINT;
}

return {
  return Token::RETURN;
}

this {
  return Token::THIS;
}

new {
  return Token::NEW;
}

int32 {
  return Token::INT32_TYPE;
}

int64 {
  return Token::INT64_TYPE;
}

bool {
  return Token::BOOL_TYPE;
}

char {
  return Token::CHAR_TYPE;
}

string {
  return Token::STR_TYPE;
}

double {
  return Token::DOUBLE_TYPE;
}

true {
  return Token::TRUE;
}

false {
  return Token::FALSE;
}

or {
  return Token::OR;
}

and {
  return Token::AND;
}

import {
  return Token::IMPORT;
}

as {
  return Token::AS;
}

[ \r\t]+ {
  yylloc->step();
}

[\n]+ {
  // Reset yylloc to the first column of next line
  yylloc->lines(YYLeng());
  yylloc->step();
}

{integer} {
  try {
    yylval->int_val = boost::lexical_cast<int64_t>(yytext);
  } catch (const boost::bad_lexical_cast&) {
    throw new IntegerCastError(yytext, *yylloc);
    yylval->int_val = 0;
  }
  return Token::INT_VAL;
}

{double} {
  try {
    yylval->double_val = boost::lexical_cast<double>(yytext);
  } catch (const boost::bad_lexical_cast&) {
    throw new DoubleCastError(yytext, *yylloc);
    yylval->double_val = 0.0;
  }
  return Token::DOUBLE_VAL;
}

{op} {
  return yytext[0];
}

{string} {
  yylval->str_val = new std::string(yytext + 1, yyleng - 2);
  return Token::STR_VAL;
}

{char} {
  yylval->char_val = yytext[1];
  return Token::CHAR_VAL;
}

{identifier} {
  yylval->str_val = new std::string(yytext, yyleng);
  return Token::ID;
}

"<=" {
  return Token::LE;
}

">=" {
  return Token::GE;
}

"==" {
  return Token::EQ;
}

"!=" {
  return Token::NE;
}

. {
  boost::format fmt("Unknow char '%1%'.");
  std::string error = boost::str(fmt % yytext[0]);
  LexerError(error.c_str());
};

%%
