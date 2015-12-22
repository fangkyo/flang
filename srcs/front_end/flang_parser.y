%skeleton "lalr1.cc"
%require  "3.0"
%debug
%defines
%locations
%define api.namespace {flang}
%define parser_class_name {FlangParser}

%code requires{

#include "syntax_tree/syntax_tree.h"

namespace flang {
  class FlangScanner;
}
}

%parse-param {FlangScanner& scanner}
%parse-param {SyntaxTree* syntax_tree}
%parse-param {std::string* filename}
%initial-action {
  @$.begin.filename = @$.end.filename = filename;
}

%code {
#include <cstdio>
#include <iostream>
#include <string>

#include <log4cxx/logger.h>

#include "exception/exception.h"
#include "flang_scanner.h"

using namespace std;

#undef yylex
// Redefine the default yylex function used in parser
#define yylex scanner.yylex

}

%union {
  int64_t int64_val; // integer value
  char  char_val; // char value
  bool  bool_val; // bool value
  std::string*   str_val; // string value
  double double_val; // double value
  int   lineno; // line number

  ASTNode* ast_node;
  VarDeclNode* var_decl_node;
  VarDeclFragmentNode* var_decl_fragment_node;
  ProgramNode* program_node;
  ExpNode* exp_node;
  TypeNode* type_node;
  IfNode* if_node;
  WhileNode* while_node;
  FuncNode* func_node;
  CallNode* call_node;
  ClassNode* class_node;
  AssignNode* assign_node;
  NameNode* name_node;
  QualifiedNameNode* qualified_name_node;
  SimpleNameNode* simple_name_node;
  StmtListNode* stmt_list_node;
  StmtNode* stmt_node;
  BlockNode* block_node;
  ImportListNode* import_list_node;
  ImportNode* import_node;
  ParamListNode* param_list_node;
  FieldAccessNode* field_access_node;
  ReturnNode* return_node;
  ClassBodyDeclNode* class_body_decl_node;
  ConstructorNode* constructor_node;
  DestructorNode* destructor_node;

}

%token <int64_val> INT_VAL
%token <char_val> CHAR_VAL
%token <bool_val> BOOL_VAL
%token <str_val> STR_VAL ID
%token <double_val> DOUBLE_VAL

%token <lineno> WHILE IF PRINT BREAK DEF CLASS RETURN THIS NEW CONTINUE
%token <lineno> BOOL_TYPE CHAR_TYPE STR_TYPE INT32_TYPE INT64_TYPE TRUE FALSE
%token <lineno> DOUBLE_TYPE
%token <lineno> IMPORT AS

%destructor { delete ($$); }  <str_val>

%nonassoc IFX
%nonassoc ELSE

%right '='

%left AND
%left OR

%left EQ NE
%left GE LE '>' '<'
%left '+' '-'
%left '*' '/'
%left '.'

%right '!'

%nonassoc UMINUS
%type <program_node> program
%type <block_node> block
%type <stmt_node> stmt
%type <stmt_list_node> stmt_list
%type <exp_node> expr
%type <var_decl_node> var_decl
%type <var_decl_fragment_node> var_decl_fragment
%type <type_node> type ret_type
%type <if_node> if_stmt
%type <while_node> while_stmt
%type <func_node>  function func_param_list
%type <call_node>  call
%type <class_node> class  class_body
%type <assign_node> assignment
%type <simple_name_node> simple_name
%type <qualified_name_node> qualified_name
%type <name_node> name
%type <field_access_node> field_access
%type <param_list_node> param_list
%type <import_list_node> import_list
%type <import_node> import
%type <return_node> return_stmt
%type <class_body_decl_node> class_body_decl
%type <constructor_node> constructor
%type <destructor_node> destructor

%start program

%%

program : import_list stmt_list {
  $$ = new ProgramNode();
  $$->setLocation(@$);
  $$->setImportList($1);
  $$->setStmtList($1);
  syntax_tree->setRoot($$);
};

import_list : import_list import {
  $$ = $1;
  $$->setLocation(@$);
  $$->addImport($2);
} | {
  $$ = new ImportList();
  $$->setLocation(@$);
};

import : IMPORT name '\n' {
  $$ = new ImportNode();
  $$->setPackage($1);
} | IMPORT name AS simple_name '\n' {
  $$ = new ImportNode();
  $$->setPackage($1);
  $$->setAlias($4);
};

stmt_list : stmt_list  stmt {
  $$ = $1;
  $$->setLocation(@$);
  $$->addStatement(stmt);
} | {
  $$ = new StmtListNode();
  $$->setLocation(@$);
}


