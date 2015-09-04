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
using namespace log4cxx;

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
  VarDeclarationNode* var_decl_node;
  VarDeclarationFragmentNode* var_decl_fragment_node;
  ProgramNode* program_node;
  ExpNode* exp_node;
  DataTypeNode* data_type_node;
  IfNode* if_node;
  WhileNode* while_node;
  FuncNode* func_node;
  CallNode* call_node;
  ClassNode* class_node;
  AssignNode* assign_node;
  NameNode* name_node;
  QualifiedNameNode* qualified_name_node;
  SimpleNameNode* simple_name_node;
  StmtNode* stmt_node;
  BlockNode* block_node;
  ReferenceNode* refer_node;
}

%token <int64_val> INT_VAL
%token <char_val> CHAR_VAL
%token <bool_val> BOOL_VAL
%token <str_val> STR_VAL ID
%token <double_val> DOUBLE_VAL

%token <lineno> WHILE IF PRINT BREAK DEF CLASS RETURN THIS NEW
%token <lineno> BOOL_TYPE CHAR_TYPE STR_TYPE INT32_TYPE INT64_TYPE TRUE FALSE
%token <lineno> DOUBLE_TYPE

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
%type <program_node> program
%type <block_node> block
%type <stmt_node> stmt simple_stmt complex_stmt
%type <exp_node> expression
%type <var_decl_node> var_declaration
%type <var_decl_fragment_node> var_declaration_fragment
%type <data_type_node> type ret_type
%type <if_node> if_stmt
%type <while_node> while_stmt
%type <func_node>  function func_param_list
%type <call_node>  call_param_list call param_list
%type <class_node> class  class_stmt_list
%type <assign_node> assignment
%type <simple_name_node> simple_name
%type <qualified_name_node> qualified_name
%type <name_node> name
%type <refer_node> reference

%start program

%%

program : program stmt {
  $$ = $1;
  $$->setLocation(@$);
  $$->addStatement($2);
} | {
  syntax_tree->setRoot(new ProgramNode());
  $$ = syntax_tree->getRoot();
  $$->setLocation(@$);
};

stmt : simple_stmt {
  $$ = $1;
  $$->setLocation(@$);
} | complex_stmt {
  $$ = $1;
  $$->setLocation(@$);
};

block : simple_stmt {
  $$ = new BlockNode();
  $$->setLocation(@$);
  $$->addStatement($1);
} | block simple_stmt {
  $$ = $1;
  $$->addStatement($2);
};

complex_stmt : function {
  $$ = $1;
  $$->setLocation(@$);
} | class {
  $$ = $1;
  $$->setLocation(@$);
};

simple_stmt : expression ';' {
  $$ = $1;
  $$->setLocation(@$);
} | PRINT expression ';' {
  $$ = new PrintNode( $2 );
  $$->setLocation(@$);
} | RETURN expression ';' {
  $$ = new ReturnNode( $2 );
  $$->setLocation(@$);
} | RETURN ';' {
  $$ = new ReturnNode();
  $$->setLocation(@$);
} | BREAK ';' {
  $$ = new BreakNode();
  $$->setLocation(@$);
} | var_declaration ';' {
  $$ = $1;
  $$->setLocation(@$);
} | if_stmt {
  $$ = $1;
  $$->setLocation(@$);
} | while_stmt {
  $$ = $1;
  $$->setLocation(@$);
} | assignment {
  $$ = $1;
  $$->setLocation(@$);
};

