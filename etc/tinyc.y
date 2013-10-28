%{

#include <cstdio>
#include <iostream>

#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>

#include "tinyc_lex.h"
#include "data_type.h"
#include "exp_node.h"
#include "print_node.h"
#include "ctrl_node.h"
#include "func_node.h"
#include "class_node.h"
#include "declare_node.h"
#include "scope.h"
#include "type_check_visitor.h"

using namespace std;
using namespace log4cxx;

extern string& getStrVal( int idx );

void yyerror(SyntaxNode* &program, const char*);

LoggerPtr g_logger(Logger::getLogger("yacc"));

%}

%union {
	int   intVal;
	char  charVal;
	bool  boolVal;
    int   strIdx;
    int   lineNum;

	SyntaxNode*      syntaxNode;
	DeclareNode*     declareNode;
	StmtListNode*    stmtListNode;
	ExpNode*         expNode;
    DataTypeNode*    dataTypeNode;
    IfNode*          ifNode;
    WhileNode*       whileNode;
    FuncNode*        funcNode;
    CallNode*        callNode;
    ClassNode*       classNode;
    AssignNode*      assignNode;
}

%token <intVal> NUMBER
%token <charVal> CHARVAL
%token <boolVal> BOOLVAL
%token <strIdx> STR ID

%token <lineNum> WHILE IF PRINT BREAK DEF CLASS RETURN THIS NEW
%token <lineNum> BOOL CHAR INT TRUE FALSE STRING

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
%type <syntaxNode> program simple_program stmt simple_stmt complex_stmt
%type <expNode> expr
%type <declareNode> declare var_list
%type <stmtListNode> stmt_list simple_stmt_list
%type <dataTypeNode> type ret_type
%type <ifNode> if_stmt
%type <whileNode> while_stmt
%type <funcNode>  function func_param_list
%type <callNode>  call_param_list call param_list
%type <classNode> class  class_stmt_list
%type <assignNode> declare_var 

%start program

%parse-param {SyntaxNode* &program}

%%

program : stmt_list { $$ = $1;
                      program = $1;
					}

        |           { $$ = NULL; 
                      program = NULL;
                    }
        ;

stmt_list : stmt { $$ = new StmtListNode();
                   $$->setLineNum( yylineno );
                   $$->addStmt( $1 ); 
                   g_collector.insert( $$ );
		         }
          | stmt_list stmt  { 
			  					$1->addStmt( $2 );
								$$ = $1;
							}
          ;

stmt : simple_stmt  { $$ = $1; } 
     | complex_stmt { $$ = $1; }
     ;

simple_program : simple_stmt_list { $$ = $1;   }
               |                  { $$ = NULL; }
               ;

simple_stmt_list : simple_stmt { $$ = new StmtListNode();
                                 $$->setLineNum( yylineno );
                                 $$->addStmt( $1 );
                                 g_collector.insert( $$ );
                               }
                 | simple_stmt_list simple_stmt { $1->addStmt( $2 ); }
                 ;

complex_stmt : function { $$ = $1; }
             | class    { $$ = $1; }
             ;

simple_stmt : ';'             { $$ = NULL; }
	        | expr ';'	       { $$ = $1; }
	        | PRINT expr ';'  { $$ = new PrintNode( $2 );  $$->setLineNum( $1 );  g_collector.insert( $$ );}
            | RETURN expr ';' { $$ = new ReturnNode( $2 );  $$->setLineNum( $1 ); g_collector.insert( $$ );}
            | RETURN ';'      { $$ = new ReturnNode();  $$->setLineNum( $1 ); g_collector.insert( $$ ); }
            | BREAK  ';'      { $$ = new BreakNode();  $$->setLineNum( $1 ); g_collector.insert( $$ ); }
	        | declare ';'     { $$ = $1; }
            | if_stmt         { $$ = $1; }
            | while_stmt      { $$ = $1; } 
	        ;


