/* This file generates class FlangScanner, which is the lexical analyzer
 * of flang.
 */
%{
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include "syntax_tree/syntax_tree.h"
#include "syntax_tree/data_type.h"
#include "syntax_tree/exp_node.h"
#include "syntax_tree/print_node.h"
#include "syntax_tree/ctrl_node.h"
#include "syntax_tree/func_node.h"
#include "syntax_tree/class_node.h"

#include "flang_parser.h"
#include "flang_scanner.h"

/* typedef flang::FLangParser::token FLangToken; */

// 存储lex识别的字符串token( identifier 或者 string )
// Tokens that recognized by lex.
std::vector<string> g_strVals;

std::string& getStrVal( int idx ) {
  return g_strVals[idx];
}
/* typedef to make the returns for the tokens shorter */
typedef flang::FlangParser::token Token;

%}

%option debug
%option yylineno
%option noyywrap
%option c++
%option yyclass="FlangScanner"

number [0-9]+
op [-+*/%(){}<>.;=!,:]
identifier [a-zA-Z][a-zA-Z0-9_]*
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

int {
  yylval->lineno = lineno();
  return Token::INT;
}

bool {
  yylval->lineno = lineno();
  return Token::BOOL;
}

char {
  yylval->lineno = lineno();
  return Token::CHAR;
}

string {
  yylval->lineno = lineno();
  return Token::STRING;
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

{number} {
  yylval->int_val = atoi(yytext);
  return Token::NUMBER;
}

{op} {
  yylval->lineno = lineno();
  return *yytext;
}

{string} {
  yylval->str_val = new std::string(yytext + 1, yyleng - 2);
  // g_strVals.size();
  /* g_strVals.push_back( string( yytext+1, yyleng-2 ) ); */
  return Token::STR;
}

{char} {
  yylval->char_val = *yytext;
  return Token::CHARVAL;
}

{identifier} {
  yylval->str_val = new std::string(yytext, yyleng);
  /* g_strVals.push_back( string( yytext, yyleng ) ); */
  /* yylval->strIdx = g_strVals.size() - 1; */
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

