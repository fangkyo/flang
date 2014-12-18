%skeleton "lalr1.cc"
%require  "3.0"
%debug
%defines
%define api.namespace {flang}
%define parser_class_name {FlangParser}

%code requires{

#include "base/types.h"
#include "syntax_tree/syntax_tree.h"
#include "syntax_tree/exp_node.h"
#include "syntax_tree/print_node.h"
#include "syntax_tree/ctrl_node.h"
#include "syntax_tree/func_node.h"
#include "syntax_tree/class_node.h"
#include "syntax_tree/declare_node.h"
#include "scope.h"

namespace flang {
  class FlangScanner;
}
}

%lex-param {FlangScanner& scanner}
%parse-param {FlangScanner& scanner}
%parse-param {SyntaxNode* &program}

%code {
#include <cstdio>
#include <iostream>
#include <string>

#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>

#include "flang_scanner.h"

using namespace std;
using namespace log4cxx;

LoggerPtr g_logger(Logger::getLogger("flang.scanner_parser"));

static int yylex(flang::FlangParser::semantic_type *yylval,
                 flang::FlangScanner &scanner) {
   return scanner.yylex(yylval);
}
}

%union {
  int   int_val; // integer value
  char  char_val; // char value
  bool  bool_val; // bool value
  std::string*   str_val; // string value
  int   lineno; // line number

  SyntaxNode*      syntax_node;
  DeclareNode*     declare_node;
  StmtListNode*    stmt_list_node;
  ExpNode*         exp_node;
  DataTypeNode*    data_type_node;
  IfNode*          if_node;
  WhileNode*       while_node;
  FuncNode*        func_node;
  CallNode*        call_node;
  ClassNode*       class_node;
  AssignNode*      assign_node;
}

%token <int_val> NUMBER
%token <char_val> CHARVAL
%token <bool_val> BOOLVAL
%token <str_val> STR ID

%token <lineno> WHILE IF PRINT BREAK DEF CLASS RETURN THIS NEW
%token <lineno> BOOL CHAR INT TRUE FALSE STRING

%destructor { if ($$)  {delete ($$); ($$) = nullptr; } }  <str_val>

%nonassoc IFX
%nonassoc ELSE

%right '='

%left AND
%left OR

%left EQ NE
%left GE LE '>' '<'
%left '+' '-'
%left '*' '/'

%right '!'

%nonassoc UMINUS
%type <syntax_node> program simple_program stmt simple_stmt complex_stmt
%type <exp_node> expr
%type <declare_node> declare var_list
%type <stmt_list_node> stmt_list simple_stmt_list
%type <data_type_node> type ret_type
%type <if_node> if_stmt
%type <while_node> while_stmt
%type <func_node>  function func_param_list
%type <call_node>  call_param_list call param_list
%type <class_node> class  class_stmt_list
%type <assign_node> declare_var

%start program

%%

program : stmt_list {
  $$ = $1;
  program = $1;
} | {
  $$ = NULL;
  program = NULL;
};

stmt_list : stmt {
  $$ = new StmtListNode();
  $$->setLineNum(scanner.lineno());
  $$->addStmt($1);
} | stmt_list stmt {
  $1->addStmt($2);
  $$ = $1;
};

stmt : simple_stmt {
  $$ = $1;
} | complex_stmt {
  $$ = $1;
};

simple_program : simple_stmt_list {
  $$ = $1;
} | {
  $$ = NULL;
};

simple_stmt_list : simple_stmt {
  $$ = new StmtListNode();
  $$->setLineNum(scanner.lineno());
  $$->addStmt($1);
} | simple_stmt_list simple_stmt {
  $1->addStmt($2);
};

complex_stmt : function {
  $$ = $1;
} | class {
  $$ = $1;
};