expr : NUMBER       { $$ = new IntNode( $1 );
                      $$->setLineNum( yylineno );
                      g_collector.insert( $$ ); }
	 | TRUE         { $$ = new BoolNode(true); 
                      $$->setLineNum( yylineno );
                      g_collector.insert( $$ );   }
	 | FALSE        { $$ = new BoolNode(false); 
                      $$->setLineNum( yylineno );
                      g_collector.insert( $$ ); }
	 | STR          { $$ = new StringNode( getStrVal($1) ); 
                      $$->setLineNum( yylineno ); 
                      g_collector.insert( $$ ); }

	 | CHARVAL      { $$ = new CharNode($1); 
                      $$->setLineNum( yylineno ); 
                      g_collector.insert( $$ ); } 
	 | ID           { $$ = new VarRefNode( getStrVal($1) ); 
                      $$->setLineNum( yylineno ); 
                      g_collector.insert( $$ );  
                    }

	 | ID '=' expr  { VarRefNode* var = new VarRefNode( getStrVal($1) ); 
                      var->setLineNum(yylineno); 
                      g_collector.insert( var );

                      $$ = new AssignNode( var, $3 ); 
                      $$->setLineNum( yylineno );
                      g_collector.insert( $$ );
                    }
	 | expr '+' expr  { $$ = new AddNode( $1, $3 ); 
                        $$->setLineNum( yylineno );
                        g_collector.insert( $$ );  }
	 | expr '-' expr  { $$ = new SubNode( $1, $3 ); 
                        $$->setLineNum( yylineno );
                        g_collector.insert( $$ );  }
	 | expr '*' expr  { $$ = new MulNode( $1, $3 ); 
                        $$->setLineNum( yylineno );
                        g_collector.insert( $$ );  }
	 | expr '/' expr  { $$ = new DivNode( $1, $3 ); 
                        $$->setLineNum( yylineno );
                        g_collector.insert( $$ );  }
	 | expr '<' expr  { $$ = new LtNode( $1, $3 );  
                        $$->setLineNum( yylineno );
                        g_collector.insert( $$ );  }
	 | expr AND  expr { $$ = new AndNode( $1, $3 ); 
                        $$->setLineNum( yylineno );
                        g_collector.insert( $$ );  }
	 | expr EQ  expr  { $$ = new EqNode( $1, $3 );  
                        $$->setLineNum( yylineno );
                        g_collector.insert( $$ );  }
	 | '(' expr ')'   { $$ = $2; }
     | call           { $$ = $1; }
     | NEW ID         { $$ = new NewNode( getStrVal($2) ); 
                        g_collector.insert( $$ );}
	 ;

declare : var_list declare_var { $$ = $1;
                                 $2->setVarDataTypeNode( $1->getDataTypeNode() );
                                 $$->addDeclare( $2 );
                                 $$->setLineNum( yylineno );
					           }
        ;

var_list : var_list declare_var ','  { $$ = $1;
                                       $2->setVarDataTypeNode( $1->getDataTypeNode() );
                                       $$->addDeclare( $2 );
                                       $$->setLineNum( yylineno );
							         }
         | type 		   { $$ = new DeclareNode();
		                     $$->setDataTypeNode($1);
							 $$->setLineNum( yylineno );
                             g_collector.insert( $$ );
						   }
		 ;
declare_var : ID           { VarNode* var = new VarDeclareNode( getStrVal($1) );
                             var->setLineNum( yylineno );
                             g_collector.insert( var );
                             $$ = new AssignNode( var );
                             $$->setLineNum( yylineno );
                             g_collector.insert( $$ );
                           }
            | ID '=' expr  { VarNode* var = new VarDeclareNode( getStrVal($1));
                             var->setLineNum( yylineno );
                             g_collector.insert( var );

                             $$ = new AssignNode( var, $3 );  
                             $$->setLineNum( yylineno );
                             g_collector.insert( $$ );
                           }
            ;


type : INT 		{ $$ = INT_TYPE_NODE;     }
     | BOOL 	{ $$ = BOOL_TYPE_NODE;    }
	 | CHAR 	{ $$ = CHAR_TYPE_NODE;    } 
	 | STRING 	{ $$ = STRING_TYPE_NODE;  } 
     | ID       { $$ = new ClassTypeNode( getStrVal($1) );
                  $$->setLineNum( yylineno); 
                  g_collector.insert( $$ );
                }
	 ;

if_stmt : IF '(' expr ')' '{'
              simple_program 
          '}' ELSE '{' 
              simple_program 
          '}' 
          {  
              $$ = new IfNode( $3, $6, $10 );
              $$->setLineNum( $1 );
              g_collector.insert( $$ );
          }

        | IF '(' expr ')' '{' simple_program '}' ELSE  stmt     { $$ = new IfNode( $3, $6, $9 ); 
                                                                  $$->setLineNum( $1 );
                                                                  g_collector.insert( $$ );

                                                                }
        | IF '(' expr ')'  stmt ELSE '{' simple_program '}'     { $$ = new IfNode( $3, $5, $8 ); 
                                                                  $$->setLineNum( $1 );
                                                                  g_collector.insert( $$ );

                                                                }
        | IF '(' expr ')'  stmt  ELSE stmt                      { $$ = new IfNode( $3, $5, $7 ); 
                                                                  $$->setLineNum( $1 );
                                                                  g_collector.insert( $$ );
                                                                }
        | IF '(' expr ')' '{' simple_program '}'    %prec IFX          { $$ = new IfNode( $3, $6 );
                                                                  $$->setLineNum( $1 );
                                                                  g_collector.insert( $$ );
                                                                }  
        | IF '(' expr ')'  stmt              %prec IFX          { $$ = new IfNode( $3, $5 ); 
                                                                  $$->setLineNum( $1 );
                                                                  g_collector.insert( $$ );
                                                                }
        ;
