/* This file generates class FlangScanner, which is the lexical analyzer
 * of flang.
 */
%{
#include <cstdio>
#include <cstdlib>
#include <string>

#include "flang_parser.h"
#include "flang_scanner.h"
#include "syntax_tree/syntax_tree.h"

/* typedef to make the returns for the tokens shorter */
typedef flang::FlangParser::token Token;

%}

%option debug
%option yylineno
%option noyywrap
%option c++
%option yyclass="FlangScanner"

integer [0-9]+
float [0-9]*.[0-9]+
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
  return Token::INT_TYPE;
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
  yylval->int_val = atoi(yytext);
  return Token::INT_VAL;
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

