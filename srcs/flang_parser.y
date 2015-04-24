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
%parse-param {SyntaxTree* syntax_tree}

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
  StmtNode*        stmt_node;
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
%type <ast_node> program simple_program
%type <stmt_node> stmt simple_stmt complex_stmt
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
  syntax_tree->setRoot($1);
} | {
  syntax_tree->setRoot(new EmptyNode());
  $$ = syntax_tree->getRoot();
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
  $$ = new ProgramNode();
  $$->setLineNum(scanner.lineno());
  $$->addStatement($1);
} | simple_stmt_list simple_stmt {
  $1->addStatement($2);
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
  $$ = new IntValNode($1);
  $$->setLineNum(scanner.lineno());
} | TRUE {
  $$ = new BoolValNode(true);
  $$->setLineNum(scanner.lineno());
} | FALSE {
  $$ = new BoolValNode(false);
  $$->setLineNum( scanner.lineno() );
} | STR_VAL {
  $$ = new StringValNode( *($1) );
  $$->setLineNum( scanner.lineno() );
} | CHAR_VAL {
  $$ = new CharValNode($1);
  $$->setLineNum( scanner.lineno() );
}| expression '+' expression {
  $$ = new BinaryExpNode(BinaryExpNode::OP_ADD, $1, $3);
  $$->setLineNum( scanner.lineno() );
} | expression '-' expression {
  $$ = new BinaryExpNode(BinaryExpNode::OP_SUB, $1, $3);
  $$->setLineNum( scanner.lineno() );
} | expression '*' expression {
  $$ = new BinaryExpNode(BinaryExpNode::OP_MUL, $1, $3);
  $$->setLineNum( scanner.lineno() );
} | expression '/' expression {
  $$ = new BinaryExpNode(BinaryExpNode::OP_DIV, $1, $3);
  $$->setLineNum( scanner.lineno() );
} | expression '<' expression {
  $$ = new BinaryExpNode(BinaryExpNode::OP_LT, $1, $3);
  $$->setLineNum( scanner.lineno() );
} | expression AND  expression {
  $$ = new BinaryExpNode(BinaryExpNode::OP_AND, $1, $3);
  $$->setLineNum( scanner.lineno() );
} | expression EQ  expression {
  $$ = new BinaryExpNode(BinaryExpNode::OP_OR,$1, $3);
  $$->setLineNum( scanner.lineno() );
} | '(' expression ')' {
  $$ = $2;
} | call {
  $$ = $1;
} | NEW simple_name {
  $$ = new NewNode($2);
} | simple_name {
  $$ = $1;
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
  $$->setDataType($1);
};

var_declaration_fragment : ID '=' expression {
  $$ = new VarDeclarationFragmentNode(*$1, $3);
} | ID {
  $$ = new VarDeclarationFragmentNode(*$1, nullptr);
};

assignment : simple_name '=' expression {
  $$ = new AssignNode($1, $3);
}

type : INT_TYPE {
  $$ = new IntTypeNode();
} | BOOL_TYPE {
  $$ = new BoolTypeNode();
} | CHAR_TYPE {
  $$ = new CharTypeNode();
} | STR_TYPE {
  $$ = new StringTypeNode();
};

if_stmt : IF '(' expression ')' '{'
            simple_program
          '}' ELSE '{'
            simple_program
          '}' {
  $$ = new IfNode($3, $6, $10);
  $$->setLineNum($1);
} | IF '(' expression ')' '{' simple_program '}' ELSE  stmt {
  $$ = new IfNode($3, $6, $9);
  $$->setLineNum($1);
} | IF '(' expression ')'  stmt ELSE '{' simple_program '}' {
  $$ = new IfNode($3, $5, $8);
  $$->setLineNum($1);
} | IF '(' expression ')'  stmt  ELSE stmt {
  $$ = new IfNode($3, $5, $7);
  $$->setLineNum($1);
} | IF '(' expression ')' '{' simple_program '}' %prec IFX {
  $$ = new IfNode($3, $6, nullptr);
  $$->setLineNum($1);
} | IF '(' expression ')'  stmt  %prec IFX {
  $$ = new IfNode($3, $5, nullptr);
  $$->setLineNum($1);
};

while_stmt : WHILE '(' expression ')' '{' simple_program '}' {
  $$ = new WhileNode($3, $6);
  $$->setLineNum($1);
} | WHILE '(' expression ')' stmt {
  $$ = new WhileNode($3, $5);
  $$->setLineNum( $1 );
};

function : DEF ID '(' func_param_list ')' ret_type '{' simple_program '}' {
  $$ = $4;
  $$->setName(*($2));
  $$->setReturnType($6);
  $$->setBody($8);
  $$->setLineNum($1);
} | DEF ID '(' ')' ret_type '{'simple_program '}' {
  $$ = new FuncNode();
  $$->setBody($7);
  $$->setName(*$2);
  $$->setReturnType($5);
  $$->setLineNum($1);
};

ret_type : type {
  $$ = $1;
} | {
  $$ = new VoidTypeNode();
};

func_param_list : func_param_list ',' type ID {
  $$ = $1;
  VarDeclarationNode* var_decl_node = new VarDeclarationNode();
  VarDeclarationFragmentNode* var_decl_fragment_node = new
      VarDeclarationFragmentNode(*($4), nullptr);
  var_decl_node->setDataType($3);
  var_decl_node->addVarDeclFragment(var_decl_fragment_node);
  $$->addParameter(var_decl_node);
} | type ID {
  $$ = new FuncNode();
  VarDeclarationNode* var_decl_node = new VarDeclarationNode();
  VarDeclarationFragmentNode* var_decl_fragment_node = new
      VarDeclarationFragmentNode(*($2), nullptr);
  var_decl_node->setDataType($1);
  var_decl_node->addVarDeclFragment(var_decl_fragment_node);
  $$->addParameter(var_decl_node);
};

call : ID '(' call_param_list ')' {
  $$ = $3;
  $$->setName(*($1));
};

call_param_list : param_list {
  $$ = $1;
} | {
  $$ = new CallNode();
};

param_list : param_list ',' expression {
  $$ = $1;
  $$->addParameter($3);
} | expression {
  $$ = new CallNode();
  $$->addParameter($1);
  $$->setLineNum(scanner.lineno());
};

class : CLASS ID '{' class_stmt_list  '}' {
  $$ = $4;
  $$->setName(*($2));
  $$->setLineNum($1);
} | CLASS ID ':' simple_name '{' class_stmt_list '}' {
  $$ = $6;
  $$->setBaseClass($4);
  $$->setName(*($2));
  $$->setLineNum($1);
};

class_stmt_list : class_stmt_list var_declaration ';' {
  $$ = $1;
  $$->addVarDeclaration($2);
} | class_stmt_list function {
  $$ = $1;
  // create a new class function to wrap a global function
  // add the function to the class
  $$->addFunction($2);
} | {
  $$ = new ClassNode();
};

%%

void flang::FlangParser::error(const std::string& err_message) {
   std::cerr << "Error: " << err_message << "\n";
}
