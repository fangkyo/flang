/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_FLANG_PARSER_H_INCLUDED
# define YY_YY_FLANG_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NUMBER = 258,
    CHARVAL = 259,
    BOOLVAL = 260,
    STR = 261,
    ID = 262,
    WHILE = 263,
    IF = 264,
    PRINT = 265,
    BREAK = 266,
    DEF = 267,
    CLASS = 268,
    RETURN = 269,
    THIS = 270,
    NEW = 271,
    BOOL = 272,
    CHAR = 273,
    INT = 274,
    TRUE = 275,
    FALSE = 276,
    STRING = 277,
    IFX = 278,
    ELSE = 279,
    AND = 280,
    OR = 281,
    EQ = 282,
    NE = 283,
    GE = 284,
    LE = 285,
    UMINUS = 286
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 27 "flang_parser.y" /* yacc.c:1909  */

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

#line 106 "flang_parser.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (SyntaxNode* &program);

#endif /* !YY_YY_FLANG_PARSER_H_INCLUDED  */