while_stmt : WHILE '(' expr ')' '{' simple_program '}' { $$ = new WhileNode( $3, $6 );
                                                         $$->setLineNum( $1 );
                                                         g_collector.insert( $$ );
                                                       } 
           | WHILE '(' expr ')'  stmt           { $$ = new WhileNode( $3, $5 );
                                                  $$->setLineNum( $1 );
                                                  g_collector.insert( $$ );
                                                }
           ;

function : DEF ID '(' func_param_list ')' ret_type '{' simple_program '}'  { $$ = $4; 
                                                                      $$->setName( getStrVal($2)); 
                                                                      $$->setRetType($6);
                                                                      $$->setBody($8);
                                                                      $$->setLineNum( $1 );
                                                                    }
         | DEF ID '(' ')'  ret_type '{'simple_program '}'                 { $$ = new GlobalFuncNode( getStrVal($2), $5, $7 );
                                                                      $$->setLineNum( $1 );
                                                                      g_collector.insert( $$ );
                                                                    }
		 ;

ret_type : type { $$ = $1; }
         |      { $$ = VOID_TYPE_NODE; }
         ;


func_param_list : func_param_list ',' type ID {  $$ = $1; 
                                                 $$->addParam( VarNode( getStrVal( $4 ), $3) ); 
                                              }
                | type ID                     {  $$ = new GlobalFuncNode();
                                                 $$->addParam( VarNode( getStrVal( $2 ), $1 ) );
                                                 g_collector.insert( $$ );
                                              }
		        ;

call : ID '(' call_param_list ')' { $$ = $3; 
                                    $$->setFuncName( getStrVal($1) ); 
                                  }
     | ID '.' ID '(' call_param_list ')'   { $$ = $5;
                                             $$->setLineNum( $<lineNum>2 );
                                             $$->setFuncName( getStrVal($3) );
                                             $$->setMemberFuncHint( true );
                                             $$->setCallerName(getStrVal( $1 ));
                                           }
     | THIS '.' ID '(' call_param_list ')' { $$ = $5;
                                             $$->setLineNum( $<lineNum>2 );
                                             $$->setFuncName( getStrVal($3) );
                                             $$->setMemberFuncHint( true );
                                           }
     ; 

call_param_list : param_list     { $$ = $1; }
                |                { $$ = new CallNode(); 
                                   g_collector.insert( $$ );
                                 }
                ;

param_list : param_list ',' expr { $$ = $1;
                                   $$->addParam( $3 ); 
                                   g_collector.insert( $$ );
                                 }
           | expr                { $$ = new CallNode();
                                   $$->addParam( $1 );
                                   $$->setLineNum( yylineno );
                                   g_collector.insert( $$ );
                                 }
		   ;

class : CLASS ID '{' class_stmt_list  '}'          { $$ = $4;
                                                     $$->setName( getStrVal($2) );
                                                     $$->setLineNum( $1 );
                                                   }
      | CLASS ID ':' ID '{' class_stmt_list '}'    { $$ = $6;
                                                     $$->setParentName( getStrVal( $4 ) );
                                                     $$->setName( getStrVal($2) );
                                                     $$->setLineNum( $1 );
                                                   }
      ;


class_stmt_list : class_stmt_list declare ';' { $$ = $1;
                                                $$->addVarDeclare( $2 );
                                              }
                | class_stmt_list function    { $$ = $1;
                                                
                                                // create a new class function to wrap a global function
                                                ClassFuncNode* classFunc = new ClassFuncNode( $1, $2 );

                                                // add the function to the class
                                                $$->addFuncion( classFunc );

                                                g_collector.insert( classFunc );
                                                g_collector.collect( $2 );
                                              }
                |                             { $$ = new ClassNode();  
                                                g_collector.insert( $$ );
                                              }
                ;

%%

void yyerror(SyntaxNode* &program, const char* msg ){

	printf( "error at line %d : %s\n", yylineno, msg );
}

int main(){

    PropertyConfigurator::configure("log4cxx.properties");
    
    LOG4CXX_INFO( g_logger, "start to parse program and build abstract syntax tree" );
    
    SyntaxTree* program = NULL;
	yyparse( program );

    if( NULL == program ){

        LOG4CXX_INFO( g_logger, "program is null" );
        return 0;
    }

    LOG4CXX_INFO( g_logger, "abstract syntax tree built completed" );

    LOG4CXX_INFO( g_logger, "start to do type check" );

    TypeCheckVisitor typeCheckVisitor;

    program->accept( typeCheckVisitor );
    
    typeCheckVisitor.printError();

    LOG4CXX_INFO( g_logger, "type check completed" );

    program = NULL;

	return 0;
}


