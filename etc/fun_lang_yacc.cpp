/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "etc/fun_lang.y"


#include <cstdio>
#include <iostream>

#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>

#include "fun_lang_lex.h"
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



/* Line 268 of yacc.c  */
#line 102 "etc/fun_lang_yacc.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
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
     NE = 282,
     EQ = 283,
     LE = 284,
     GE = 285,
     UMINUS = 286
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 31 "etc/fun_lang.y"

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



/* Line 293 of yacc.c  */
#line 191 "etc/fun_lang_yacc.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 203 "etc/fun_lang_yacc.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  51
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   379

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  75
/* YYNRULES -- Number of states.  */
#define YYNSTATES  147

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   286

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    38,     2,     2,     2,     2,     2,     2,
      41,    42,    36,    34,    43,    35,    46,    37,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    47,    40,
      31,    25,    30,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    44,     2,    45,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      26,    27,    28,    29,    32,    33,    39
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     8,    11,    13,    15,    17,
      18,    20,    23,    25,    27,    29,    32,    36,    40,    43,
      46,    49,    51,    53,    55,    57,    59,    61,    63,    65,
      69,    73,    77,    81,    85,    89,    93,    97,   101,   103,
     106,   109,   113,   115,   117,   121,   123,   125,   127,   129,
     131,   143,   153,   163,   171,   179,   185,   193,   199,   209,
     218,   220,   221,   226,   229,   234,   241,   248,   250,   251,
     255,   257,   263,   271,   275,   278
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      49,     0,    -1,    50,    -1,    -1,    51,    -1,    50,    51,
      -1,    55,    -1,    54,    -1,    53,    -1,    -1,    55,    -1,
      53,    55,    -1,    63,    -1,    69,    -1,    40,    -1,    56,
      40,    -1,    10,    56,    40,    -1,    14,    56,    40,    -1,
      14,    40,    -1,    11,    40,    -1,    57,    40,    -1,    61,
      -1,    62,    -1,     3,    -1,    20,    -1,    21,    -1,     6,
      -1,     4,    -1,     7,    -1,     7,    25,    56,    -1,    56,
      34,    56,    -1,    56,    35,    56,    -1,    56,    36,    56,
      -1,    56,    37,    56,    -1,    56,    31,    56,    -1,    56,
      26,    56,    -1,    56,    29,    56,    -1,    41,    56,    42,
      -1,    66,    -1,    16,     7,    -1,    58,    59,    -1,    58,
      59,    43,    -1,    60,    -1,     7,    -1,     7,    25,    56,
      -1,    19,    -1,    17,    -1,    18,    -1,    22,    -1,     7,
      -1,     9,    41,    56,    42,    44,    52,    45,    24,    44,
      52,    45,    -1,     9,    41,    56,    42,    44,    52,    45,
      24,    51,    -1,     9,    41,    56,    42,    51,    24,    44,
      52,    45,    -1,     9,    41,    56,    42,    51,    24,    51,
      -1,     9,    41,    56,    42,    44,    52,    45,    -1,     9,
      41,    56,    42,    51,    -1,     8,    41,    56,    42,    44,
      52,    45,    -1,     8,    41,    56,    42,    51,    -1,    12,
       7,    41,    65,    42,    64,    44,    52,    45,    -1,    12,
       7,    41,    42,    64,    44,    52,    45,    -1,    60,    -1,
      -1,    65,    43,    60,     7,    -1,    60,     7,    -1,     7,
      41,    67,    42,    -1,     7,    46,     7,    41,    67,    42,
      -1,    15,    46,     7,    41,    67,    42,    -1,    68,    -1,
      -1,    68,    43,    56,    -1,    56,    -1,    13,     7,    44,
      70,    45,    -1,    13,     7,    47,     7,    44,    70,    45,
      -1,    70,    57,    40,    -1,    70,    63,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    93,    93,    96,   101,   106,   111,   113,   117,   119,
     123,   128,   132,   134,   138,   140,   142,   146,   150,   154,
     158,   160,   162,   166,   169,   172,   175,   179,   182,   187,
     195,   198,   201,   204,   207,   210,   213,   216,   217,   218,
     222,   229,   234,   240,   247,   258,   259,   260,   261,   262,
     268,   279,   284,   289,   293,   297,   302,   306,   312,   318,
     324,   325,   329,   332,   338,   341,   347,   354,   355,   360,
     364,   371,   375,   383,   386,   397
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "CHARVAL", "BOOLVAL", "STR",
  "ID", "WHILE", "IF", "PRINT", "BREAK", "DEF", "CLASS", "RETURN", "THIS",
  "NEW", "BOOL", "CHAR", "INT", "TRUE", "FALSE", "STRING", "IFX", "ELSE",
  "'='", "AND", "OR", "NE", "EQ", "'>'", "'<'", "LE", "GE", "'+'", "'-'",
  "'*'", "'/'", "'!'", "UMINUS", "';'", "'('", "')'", "','", "'{'", "'}'",
  "'.'", "':'", "$accept", "program", "stmt_list", "stmt",
  "simple_program", "simple_stmt_list", "complex_stmt", "simple_stmt",
  "expr", "declare", "var_list", "declare_var", "type", "if_stmt",
  "while_stmt", "function", "ret_type", "func_param_list", "call",
  "call_param_list", "param_list", "class", "class_stmt_list", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,    61,   280,   281,   282,   283,
      62,    60,   284,   285,    43,    45,    42,    47,    33,   286,
      59,    40,    41,    44,   123,   125,    46,    58
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    48,    49,    49,    50,    50,    51,    51,    52,    52,
      53,    53,    54,    54,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      57,    58,    58,    59,    59,    60,    60,    60,    60,    60,
      61,    61,    61,    61,    61,    61,    62,    62,    63,    63,
      64,    64,    65,    65,    66,    66,    66,    67,    67,    68,
      68,    69,    69,    70,    70,    70
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     1,     1,     1,     0,
       1,     2,     1,     1,     1,     2,     3,     3,     2,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     2,
       2,     3,     1,     1,     3,     1,     1,     1,     1,     1,
      11,     9,     9,     7,     7,     5,     7,     5,     9,     8,
       1,     0,     4,     2,     4,     6,     6,     1,     0,     3,
       1,     5,     7,     3,     2,     0
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,    23,    27,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    46,    47,    45,    24,    25,    48,
      14,     0,     0,     2,     4,     7,     6,     0,     0,     0,
      42,    21,    22,    12,    38,    13,     0,    68,     0,     0,
       0,    28,     0,    19,     0,     0,    18,     0,     0,    39,
       0,     1,     5,     0,     0,     0,     0,     0,     0,     0,
      15,    20,    43,    40,    29,    70,     0,    67,     0,     0,
       0,    16,     0,    75,     0,    17,     0,    37,    35,    36,
      34,    30,    31,    32,    33,     0,    41,    64,     0,    68,
       0,     0,    49,    61,     0,     0,     0,     0,    68,    44,
      69,     0,     9,    57,     9,    55,    60,     0,    63,    61,
       0,    71,     0,    74,    75,     0,    65,     0,     8,    10,
       0,     0,     9,     0,     0,    73,     0,    66,    56,    11,
      54,     9,    53,     0,     9,    62,    72,     0,     0,    59,
       0,     9,    51,    52,    58,     0,    50
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    22,    23,    24,   117,   118,    25,    26,    27,    28,
      29,    63,    30,    31,    32,    33,   107,    95,    34,    66,
      67,    35,    96
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -97
static const yytype_int16 yypact[] =
{
     265,   -97,   -97,   -97,    -5,   -30,   -27,   294,   -24,    14,
      16,   287,   -21,    37,   -97,   -97,   -97,   -97,   -97,   -97,
     -97,   294,    46,   265,   -97,   -97,   -97,   146,    17,    47,
     -97,   -97,   -97,   -97,   -97,   -97,   294,   294,    77,   294,
     294,   -22,   318,   -97,    44,   -35,   -97,   330,    79,   -97,
     184,   -97,   -97,   294,   294,   294,   294,   294,   294,   294,
     -97,   -97,    63,    48,   342,   342,    51,    64,    67,   223,
     303,   -97,   304,   -97,    82,   -97,    69,   -97,   105,   282,
      66,     6,     6,   -97,   -97,   294,   -97,   -97,   294,   294,
     109,   148,   -97,    10,   104,    38,    87,    91,   294,   342,
     342,    95,    55,   -97,    55,   122,   -97,   103,   -97,    10,
      10,   -97,   133,   -97,   -97,   132,   -97,   131,    55,   -97,
     134,   187,    55,   140,   171,   -97,   126,   -97,   -97,   -97,
     161,    55,   -97,   142,    55,   -97,   -97,   226,   166,   -97,
     167,    55,   -97,   -97,   -97,   169,   -97
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -97,   -97,   -97,   -23,   -44,   -97,   -97,   -96,    -6,   -89,
     -97,   -97,   -54,   -97,   -97,   -86,   107,   -97,   -97,   -85,
     -97,   -97,   108
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -50
static const yytype_int16 yytable[] =
{
      52,    42,   -49,    36,   101,    47,   119,   112,   119,    73,
     113,    39,    74,   115,    40,    50,    43,    92,    94,    37,
      36,    44,   129,    45,    38,    48,   119,    14,    15,    16,
      64,    65,    19,    69,    70,   119,    37,   112,   119,   106,
     113,    38,    58,    59,    49,   119,    51,    78,    79,    80,
      81,    82,    83,    84,    62,   106,   124,    61,     1,     2,
     120,     3,     4,     5,     6,     7,     8,   103,   105,    11,
      12,    13,    14,    15,    16,    17,    18,    19,   133,    99,
     109,   110,   100,    65,    68,    72,    76,   138,    85,    97,
     140,    86,    65,    87,    92,    20,    21,   145,   132,     9,
      56,    57,    58,    59,    14,    15,    16,    88,    89,    19,
      98,   108,     1,     2,   142,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,   111,    92,    54,   114,    55,   116,     9,    56,
      57,    58,    59,    14,    15,    16,   121,   122,    19,    20,
      21,     1,     2,   102,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,   136,    53,   125,   127,    54,   128,    55,   135,   130,
      56,    57,    58,    59,   134,   137,    60,   139,    20,    21,
       1,     2,   104,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      53,   143,   144,    54,   146,    55,   123,     0,    56,    57,
      58,    59,   126,     0,     0,     0,    77,    20,    21,     1,
       2,   131,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    53,
       0,     0,    54,     0,    55,     0,     0,    56,    57,    58,
      59,     0,     0,     0,     0,    90,    20,    21,     1,     2,
     141,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,     0,
       1,     2,     0,     3,    41,     0,     0,     1,     2,     0,
       3,    41,    12,    13,     0,    20,    21,    17,    18,    12,
      13,    92,     0,    55,    17,    18,    56,    57,    58,    59,
       0,    14,    15,    16,     0,     0,    19,    46,    21,    53,
       0,     0,    54,     0,    55,    21,     0,    56,    57,    58,
      59,     0,     0,     0,    53,    91,    93,    54,     0,    55,
       0,     0,    56,    57,    58,    59,    53,     0,    71,    54,
       0,    55,     0,     0,    56,    57,    58,    59,    53,     0,
      75,    54,     0,    55,     0,     0,    56,    57,    58,    59
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-97))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      23,     7,     7,    25,    89,    11,   102,    96,   104,    44,
      96,    41,    47,    98,    41,    21,    40,     7,    72,    41,
      25,     7,   118,     7,    46,    46,   122,    17,    18,    19,
      36,    37,    22,    39,    40,   131,    41,   126,   134,    93,
     126,    46,    36,    37,     7,   141,     0,    53,    54,    55,
      56,    57,    58,    59,     7,   109,   110,    40,     3,     4,
     104,     6,     7,     8,     9,    10,    11,    90,    91,    14,
      15,    16,    17,    18,    19,    20,    21,    22,   122,    85,
      42,    43,    88,    89,     7,    41,     7,   131,    25,     7,
     134,    43,    98,    42,     7,    40,    41,   141,   121,    12,
      34,    35,    36,    37,    17,    18,    19,    43,    41,    22,
      41,     7,     3,     4,   137,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    45,     7,    29,    44,    31,    42,    12,    34,
      35,    36,    37,    17,    18,    19,    24,    44,    22,    40,
      41,     3,     4,    44,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    45,    26,    40,    42,    29,    45,    31,     7,    45,
      34,    35,    36,    37,    44,    24,    40,    45,    40,    41,
       3,     4,    44,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      26,    45,    45,    29,    45,    31,   109,    -1,    34,    35,
      36,    37,   114,    -1,    -1,    -1,    42,    40,    41,     3,
       4,    44,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    26,
      -1,    -1,    29,    -1,    31,    -1,    -1,    34,    35,    36,
      37,    -1,    -1,    -1,    -1,    42,    40,    41,     3,     4,
      44,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    -1,
       3,     4,    -1,     6,     7,    -1,    -1,     3,     4,    -1,
       6,     7,    15,    16,    -1,    40,    41,    20,    21,    15,
      16,     7,    -1,    31,    20,    21,    34,    35,    36,    37,
      -1,    17,    18,    19,    -1,    -1,    22,    40,    41,    26,
      -1,    -1,    29,    -1,    31,    41,    -1,    34,    35,    36,
      37,    -1,    -1,    -1,    26,    42,    42,    29,    -1,    31,
      -1,    -1,    34,    35,    36,    37,    26,    -1,    40,    29,
      -1,    31,    -1,    -1,    34,    35,    36,    37,    26,    -1,
      40,    29,    -1,    31,    -1,    -1,    34,    35,    36,    37
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      40,    41,    49,    50,    51,    54,    55,    56,    57,    58,
      60,    61,    62,    63,    66,    69,    25,    41,    46,    41,
      41,     7,    56,    40,     7,     7,    40,    56,    46,     7,
      56,     0,    51,    26,    29,    31,    34,    35,    36,    37,
      40,    40,     7,    59,    56,    56,    67,    68,     7,    56,
      56,    40,    41,    44,    47,    40,     7,    42,    56,    56,
      56,    56,    56,    56,    56,    25,    43,    42,    43,    41,
      42,    42,     7,    42,    60,    65,    70,     7,    41,    56,
      56,    67,    44,    51,    44,    51,    60,    64,     7,    42,
      43,    45,    57,    63,    44,    67,    42,    52,    53,    55,
      52,    24,    44,    64,    60,    40,    70,    42,    45,    55,
      45,    44,    51,    52,    44,     7,    45,    24,    52,    45,
      52,    44,    51,    45,    45,    52,    45
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (program, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, program); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, SyntaxNode* &program)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, program)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    SyntaxNode* &program;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (program);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, SyntaxNode* &program)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, program)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    SyntaxNode* &program;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, program);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, SyntaxNode* &program)
#else
static void
yy_reduce_print (yyvsp, yyrule, program)
    YYSTYPE *yyvsp;
    int yyrule;
    SyntaxNode* &program;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       , program);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, program); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, SyntaxNode* &program)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, program)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    SyntaxNode* &program;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (program);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (SyntaxNode* &program);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (SyntaxNode* &program)