stmt : expr ';' {
  $$ = $1;
  $$->setLocation(@$);
} | PRINT expr ';' {
  $$ = new PrintNode($2);
  $$->setLocation(@$);
} | return_stmt {
  $$ = $1;
  $$->setLocation(@$);
} | BREAK ';' {
  $$ = new BreakNode();
  $$->setLocation(@$);
} | CONTINUE ';' {
  $$ = new ContinueNode();
  $$->setLocation(@$);
} | var_decl ';' {
  $$ = $1;
  $$->setLocation(@$);
} | if_stmt {
  $$ = $1;
  $$->setLocation(@$);
} | while_stmt {
  $$ = $1;
  $$->setLocation(@$);
} | assignment ';' {
  $$ = $1;
  $$->setLocation(@$);
} | function {
  $$ = $1;
  $$->setLocation(@$);
} | class {
  $$ = $1;
  $$->setLocation(@$);
} | block {
  $$ = $1;
  $$->setLocation(@$);
} | ';' {
  $$ = new EmptyStmtNode();
  $$->setLocation(@$);
};

return_stmt : RETURN ';' {
  $$= new ReturnNode();
  $$->setLocation(@$);

} | RETURN expr ';' {
  $$ = new ReturnNode($2);
  $$->setLocation(@$);
}

block : '{' stmt_list '}'{
  $$ = new BlockNode();
  $$->setStmtList($2);
};

expr : INT_VAL {
  $$ = new Int64ValNode($1);
  $$->setLocation(@$);
} | TRUE {
  $$ = new BoolValNode(true);
  $$->setLocation(@$);
} | FALSE {
  $$ = new BoolValNode(false);
  $$->setLocation(@$);
} | STR_VAL {
  $$ = new StringValNode(*($1));
  $$->setLocation(@$);
} | CHAR_VAL {
  $$ = new CharValNode($1);
  $$->setLocation(@$);
} | DOUBLE_VAL {
  $$ = new DoubleValNode($1);
  $$->setLocation(@$);
} | expr '+' expr {
  $$ = new BinaryExpNode(BinaryExpNode::OP_ADD, $1, $3);
  $$->setLocation(@$);
} | expr '-' expr {
  $$ = new BinaryExpNode(BinaryExpNode::OP_SUB, $1, $3);
  $$->setLocation(@$);
} | expr '*' expr {
  $$ = new BinaryExpNode(BinaryExpNode::OP_MUL, $1, $3);
  $$->setLocation(@$);
} | expr '/' expr {
  $$ = new BinaryExpNode(BinaryExpNode::OP_DIV, $1, $3);
  $$->setLocation(@$);
} | expr '<' expr {
  $$ = new BinaryExpNode(BinaryExpNode::OP_LT, $1, $3);
  $$->setLocation(@$);
} | expr AND  expr {
  $$ = new BinaryExpNode(BinaryExpNode::OP_AND, $1, $3);
  $$->setLocation(@$);
} | expr EQ  expr {
  $$ = new BinaryExpNode(BinaryExpNode::OP_EQ, $1, $3);
  $$->setLocation(@$);
} | '(' expr ')' {
  $$ = $2;
  $$->setLocation(@$);
} | NEW name {
  $$ = new NewNode($2);
  $$->setLocation(@$);
} | field_access {
  $$ = $1;
  $$->setLocation(@$);
} | call {
  $$ = $1;
  $$->setLocation(@$);
};

name : simple_name {
  $$ = $1;
  $$->setLocation(@$);
} | qualified_name {
  $$ = $1;
  $$->setLocation(@$);
};

qualified_name : qualified_name '$' simple_name {
  $$ = new QualifiedNameNode($1, $3);
  $$->setLocation(@$);
} | simple_name '$' simple_name {
  $$ = new QualifiedNameNode($1, $3);
  $$->setLocation(@$);
}

simple_name : ID {
  $$ = new SimpleNameNode(*$1);
  $$->setLocation(@$);
};

field_access : expr '.' simple_name {
  $$ = new FieldAccessNode();
  $$->setLocation(@$);
  $$->setExpression($1);
  $$->setName($3);
};

var_decl : var_decl ',' var_decl_fragment {
  $$ = $1;
  $$->setLocation(@$);
  $$->addVarDeclFragment($3);
} | type var_decl_fragment {
  $$ = new VarDeclNode();
  $$->setLocation(@$);
  $$->setDataType($1);
  $$->addVarDeclFragment($2);
};

var_decl_fragment : ID '=' expr {
  $$ = new VarDeclFragmentNode(*$1, $3);
  $$->setLocation(@$);
} | ID {
  $$ = new VarDeclFragmentNode(*$1, nullptr);
  $$->setLocation(@$);
};

assignment : expr '=' expr {
  $$ = new AssignNode($1, $3);
  $$->setLocation(@$);
}