simple_stmt : ';' {
  $$ = NULL;
} | expr ';' {
  $$ = $1;
} | PRINT expr ';' {
  $$ = new PrintNode( $2 );
  $$->setLineNum( $1 );
} | RETURN expr ';' {
  $$ = new ReturnNode( $2 );
  $$->setLineNum( $1 );
} | RETURN ';' {
  $$ = new ReturnNode();
  $$->setLineNum( $1 );
} | BREAK ';' {
  $$ = new BreakNode();
  $$->setLineNum( $1 );
} | declare ';' {
  $$ = $1;
} | if_stmt {
  $$ = $1;
} | while_stmt {
  $$ = $1;
};

expr : NUMBER {
  $$ = new IntNode($1);
  $$->setLineNum(scanner.lineno());
} | TRUE {
  $$ = new BoolNode(true);
  $$->setLineNum(scanner.lineno());
} | FALSE {
  $$ = new BoolNode(false);
  $$->setLineNum( scanner.lineno() );
} | STR {
  $$ = new StringNode( *($1) );
  $$->setLineNum( scanner.lineno() );
} | CHARVAL {
  $$ = new CharNode($1);
  $$->setLineNum( scanner.lineno() );
} | ID {
  $$ = new VarRefNode(*($1));
  $$->setLineNum( scanner.lineno() );
} | ID '=' expr {
  VarRefNode* var = new VarRefNode(*($1));
  var->setLineNum(scanner.lineno());
  $$ = new AssignNode(var, $3);
  $$->setLineNum( scanner.lineno() );
} | expr '+' expr {
  $$ = new AddNode($1, $3);
  $$->setLineNum( scanner.lineno() );
} | expr '-' expr {
  $$ = new SubNode($1, $3);
  $$->setLineNum( scanner.lineno() );
} | expr '*' expr {
  $$ = new MulNode($1, $3);
  $$->setLineNum( scanner.lineno() );
} | expr '/' expr {
  $$ = new DivNode($1, $3);
  $$->setLineNum( scanner.lineno() );
} | expr '<' expr {
  $$ = new LtNode($1, $3);
  $$->setLineNum( scanner.lineno() );
} | expr AND  expr {
  $$ = new AndNode($1, $3);
  $$->setLineNum( scanner.lineno() );
} | expr EQ  expr {
  $$ = new EqNode($1, $3);
  $$->setLineNum( scanner.lineno() );
} | '(' expr ')' {
  $$ = $2;
} | call {
  $$ = $1;
} | NEW ID {
  $$ = new NewNode(*($2));
} | THIS '.' ID {
  $$ = new MemberVarRefNode(*($3));
};

declare : var_list declare_var {
  $$ = $1;
  $2->setVarDataTypeNode( $1->getDataTypeNode() );
  $$->addDeclare( $2 );
  $$->setLineNum( scanner.lineno() );
};

var_list : var_list declare_var ',' {
  $$ = $1;
  $2->setVarDataTypeNode( $1->getDataTypeNode() );
  $$->addDeclare( $2 );
  $$->setLineNum( scanner.lineno() );
} | type {
  $$ = new DeclareNode();
  $$->setDataTypeNode($1);
  $$->setLineNum( scanner.lineno() );
};

declare_var : ID {
  VarNode* var = new VarDeclareNode( *($1) );
  var->setLineNum( scanner.lineno() );
  $$ = new AssignNode( var );
  $$->setLineNum( scanner.lineno() );
} | ID '=' expr {
  VarNode* var = new VarDeclareNode(*($1));
  var->setLineNum( scanner.lineno() );
  $$ = new AssignNode( var, $3 );
  $$->setLineNum( scanner.lineno() );
};

type : INT {
  $$ = INT_TYPE_NODE;
} | BOOL {
  $$ = BOOL_TYPE_NODE;
} | CHAR {
  $$ = CHAR_TYPE_NODE;
} | STRING {
  $$ = STRING_TYPE_NODE;
} | ID {
  $$ = new ClassTypeNode( *($1) );
  $$->setLineNum( scanner.lineno());
};

