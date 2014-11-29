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
  yylval->lineNum = lineno();
  return Token::WHILE;
}

if {
  yylval->lineNum = lineno();
  return Token::IF;
}

else {
  yylval->lineNum = lineno();
  return Token::ELSE;
}

break {
  yylval->lineNum = lineno();
  return Token::BREAK;
}

def {
  yylval->lineNum = lineno();
  return Token::DEF;
}

class {
  yylval->lineNum = lineno();
  return Token::CLASS;
}

print {
  yylval->lineNum = lineno();
  return Token::PRINT;
}

return {
  yylval->lineNum = lineno();
  return Token::RETURN;
}

this {
  yylval->lineNum = lineno();
  return Token::THIS;
}

new {
  yylval->lineNum = lineno();
  return Token::NEW;
}

int {
  yylval->lineNum = lineno();
  return Token::INT;
}

bool {
  yylval->lineNum = lineno();
  return Token::BOOL;
}

char {
  yylval->lineNum = lineno();
  return Token::CHAR;
}

string {
  yylval->lineNum = lineno();
  return Token::STRING;
}

true {
  yylval->lineNum = lineno();
  return Token::TRUE;
}

false {
  yylval->lineNum = lineno();
  return Token::FALSE;
}

or {
  yylval->lineNum = lineno();
  return Token::OR;
}

and {
  yylval->lineNum = lineno();
  return Token::AND;
}

[ \n\r\t] ;

{number} {
  yylval->intVal = atoi(yytext);
  return Token::NUMBER;
}

{op} {
  yylval->lineNum = lineno();
  return *yytext;
}

{string} {
  yylval->strIdx = g_strVals.size();
  g_strVals.push_back( string( yytext+1, yyleng-2 ) );
  return Token::STR;
}

{char} {
  yylval->charVal = *yytext;
  return Token::CHARVAL;
}

{identifier} {
  g_strVals.push_back( string( yytext, yyleng ) );
  yylval->strIdx = g_strVals.size() - 1;
  return Token::ID;
}

"<=" {
  yylval->lineNum = lineno();
  return Token::LE;
}

">=" {
  yylval->lineNum = lineno();
  return Token::GE;
}

"==" {
  yylval->lineNum = lineno();
  return Token::EQ;
}

"!=" {
  yylval->lineNum = lineno();
  return Token::NE;
}

. {
  printf("Unknown char at line %d : %c\n", lineno(), yytext[0]);
};

%%