#else
int
yyparse (program)
    SyntaxNode* &program;
#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 93 "etc/fun_lang.y"
    { 
  (yyval.syntaxNode) = (yyvsp[(1) - (1)].stmtListNode);
  program = (yyvsp[(1) - (1)].stmtListNode);
}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 96 "etc/fun_lang.y"
    { 
  (yyval.syntaxNode) = NULL; 
  program = NULL;
}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 101 "etc/fun_lang.y"
    {
  (yyval.stmtListNode) = new StmtListNode();
  (yyval.stmtListNode)->setLineNum( yylineno );
  (yyval.stmtListNode)->addStmt( (yyvsp[(1) - (1)].syntaxNode) ); 
  g_collector.insert( (yyval.stmtListNode) );
}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 106 "etc/fun_lang.y"
    { 
	(yyvsp[(1) - (2)].stmtListNode)->addStmt( (yyvsp[(2) - (2)].syntaxNode) );
	(yyval.stmtListNode) = (yyvsp[(1) - (2)].stmtListNode);
}
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 111 "etc/fun_lang.y"
    {
  (yyval.syntaxNode) = (yyvsp[(1) - (1)].syntaxNode);
}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 113 "etc/fun_lang.y"
    {
  (yyval.syntaxNode) = (yyvsp[(1) - (1)].syntaxNode);
}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 117 "etc/fun_lang.y"
    {
  (yyval.syntaxNode) = (yyvsp[(1) - (1)].stmtListNode);
}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 119 "etc/fun_lang.y"
    {
  (yyval.syntaxNode) = NULL;
}
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 123 "etc/fun_lang.y"
    {
  (yyval.stmtListNode) = new StmtListNode();
  (yyval.stmtListNode)->setLineNum( yylineno );
  (yyval.stmtListNode)->addStmt( (yyvsp[(1) - (1)].syntaxNode) );
  g_collector.insert( (yyval.stmtListNode) );
}
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 128 "etc/fun_lang.y"
    {
  (yyvsp[(1) - (2)].stmtListNode)->addStmt( (yyvsp[(2) - (2)].syntaxNode) );
}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 132 "etc/fun_lang.y"
    {
  (yyval.syntaxNode) = (yyvsp[(1) - (1)].funcNode);
}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 134 "etc/fun_lang.y"
    {
  (yyval.syntaxNode) = (yyvsp[(1) - (1)].classNode);
}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 138 "etc/fun_lang.y"
    {
  (yyval.syntaxNode) = NULL;
}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 140 "etc/fun_lang.y"
    {
  (yyval.syntaxNode) = (yyvsp[(1) - (2)].expNode);
}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 142 "etc/fun_lang.y"
    {
  (yyval.syntaxNode) = new PrintNode( (yyvsp[(2) - (3)].expNode) );
  (yyval.syntaxNode)->setLineNum( (yyvsp[(1) - (3)].lineNum) );
  g_collector.insert( (yyval.syntaxNode) );
}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 146 "etc/fun_lang.y"
    {
  (yyval.syntaxNode) = new ReturnNode( (yyvsp[(2) - (3)].expNode) );
  (yyval.syntaxNode)->setLineNum( (yyvsp[(1) - (3)].lineNum) );
  g_collector.insert( (yyval.syntaxNode) );
}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 150 "etc/fun_lang.y"
    { 
  (yyval.syntaxNode) = new ReturnNode();
  (yyval.syntaxNode)->setLineNum( (yyvsp[(1) - (2)].lineNum) );
  g_collector.insert( (yyval.syntaxNode) );
}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 154 "etc/fun_lang.y"
    {
  (yyval.syntaxNode) = new BreakNode();
  (yyval.syntaxNode)->setLineNum( (yyvsp[(1) - (2)].lineNum) );
  g_collector.insert( (yyval.syntaxNode) );
}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 158 "etc/fun_lang.y"
    { 
  (yyval.syntaxNode) = (yyvsp[(1) - (2)].declareNode);
}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 160 "etc/fun_lang.y"
    { 
  (yyval.syntaxNode) = (yyvsp[(1) - (1)].ifNode);
}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 162 "etc/fun_lang.y"
    { 
  (yyval.syntaxNode) = (yyvsp[(1) - (1)].whileNode);
}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 166 "etc/fun_lang.y"
    { (yyval.expNode) = new IntNode( (yyvsp[(1) - (1)].intVal) );
                      (yyval.expNode)->setLineNum( yylineno );
                      g_collector.insert( (yyval.expNode) ); }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 169 "etc/fun_lang.y"
    { (yyval.expNode) = new BoolNode(true); 
                      (yyval.expNode)->setLineNum( yylineno );
                      g_collector.insert( (yyval.expNode) );   }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 172 "etc/fun_lang.y"
    { (yyval.expNode) = new BoolNode(false); 
                      (yyval.expNode)->setLineNum( yylineno );
                      g_collector.insert( (yyval.expNode) ); }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 175 "etc/fun_lang.y"
    { (yyval.expNode) = new StringNode( getStrVal((yyvsp[(1) - (1)].strIdx)) ); 
                      (yyval.expNode)->setLineNum( yylineno ); 
                      g_collector.insert( (yyval.expNode) ); }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 179 "etc/fun_lang.y"
    { (yyval.expNode) = new CharNode((yyvsp[(1) - (1)].charVal)); 
                      (yyval.expNode)->setLineNum( yylineno ); 
                      g_collector.insert( (yyval.expNode) ); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 182 "etc/fun_lang.y"
    { (yyval.expNode) = new VarRefNode( getStrVal((yyvsp[(1) - (1)].strIdx)) ); 
                      (yyval.expNode)->setLineNum( yylineno ); 
                      g_collector.insert( (yyval.expNode) );  
                    }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 187 "etc/fun_lang.y"
    { VarRefNode* var = new VarRefNode( getStrVal((yyvsp[(1) - (3)].strIdx)) ); 
                      var->setLineNum(yylineno); 
                      g_collector.insert( var );

                      (yyval.expNode) = new AssignNode( var, (yyvsp[(3) - (3)].expNode) ); 
                      (yyval.expNode)->setLineNum( yylineno );
                      g_collector.insert( (yyval.expNode) );
                    }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 195 "etc/fun_lang.y"
    { (yyval.expNode) = new AddNode( (yyvsp[(1) - (3)].expNode), (yyvsp[(3) - (3)].expNode) ); 
                        (yyval.expNode)->setLineNum( yylineno );
                        g_collector.insert( (yyval.expNode) );  }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 198 "etc/fun_lang.y"
    { (yyval.expNode) = new SubNode( (yyvsp[(1) - (3)].expNode), (yyvsp[(3) - (3)].expNode) ); 
                        (yyval.expNode)->setLineNum( yylineno );
                        g_collector.insert( (yyval.expNode) );  }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 201 "etc/fun_lang.y"
    { (yyval.expNode) = new MulNode( (yyvsp[(1) - (3)].expNode), (yyvsp[(3) - (3)].expNode) ); 
                        (yyval.expNode)->setLineNum( yylineno );
                        g_collector.insert( (yyval.expNode) );  }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 204 "etc/fun_lang.y"
    { (yyval.expNode) = new DivNode( (yyvsp[(1) - (3)].expNode), (yyvsp[(3) - (3)].expNode) ); 
                        (yyval.expNode)->setLineNum( yylineno );
                        g_collector.insert( (yyval.expNode) );  }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 207 "etc/fun_lang.y"
    { (yyval.expNode) = new LtNode( (yyvsp[(1) - (3)].expNode), (yyvsp[(3) - (3)].expNode) );  
                        (yyval.expNode)->setLineNum( yylineno );
                        g_collector.insert( (yyval.expNode) );  }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 210 "etc/fun_lang.y"
    { (yyval.expNode) = new AndNode( (yyvsp[(1) - (3)].expNode), (yyvsp[(3) - (3)].expNode) ); 
                        (yyval.expNode)->setLineNum( yylineno );
                        g_collector.insert( (yyval.expNode) );  }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 213 "etc/fun_lang.y"
    { (yyval.expNode) = new EqNode( (yyvsp[(1) - (3)].expNode), (yyvsp[(3) - (3)].expNode) );  
                        (yyval.expNode)->setLineNum( yylineno );
                        g_collector.insert( (yyval.expNode) );  }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 216 "etc/fun_lang.y"
    { (yyval.expNode) = (yyvsp[(2) - (3)].expNode); }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 217 "etc/fun_lang.y"
    { (yyval.expNode) = (yyvsp[(1) - (1)].callNode); }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 218 "etc/fun_lang.y"
    { (yyval.expNode) = new NewNode( getStrVal((yyvsp[(2) - (2)].strIdx)) ); 
                        g_collector.insert( (yyval.expNode) );}
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 222 "etc/fun_lang.y"
    { (yyval.declareNode) = (yyvsp[(1) - (2)].declareNode);
                                 (yyvsp[(2) - (2)].assignNode)->setVarDataTypeNode( (yyvsp[(1) - (2)].declareNode)->getDataTypeNode() );
                                 (yyval.declareNode)->addDeclare( (yyvsp[(2) - (2)].assignNode) );
                                 (yyval.declareNode)->setLineNum( yylineno );
					           }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 229 "etc/fun_lang.y"
    { (yyval.declareNode) = (yyvsp[(1) - (3)].declareNode);
                                       (yyvsp[(2) - (3)].assignNode)->setVarDataTypeNode( (yyvsp[(1) - (3)].declareNode)->getDataTypeNode() );
                                       (yyval.declareNode)->addDeclare( (yyvsp[(2) - (3)].assignNode) );
                                       (yyval.declareNode)->setLineNum( yylineno );
							         }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 234 "etc/fun_lang.y"
    { (yyval.declareNode) = new DeclareNode();
		                     (yyval.declareNode)->setDataTypeNode((yyvsp[(1) - (1)].dataTypeNode));
							 (yyval.declareNode)->setLineNum( yylineno );
                             g_collector.insert( (yyval.declareNode) );
						   }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 240 "etc/fun_lang.y"
    { VarNode* var = new VarDeclareNode( getStrVal((yyvsp[(1) - (1)].strIdx)) );
                             var->setLineNum( yylineno );
                             g_collector.insert( var );
                             (yyval.assignNode) = new AssignNode( var );
                             (yyval.assignNode)->setLineNum( yylineno );
                             g_collector.insert( (yyval.assignNode) );
                           }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 247 "etc/fun_lang.y"
    { VarNode* var = new VarDeclareNode( getStrVal((yyvsp[(1) - (3)].strIdx)));
                             var->setLineNum( yylineno );
                             g_collector.insert( var );

                             (yyval.assignNode) = new AssignNode( var, (yyvsp[(3) - (3)].expNode) );  
                             (yyval.assignNode)->setLineNum( yylineno );
                             g_collector.insert( (yyval.assignNode) );
                           }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 258 "etc/fun_lang.y"
    { (yyval.dataTypeNode) = INT_TYPE_NODE;     }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 259 "etc/fun_lang.y"
    { (yyval.dataTypeNode) = BOOL_TYPE_NODE;    }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 260 "etc/fun_lang.y"
    { (yyval.dataTypeNode) = CHAR_TYPE_NODE;    }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 261 "etc/fun_lang.y"
    { (yyval.dataTypeNode) = STRING_TYPE_NODE;  }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 262 "etc/fun_lang.y"
    { (yyval.dataTypeNode) = new ClassTypeNode( getStrVal((yyvsp[(1) - (1)].strIdx)) );
                  (yyval.dataTypeNode)->setLineNum( yylineno); 
                  g_collector.insert( (yyval.dataTypeNode) );
                }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 273 "etc/fun_lang.y"
    {  
              (yyval.ifNode) = new IfNode( (yyvsp[(3) - (11)].expNode), (yyvsp[(6) - (11)].syntaxNode), (yyvsp[(10) - (11)].syntaxNode) );
              (yyval.ifNode)->setLineNum( (yyvsp[(1) - (11)].lineNum) );
              g_collector.insert( (yyval.ifNode) );
          }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 279 "etc/fun_lang.y"
    { (yyval.ifNode) = new IfNode( (yyvsp[(3) - (9)].expNode), (yyvsp[(6) - (9)].syntaxNode), (yyvsp[(9) - (9)].syntaxNode) ); 
                                                                  (yyval.ifNode)->setLineNum( (yyvsp[(1) - (9)].lineNum) );
                                                                  g_collector.insert( (yyval.ifNode) );

                                                                }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 284 "etc/fun_lang.y"
    { (yyval.ifNode) = new IfNode( (yyvsp[(3) - (9)].expNode), (yyvsp[(5) - (9)].syntaxNode), (yyvsp[(8) - (9)].syntaxNode) ); 
                                                                  (yyval.ifNode)->setLineNum( (yyvsp[(1) - (9)].lineNum) );
                                                                  g_collector.insert( (yyval.ifNode) );

                                                                }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 289 "etc/fun_lang.y"
    { (yyval.ifNode) = new IfNode( (yyvsp[(3) - (7)].expNode), (yyvsp[(5) - (7)].syntaxNode), (yyvsp[(7) - (7)].syntaxNode) ); 
                                                                  (yyval.ifNode)->setLineNum( (yyvsp[(1) - (7)].lineNum) );
                                                                  g_collector.insert( (yyval.ifNode) );
                                                                }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 293 "etc/fun_lang.y"
    { (yyval.ifNode) = new IfNode( (yyvsp[(3) - (7)].expNode), (yyvsp[(6) - (7)].syntaxNode) );
                                                                  (yyval.ifNode)->setLineNum( (yyvsp[(1) - (7)].lineNum) );
                                                                  g_collector.insert( (yyval.ifNode) );
                                                                }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 297 "etc/fun_lang.y"
    { (yyval.ifNode) = new IfNode( (yyvsp[(3) - (5)].expNode), (yyvsp[(5) - (5)].syntaxNode) ); 
                                                                  (yyval.ifNode)->setLineNum( (yyvsp[(1) - (5)].lineNum) );
                                                                  g_collector.insert( (yyval.ifNode) );
                                                                }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 302 "etc/fun_lang.y"
    { (yyval.whileNode) = new WhileNode( (yyvsp[(3) - (7)].expNode), (yyvsp[(6) - (7)].syntaxNode) );
                                                         (yyval.whileNode)->setLineNum( (yyvsp[(1) - (7)].lineNum) );
                                                         g_collector.insert( (yyval.whileNode) );
                                                       }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 306 "etc/fun_lang.y"
    { (yyval.whileNode) = new WhileNode( (yyvsp[(3) - (5)].expNode), (yyvsp[(5) - (5)].syntaxNode) );
                                                  (yyval.whileNode)->setLineNum( (yyvsp[(1) - (5)].lineNum) );
                                                  g_collector.insert( (yyval.whileNode) );
                                                }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 312 "etc/fun_lang.y"
    { (yyval.funcNode) = (yyvsp[(4) - (9)].funcNode); 
                                                                      (yyval.funcNode)->setName( getStrVal((yyvsp[(2) - (9)].strIdx))); 
                                                                      (yyval.funcNode)->setRetType((yyvsp[(6) - (9)].dataTypeNode));
                                                                      (yyval.funcNode)->setBody((yyvsp[(8) - (9)].syntaxNode));
                                                                      (yyval.funcNode)->setLineNum( (yyvsp[(1) - (9)].lineNum) );
                                                                    }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 318 "etc/fun_lang.y"
    { (yyval.funcNode) = new GlobalFuncNode( getStrVal((yyvsp[(2) - (8)].strIdx)), (yyvsp[(5) - (8)].dataTypeNode), (yyvsp[(7) - (8)].syntaxNode) );
                                                                      (yyval.funcNode)->setLineNum( (yyvsp[(1) - (8)].lineNum) );
                                                                      g_collector.insert( (yyval.funcNode) );
                                                                    }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 324 "etc/fun_lang.y"
    { (yyval.dataTypeNode) = (yyvsp[(1) - (1)].dataTypeNode); }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 325 "etc/fun_lang.y"
    { (yyval.dataTypeNode) = VOID_TYPE_NODE; }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 329 "etc/fun_lang.y"
    {  (yyval.funcNode) = (yyvsp[(1) - (4)].funcNode); 
                                                 (yyval.funcNode)->addParam( VarNode( getStrVal( (yyvsp[(4) - (4)].strIdx) ), (yyvsp[(3) - (4)].dataTypeNode)) ); 
                                              }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 332 "etc/fun_lang.y"
    {  (yyval.funcNode) = new GlobalFuncNode();
                                                 (yyval.funcNode)->addParam( VarNode( getStrVal( (yyvsp[(2) - (2)].strIdx) ), (yyvsp[(1) - (2)].dataTypeNode) ) );
                                                 g_collector.insert( (yyval.funcNode) );
                                              }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 338 "etc/fun_lang.y"
    { (yyval.callNode) = (yyvsp[(3) - (4)].callNode); 
                                    (yyval.callNode)->setFuncName( getStrVal((yyvsp[(1) - (4)].strIdx)) ); 
                                  }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 341 "etc/fun_lang.y"
    { (yyval.callNode) = (yyvsp[(5) - (6)].callNode);
                                             (yyval.callNode)->setLineNum( (yyvsp[(2) - (6)].lineNum) );
                                             (yyval.callNode)->setFuncName( getStrVal((yyvsp[(3) - (6)].strIdx)) );
                                             (yyval.callNode)->setMemberFuncHint( true );
                                             (yyval.callNode)->setCallerName(getStrVal( (yyvsp[(1) - (6)].strIdx) ));
                                           }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 347 "etc/fun_lang.y"
    { (yyval.callNode) = (yyvsp[(5) - (6)].callNode);
                                             (yyval.callNode)->setLineNum( (yyvsp[(2) - (6)].lineNum) );
                                             (yyval.callNode)->setFuncName( getStrVal((yyvsp[(3) - (6)].strIdx)) );
                                             (yyval.callNode)->setMemberFuncHint( true );
                                           }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 354 "etc/fun_lang.y"
    { (yyval.callNode) = (yyvsp[(1) - (1)].callNode); }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 355 "etc/fun_lang.y"
    { (yyval.callNode) = new CallNode(); 
                                   g_collector.insert( (yyval.callNode) );
                                 }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 360 "etc/fun_lang.y"
    { (yyval.callNode) = (yyvsp[(1) - (3)].callNode);
                                   (yyval.callNode)->addParam( (yyvsp[(3) - (3)].expNode) ); 
                                   g_collector.insert( (yyval.callNode) );
                                 }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 364 "etc/fun_lang.y"
    { (yyval.callNode) = new CallNode();
                                   (yyval.callNode)->addParam( (yyvsp[(1) - (1)].expNode) );
                                   (yyval.callNode)->setLineNum( yylineno );
                                   g_collector.insert( (yyval.callNode) );
                                 }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 371 "etc/fun_lang.y"
    { (yyval.classNode) = (yyvsp[(4) - (5)].classNode);
                                                     (yyval.classNode)->setName( getStrVal((yyvsp[(2) - (5)].strIdx)) );
                                                     (yyval.classNode)->setLineNum( (yyvsp[(1) - (5)].lineNum) );
                                                   }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 375 "etc/fun_lang.y"
    { (yyval.classNode) = (yyvsp[(6) - (7)].classNode);
                                                     (yyval.classNode)->setParentName( getStrVal( (yyvsp[(4) - (7)].strIdx) ) );
                                                     (yyval.classNode)->setName( getStrVal((yyvsp[(2) - (7)].strIdx)) );
                                                     (yyval.classNode)->setLineNum( (yyvsp[(1) - (7)].lineNum) );
                                                   }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 383 "etc/fun_lang.y"
    { (yyval.classNode) = (yyvsp[(1) - (3)].classNode);
                                                (yyval.classNode)->addVarDeclare( (yyvsp[(2) - (3)].declareNode) );
                                              }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 386 "etc/fun_lang.y"
    { (yyval.classNode) = (yyvsp[(1) - (2)].classNode);
                                                
                                                // create a new class function to wrap a global function
                                                ClassFuncNode* classFunc = new ClassFuncNode( (yyvsp[(1) - (2)].classNode), (yyvsp[(2) - (2)].funcNode) );

                                                // add the function to the class
                                                (yyval.classNode)->addFuncion( classFunc );

                                                g_collector.insert( classFunc );
                                                g_collector.collect( (yyvsp[(2) - (2)].funcNode) );
                                              }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 397 "etc/fun_lang.y"
    { (yyval.classNode) = new ClassNode();  
                                                g_collector.insert( (yyval.classNode) );
                                              }
    break;



/* Line 1806 of yacc.c  */
#line 2329 "etc/fun_lang_yacc.cpp"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (program, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (program, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, program);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, program);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (program, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, program);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, program);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 402 "etc/fun_lang.y"


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