type : INT32_TYPE {
  $$ = new Int32TypeNode();
  $$->setLocation(@$);
} | INT64_TYPE {
  $$ = new Int64TypeNode();
  $$->setLocation(@$);
} | BOOL_TYPE {
  $$ = new BoolTypeNode();
  $$->setLocation(@$);
} | CHAR_TYPE {
  $$ = new CharTypeNode();
  $$->setLocation(@$);
} | STR_TYPE {
  $$ = new StringTypeNode();
  $$->setLocation(@$);
} | DOUBLE_TYPE {
  $$ = new DoubleTypeNode();
  $$->setLocation(@$);
} | name {
  $$ = new UserDefTypeNode();
  $$->setName($1);
  $$->setLocation(@$);
};

if_stmt : IF '(' expr ')' stmt ELSE stmt {
  $$ = new IfNode($3, $5, $7);
  $$->setLocation(@$);
} | IF '(' expr ')'  stmt  %prec IFX {
  $$ = new IfNode($3, $5, nullptr);
  $$->setLocation(@$);
};

while_stmt : WHILE '(' expr ')' stmt {
  $$ = new WhileNode($3, $5);
  $$->setLocation(@$);
};

function : DEF ID '(' func_param_list ')' ret_type block {
  $$ = $4;
  $$->setLocation(@$);
  $$->setName(*($2));
  $$->setReturnType($6);
  $$->setBody($7);
} | DEF ID '(' ')' ret_type block {
  $$ = new FuncNode();
  $$->setLocation(@$);
  $$->setBody($6);
  $$->setName(*$2);
  $$->setReturnType($5);
};

ret_type : type {
  $$ = $1;
  $$->setLocation(@$);
} | {
  $$ = new VoidTypeNode();
  $$->setLocation(@$);
};

func_param_list : func_param_list ',' type ID {
  $$ = $1;
  $$->setLocation(@$);
  VarDeclNode* var_decl_node = new VarDeclNode();
  VarDeclFragmentNode* var_decl_fragment_node = new
      VarDeclFragmentNode(*($4), nullptr);
  var_decl_node->setDataType($3);
  var_decl_node->addVarDeclFragment(var_decl_fragment_node);
  $$->addParameter(var_decl_node);
} | type ID {
  $$ = new FuncNode();
  $$->setLocation(@$);
  VarDeclNode* var_decl_node = new VarDeclNode();
  VarDeclFragmentNode* var_decl_fragment_node = new
      VarDeclFragmentNode(*($2), nullptr);
  var_decl_node->setDataType($1);
  var_decl_node->addVarDeclFragment(var_decl_fragment_node);
  $$->addParameter(var_decl_node);
};

call : expr '.' simple_name '(' param_list ')' {
  $$ = new CallNode();
  $$->setLocation(@$);
  $$->setCaller($1);
  $$->setName($3);
  $$->setParamList($5);
} |  simple_name '(' param_list ')' {
  $$ = new CallNode();
  $$->setLocation(@$);
  $$->setName($1);
  $$->setParamList($3);
};

param_list : param_list ',' expr {
  $$ = $1;
  $$->setLocation(@$);
  $$->addParameter($3);
} | {
  $$ = new ParamListNode();
  $$->setLocation(@$);
};

class : CLASS ID '{' class_body  '}' {
  $$ = $4;
  $$->setName(*($2));
  $$->setLocation(@$);
} | CLASS ID ':' name '{' class_body '}' {
  $$ = $6;
  $$->setLocation(@$);
  $$->setSuperClass($4);
  $$->setName(*($2));
};

class_body : class_body class_body_decl {
  $$ = $1;
  $$->setLocation(@$);
  $$->addDecl($2);
} | {
  $$ = new ClassNode();
  $$->setLocation(@$);
}

class_body_decl : var_decl ';' {
  $$ = $1;
} | function {
  $$ = $1;
} | class {
  $$ = $1;
} | constructor {
  $$ = $1;
} | destructor {
  $$ = $1;
};

constructor : THIS '(' func_param_list ')' block {
  $$ = new ConstructorNode();
  $$->setLocation(@$);
  $$->setParamList($3);
  $$->setBody($5);
};

destructor : '~' THIS '(' ')'  block {
  $$ = new DestructorNode();
  $$->setLocation(@$);
  $$->setBody($5);
};

%%

void flang::FlangParser::error(const flang::FlangParser::location_type& loc,
                               const std::string& msg) {
  Error err(loc);
  err.setMessage(msg);
  log4cxx::LoggerPtr logger(
      log4cxx::Logger::getLogger("flang.FlangParser"));
  LOG4CXX_ERROR(logger, err.getMessage());
}
