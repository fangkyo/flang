%skeleton "lalr1.cc"
%require  "3.0"
%debug
%defines
%define api.namespace {flang}
%define parser_class_name {FlangParser}

%code requires{

#include "syntax_tree/syntax_tree.h"

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

  ASTNode* ast_node;
  VarDeclarationNode* var_decl_node;
  VarDeclarationFragmentNode* var_decl_fragment_node;
  ProgramNode* program_node;
  ExpNode* exp_node;
  DataTypeNode*    data_type_node;
  IfNode*          if_node;
  WhileNode*       while_node;
  FuncNode*        func_node;
  CallNode*        call_node;
  ClassNode*       class_node;
  AssignNode*      assign_node;
  SimpleNameNode*  simple_name_node;
}

%token <int_val> INT_VAL
%token <char_val> CHAR_VAL
%token <bool_val> BOOL_VAL
%token <str_val> STR_VAL ID

%token <lineno> WHILE IF PRINT BREAK DEF CLASS RETURN THIS NEW
%token <lineno> BOOL_TYPE CHAR_TYPE STR_TYPE INT_TYPE TRUE FALSE 

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
%type <ast_node> program simple_program stmt simple_stmt complex_stmt
%type <exp_node> expression
%type <var_decl_node> var_declaration
%type <var_decl_fragment_node> var_declaration_fragment
%type <program_node> stmt_list simple_stmt_list
%type <data_type_node> type ret_type
%type <if_node> if_stmt
%type <while_node> while_stmt
%type <func_node>  function func_param_list
%type <call_node>  call_param_list call param_list
%type <class_node> class  class_stmt_list
%type <assign_node> assignment
%type <simple_name_node> simple_name

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
  $$ = new ProgramNode();
  $$->setLineNum(scanner.lineno());
  $$->addStatement($1);
} | stmt_list stmt {
  $1->addStatement($2);
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
} | expression ';' {
  $$ = $1;
} | PRINT expression ';' {
  $$ = new PrintNode( $2 );
  $$->setLineNum( $1 );
} | RETURN expression ';' {
  $$ = new ReturnNode( $2 );
  $$->setLineNum( $1 );
} | RETURN ';' {
  $$ = new ReturnNode();
  $$->setLineNum( $1 );
} | BREAK ';' {
  $$ = new BreakNode();
  $$->setLineNum( $1 );
} | var_declaration ';' {
  $$ = $1;
} | if_stmt {
  $$ = $1;
} | while_stmt {
  $$ = $1;
} | assignment {
  $$ = $1;
};

expression : INT_VAL {
  $$ = new IntNode($1);
  $$->setLineNum(scanner.lineno());
} | TRUE {
  $$ = new BoolNode(true);
  $$->setLineNum(scanner.lineno());
} | FALSE {
  $$ = new BoolNode(false);
  $$->setLineNum( scanner.lineno() );
} | STR_VAL {
  $$ = new StringNode( *($1) );
  $$->setLineNum( scanner.lineno() );
} | CHAR_VAL {
  $$ = new CharNode($1);
  $$->setLineNum( scanner.lineno() );
}| expression '+' expression {
  $$ = new AddNode($1, $3);
  $$->setLineNum( scanner.lineno() );
} | expression '-' expression {
  $$ = new SubNode($1, $3);
  $$->setLineNum( scanner.lineno() );
} | expression '*' expression {
  $$ = new MulNode($1, $3);
  $$->setLineNum( scanner.lineno() );
} | expression '/' expression {
  $$ = new DivNode($1, $3);
  $$->setLineNum( scanner.lineno() );
} | expression '<' expression {
  $$ = new LtNode($1, $3);
  $$->setLineNum( scanner.lineno() );
} | expression AND  expression {
  $$ = new AndNode($1, $3);
  $$->setLineNum( scanner.lineno() );
} | expression EQ  expression {
  $$ = new EqNode($1, $3);
  $$->setLineNum( scanner.lineno() );
} | '(' expression ')' {
  $$ = $2;
} | call {
  $$ = $1;
} | NEW ID {
  $$ = new NewNode(*($2));
} | simple_name {
  $$ = $1
};

simple_name : ID {
  $$ = new SimpleNameNode(*$1);
};

var_declaration : var_declaration ',' var_declaration_fragment {
  $$ = $1;
  $$->addVarDeclFragment($3);
  $$->setLineNum(scanner.lineno());
} | type var_declaration_fragment {
  $$ = new VarDeclarationNode();
  $$->setDataTypeNode($1);
};

var_declaration_fragment : ID '=' expression {
  $$ = new VarDeclarationFragmentNode(*$1, $3);
} | ID {
  $$ = new VarDeclarationFragmentNode(*$1, nullptr);
};

assignment : ID '=' expression {
  $$ = new AssignNode(*$1, $3);
}

type : INT_TYPE {
  $$ = INT_TYPE_NODE;
} | BOOL_TYPE {
  $$ = BOOL_TYPE_NODE;
} | CHAR_TYPE {
  $$ = CHAR_TYPE_NODE;
} | STR_TYPE {
  $$ = STRING_TYPE_NODE;
} | ID {
  $$ = new ClassTypeNode(*($1));
  $$->setLineNum(scanner.lineno());
};

if_stmt : IF '(' expression ')' '{'
            simple_program
          '}' ELSE '{'
            simple_program
          '}' {
  $$ = new IfNode( $3, $6, $10 );
  $$->setLineNum( $1 );
} | IF '(' expression ')' '{' simple_program '}' ELSE  stmt {
  $$ = new IfNode( $3, $6, $9 );
  $$->setLineNum( $1 );
} | IF '(' expression ')'  stmt ELSE '{' simple_program '}' {
  $$ = new IfNode( $3, $5, $8 );
  $$->setLineNum( $1 );
} | IF '(' expression ')'  stmt  ELSE stmt {
  $$ = new IfNode( $3, $5, $7 );
  $$->setLineNum( $1 );
} | IF '(' expression ')' '{' simple_program '}' %prec IFX {
  $$ = new IfNode( $3, $6 );
  $$->setLineNum( $1 );
} | IF '(' expression ')'  stmt  %prec IFX {
  $$ = new IfNode( $3, $5 );
  $$->setLineNum( $1 );
};

while_stmt : WHILE '(' expression ')' '{' simple_program '}' {
  $$ = new WhileNode( $3, $6 );
  $$->setLineNum( $1 );
  g_collector.insert( $$ );
} | WHILE '(' expression ')' stmt {
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

call : simple_name '(' call_param_list ')' {
  $$ = $3;
  $$->setFuncName(*($1));
};

call_param_list : param_list {
  $$ = $1;
} | {
  $$ = new CallNode();
};

param_list : param_list ',' expression {
  $$ = $1;
  $$->addParam($3);
} | expression {
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

class_stmt_list : class_stmt_list var_declaration ';' {
  $$ = $1;
  $$->addVarDeclaration($2);
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