expression : INT_VAL {
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
} | expression '+' expression {
  $$ = new BinaryExpNode(BinaryExpNode::OP_ADD, $1, $3);
  $$->setLocation(@$);
} | expression '-' expression {
  $$ = new BinaryExpNode(BinaryExpNode::OP_SUB, $1, $3);
  $$->setLocation(@$);
} | expression '*' expression {
  $$ = new BinaryExpNode(BinaryExpNode::OP_MUL, $1, $3);
  $$->setLocation(@$);
} | expression '/' expression {
  $$ = new BinaryExpNode(BinaryExpNode::OP_DIV, $1, $3);
  $$->setLocation(@$);
} | expression '<' expression {
  $$ = new BinaryExpNode(BinaryExpNode::OP_LT, $1, $3);
  $$->setLocation(@$);
} | expression AND  expression {
  $$ = new BinaryExpNode(BinaryExpNode::OP_AND, $1, $3);
  $$->setLocation(@$);
} | expression EQ  expression {
  $$ = new BinaryExpNode(BinaryExpNode::OP_EQ,$1, $3);
  $$->setLocation(@$);
} | '(' expression ')' {
  $$ = $2;
  $$->setLocation(@$);
} | NEW name {
  $$ = new NewNode($2);
  $$->setLocation(@$);
} | reference {
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

reference : reference '.' name {
  $$ = $1;
  $$->addChildNode($3);
  $$->setLocation(@$);
} | reference '.' call {
  $$ = $1;
  $$->addChildNode($3);
  $$->setLocation(@$);
} | name {
  $$ = new ReferenceNode();
  $$->addChildNode($1);
  $$->setLocation(@$);
} | call {
  $$ = new ReferenceNode();
  $$->addChildNode($1);
  $$->setLocation(@$);
}

var_declaration : var_declaration ',' var_declaration_fragment {
  $$ = $1;
  $$->setLocation(@$);
  $$->addVarDeclFragment($3);
} | type var_declaration_fragment {
  $$ = new VarDeclarationNode();
  $$->setLocation(@$);
  $$->setDataType($1);
  $$->addVarDeclFragment($2);
};

var_declaration_fragment : ID '=' expression {
  $$ = new VarDeclarationFragmentNode(*$1, $3);
  $$->setLocation(@$);
} | ID {
  $$ = new VarDeclarationFragmentNode(*$1, nullptr);
  $$->setLocation(@$);
};

assignment : simple_name '=' expression {
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
};

if_stmt : IF '(' expression ')' '{'
            block
          '}' ELSE '{'
            block
          '}' {
  $$ = new IfNode($3, $6, $10);
  $$->setLocation(@$);
} | IF '(' expression ')' '{' block '}' ELSE  stmt {
  $$ = new IfNode($3, $6, $9);
  $$->setLocation(@$);
} | IF '(' expression ')'  stmt ELSE '{' block '}' {
  $$ = new IfNode($3, $5, $8);
  $$->setLocation(@$);
} | IF '(' expression ')'  stmt  ELSE stmt {
  $$ = new IfNode($3, $5, $7);
  $$->setLocation(@$);
} | IF '(' expression ')' '{' block '}' %prec IFX {
  $$ = new IfNode($3, $6, nullptr);
  $$->setLocation(@$);
} | IF '(' expression ')'  stmt  %prec IFX {
  $$ = new IfNode($3, $5, nullptr);
  $$->setLocation(@$);
};

while_stmt : WHILE '(' expression ')' '{' block '}' {
  $$ = new WhileNode($3, $6);
  $$->setLocation(@$);
} | WHILE '(' expression ')' stmt {
  $$ = new WhileNode($3, $5);
  $$->setLocation(@$);
};

function : DEF ID '(' func_param_list ')' ret_type '{' block '}' {
  $$ = $4;
  $$->setLocation(@$);
  $$->setName(*($2));
  $$->setReturnType($6);
  $$->setBody($8);
} | DEF ID '(' ')' ret_type '{'block '}' {
  $$ = new FuncNode();
  $$->setLocation(@$);
  $$->setBody($7);
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
  VarDeclarationNode* var_decl_node = new VarDeclarationNode();
  VarDeclarationFragmentNode* var_decl_fragment_node = new
      VarDeclarationFragmentNode(*($4), nullptr);
  var_decl_node->setDataType($3);
  var_decl_node->addVarDeclFragment(var_decl_fragment_node);
  $$->addParameter(var_decl_node);
} | type ID {
  $$ = new FuncNode();
  $$->setLocation(@$);
  VarDeclarationNode* var_decl_node = new VarDeclarationNode();
  VarDeclarationFragmentNode* var_decl_fragment_node = new
      VarDeclarationFragmentNode(*($2), nullptr);
  var_decl_node->setDataType($1);
  var_decl_node->addVarDeclFragment(var_decl_fragment_node);
  $$->addParameter(var_decl_node);
};

call : name '(' call_param_list ')' {
  $$ = $3;
  $$->setLocation(@$);
  // TODO(congfang): Change CallNode interface.
  // $$->setName(*($1));
};

call_param_list : param_list {
  $$ = $1;
  $$->setLocation(@$);
} | {
  $$ = new CallNode();
  $$->setLocation(@$);
};

param_list : param_list ',' expression {
  $$ = $1;
  $$->addParameter($3);
  $$->setLocation(@$);
} | expression {
  $$ = new CallNode();
  $$->addParameter($1);
  $$->setLocation(@$);
};

class : CLASS ID '{' class_stmt_list  '}' {
  $$ = $4;
  $$->setName(*($2));
  $$->setLocation(@$);
} | CLASS ID ':' simple_name '{' class_stmt_list '}' {
  $$ = $6;
  $$->setLocation(@$);
  $$->setBaseClass($4);
  $$->setName(*($2));
};

class_stmt_list : class_stmt_list var_declaration ';' {
  $$ = $1;
  $$->addVarDeclaration($2);
  $$->setLocation(@$);
} | class_stmt_list function {
  $$ = $1;
  $$->setLocation(@$);
  // create a new class function to wrap a global function
  // add the function to the class
  $$->addFunction($2);
} | {
  $$ = new ClassNode();
  $$->setLocation(@$);
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
