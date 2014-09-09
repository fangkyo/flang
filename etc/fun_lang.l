%{
#include <cstdio>
#include <cstdlib>

#include <string>
#include <vector>

#include "syntax_tree.h"
#include "data_type.h"
#include "exp_node.h"
#include "print_node.h"
#include "ctrl_node.h"
#include "func_node.h"
#include "class_node.h"
#include "fun_lang_yacc.h"

using namespace std;

// 存储lex识别的字符串token( identifier 或者 string )
vector<string> g_strVals;

string& getStrVal( int idx ) {
	return g_strVals[idx];
}

%}

%option yylineno
%option noyywrap

number [0-9]+
op [-+*/%(){}<>.;=!,:] 
identifier [a-zA-Z_][a-zA-Z0-9_]*
string \"[^"]*\"
char '.'

%%

while                { yylval.lineNum = yylineno; return WHILE; }
if                   { yylval.lineNum = yylineno; return IF; }
else			           { yylval.lineNum = yylineno; return ELSE; }
break                { yylval.lineNum = yylineno; return BREAK; }
def                  { yylval.lineNum = yylineno; return DEF;  }
class                { yylval.lineNum = yylineno; return CLASS; }
print                { yylval.lineNum = yylineno; return PRINT; }
return               { yylval.lineNum = yylineno; return RETURN; }
this                 { yylval.lineNum = yylineno; return THIS; }
new                  { yylval.lineNum = yylineno; return NEW; }

int                  { yylval.lineNum = yylineno; return INT;  }
bool                 { yylval.lineNum = yylineno; return BOOL; }
char                 { yylval.lineNum = yylineno; return CHAR; }
string               { yylval.lineNum = yylineno; return STRING; }
true                 { yylval.lineNum = yylineno; return TRUE;  }
false                { yylval.lineNum = yylineno; return FALSE; }
or                   { yylval.lineNum = yylineno; return OR; }
and                  { yylval.lineNum = yylineno; return AND; }

[ \n\r\t]            ;

{number} { 
	yylval.intVal = atoi(yytext);
	return NUMBER; 
}

{op} { 
  yylval.lineNum = yylineno;
  return *yytext; 
}

{string} {
  yylval.strIdx = g_strVals.size();
  g_strVals.push_back( string( yytext+1, yyleng-2 ) );
  return STR;
}

{char} {
  yylval.charVal = *yytext;
  return CHARVAL;
}


{identifier} {
  g_strVals.push_back( string( yytext, yyleng ) );
  yylval.strIdx = g_strVals.size() - 1;
  return ID; 
}

"<="				 { yylval.lineNum = yylineno; return LE; }
">="				 { yylval.lineNum = yylineno; return GE; }
"==" 				 { yylval.lineNum = yylineno; return EQ;  }
"!="				 { yylval.lineNum = yylineno; return NE; }

.            { printf("Unknown char at line %d : %c\n", yylineno, yytext[0]); };

%%