if_stmt : IF '(' expr ')' '{'
            simple_program
          '}' ELSE '{'
            simple_program
          '}' {
  $$ = new IfNode( $3, $6, $10 );
  $$->setLineNum( $1 );
} | IF '(' expr ')' '{' simple_program '}' ELSE  stmt {
  $$ = new IfNode( $3, $6, $9 );
  $$->setLineNum( $1 );
} | IF '(' expr ')'  stmt ELSE '{' simple_program '}' {
  $$ = new IfNode( $3, $5, $8 );
  $$->setLineNum( $1 );
} | IF '(' expr ')'  stmt  ELSE stmt {
  $$ = new IfNode( $3, $5, $7 );
  $$->setLineNum( $1 );
} | IF '(' expr ')' '{' simple_program '}' %prec IFX {
  $$ = new IfNode( $3, $6 );
  $$->setLineNum( $1 );
} | IF '(' expr ')'  stmt  %prec IFX {
  $$ = new IfNode( $3, $5 );
  $$->setLineNum( $1 );
};

while_stmt : WHILE '(' expr ')' '{' simple_program '}' {
  $$ = new WhileNode( $3, $6 );
  $$->setLineNum( $1 );
  g_collector.insert( $$ );
} | WHILE '(' expr ')' stmt {
  $$ = new WhileNode( $3, $5 );
  $$->setLineNum( $1 );
};

function : DEF ID '(' func_param_list ')' ret_type '{' simple_program '}' {
  $$ = $4;
  $$->setName( *($2));
  $$->setRetType($6);
  $$->setBody($8);
  $$->setLineNum($1);
} | DEF ID '(' ')' ret_type '{'simple_program '}' {
  $$ = new GlobalFuncNode(*($2), $5, $7);
  $$->setLineNum($1);
};

ret_type : type {
  $$ = $1;
} | {
  $$ = VOID_TYPE_NODE;
};

func_param_list : func_param_list ',' type ID {
  $$ = $1;
  $$->addParam(VarNode(*($4), $3));
} | type ID {
  $$ = new GlobalFuncNode();
  $$->addParam(VarNode(*($2), $1));
};

call : ID '(' call_param_list ')' {
  $$ = $3;
  $$->setFuncName(*($1));
} | ID '.' ID '(' call_param_list ')' {
  $$ = $5;
  $$->setLineNum($<lineno>2);
  $$->setFuncName(*($3));
  $$->setMemberFuncHint(true);
  $$->setCallerName(*($1));
} | THIS '.' ID '(' call_param_list ')' {
  $$ = $5;
  $$->setLineNum($<lineno>2);
  $$->setFuncName(*($3));
  $$->setMemberFuncHint(true);
};

call_param_list : param_list {
  $$ = $1;
} | {
  $$ = new CallNode();
};

param_list : param_list ',' expr {
  $$ = $1;
  $$->addParam($3);
} | expr {
  $$ = new CallNode();
  $$->addParam($1);
  $$->setLineNum(scanner.lineno());
};

class : CLASS ID '{' class_stmt_list  '}' {
  $$ = $4;
  $$->setName(*($2));
  $$->setLineNum($1);
} | CLASS ID ':' ID '{' class_stmt_list '}' {
  $$ = $6;
  $$->setParentName(*($4));
  $$->setName(*($2));
  $$->setLineNum($1);
};

class_stmt_list : class_stmt_list declare ';' {
  $$ = $1;
  $$->addVarDeclare($2);
} | class_stmt_list function {
  $$ = $1;
  // create a new class function to wrap a global function
  ClassFuncNode* classFunc = new ClassFuncNode($1, $2);
  // add the function to the class
  $$->addFuncion(classFunc);
} | {
  $$ = new ClassNode();
};

%%

void flang::FlangParser::error(const std::string& err_message) {
   std::cerr << "Error: " << err_message << "\n";
}
