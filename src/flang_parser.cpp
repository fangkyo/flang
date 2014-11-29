// A Bison parser, made by GNU Bison 3.0.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2013 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

#line 37 "flang_parser.cpp" // lalr1.cc:399

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "flang_parser.h"

// User implementation prologue.

#line 51 "flang_parser.cpp" // lalr1.cc:407
// Unqualified %code blocks.
#line 29 "flang_parser.y" // lalr1.cc:408

#include <cstdio>
#include <iostream>

#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>

#include "flang_scanner.h"

using namespace std;
using namespace log4cxx;

extern string& getStrVal(int idx);
/* void yyerror(SyntaxNode* &program, const char*); */
LoggerPtr g_logger(Logger::getLogger("yacc"));

static int yylex(flang::FlangParser::semantic_type *yylval,
                 flang::FlangScanner &scanner) {
   return scanner.yylex(yylval);
}

#line 75 "flang_parser.cpp" // lalr1.cc:408


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif



// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyempty = true)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 5 "flang_parser.y" // lalr1.cc:474
namespace flang {
#line 142 "flang_parser.cpp" // lalr1.cc:474

  /// Build a parser object.
  FlangParser::FlangParser (FlangScanner& scanner_yyarg, SyntaxNode* &program_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      scanner (scanner_yyarg),
      program (program_yyarg)
  {}

  FlangParser::~FlangParser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  FlangParser::syntax_error::syntax_error (const std::string& m)
    : std::runtime_error (m)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  FlangParser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  FlangParser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
  {
    value = other.value;
  }


  template <typename Base>
  inline
  FlangParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v)
    : Base (t)
    , value (v)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  FlangParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t)
    : Base (t)
    , value ()
  {}

  template <typename Base>
  inline
  FlangParser::basic_symbol<Base>::~basic_symbol ()
  {
  }

  template <typename Base>
  inline
  void
  FlangParser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
  }

  // by_type.
  inline
  FlangParser::by_type::by_type ()
     : type (empty)
  {}

  inline
  FlangParser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  FlangParser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  FlangParser::by_type::move (by_type& that)
  {
    type = that.type;
    that.type = empty;
  }

  inline
  int
  FlangParser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  FlangParser::by_state::by_state ()
    : state (empty)
  {}

  inline
  FlangParser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  FlangParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.state = empty;
  }

  inline
  FlangParser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  FlangParser::symbol_number_type
  FlangParser::by_state::type_get () const
  {
    return state == empty ? 0 : yystos_[state];
  }

  inline
  FlangParser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  FlangParser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s)
  {
    value = that.value;
    // that is emptied.
    that.type = empty;
  }

  inline
  FlangParser::stack_symbol_type&
  FlangParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    return *this;
  }


  template <typename Base>
  inline
  void
  FlangParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YYUSE (yysym.type_get ());
  }

#if YYDEBUG
  template <typename Base>
  void
  FlangParser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " (";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  FlangParser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  FlangParser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  FlangParser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  FlangParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  FlangParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  FlangParser::debug_level_type
  FlangParser::debug_level () const
  {
    return yydebug_;
  }

  void
  FlangParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline FlangParser::state_type
  FlangParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  FlangParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  FlangParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  FlangParser::parse ()
  {
    /// Whether yyla contains a lookahead.
    bool yyempty = true;

    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyempty)
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, scanner));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
        yyempty = false;
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Discard the token being shifted.
    yyempty = true;

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;


      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 112 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.syntaxNode) = (yystack_[0].value.stmtListNode);
  program = (yystack_[0].value.stmtListNode);
}
#line 542 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 3:
#line 115 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.syntaxNode) = NULL;
  program = NULL;
}
#line 551 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 4:
#line 120 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.stmtListNode) = new StmtListNode();
  (yylhs.value.stmtListNode)->setLineNum(scanner.lineno());
  (yylhs.value.stmtListNode)->addStmt( (yystack_[0].value.syntaxNode) );
  g_collector.insert( (yylhs.value.stmtListNode) );
}
#line 562 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 5:
#line 125 "flang_parser.y" // lalr1.cc:847
    {
  (yystack_[1].value.stmtListNode)->addStmt( (yystack_[0].value.syntaxNode) );
  (yylhs.value.stmtListNode) = (yystack_[1].value.stmtListNode);
}
#line 571 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 6:
#line 130 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.syntaxNode) = (yystack_[0].value.syntaxNode);
}
#line 579 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 7:
#line 132 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.syntaxNode) = (yystack_[0].value.syntaxNode);
}
#line 587 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 8:
#line 136 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.syntaxNode) = (yystack_[0].value.stmtListNode);
}
#line 595 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 9:
#line 138 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.syntaxNode) = NULL;
}
#line 603 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 10:
#line 142 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.stmtListNode) = new StmtListNode();
  (yylhs.value.stmtListNode)->setLineNum(scanner.lineno());
  (yylhs.value.stmtListNode)->addStmt( (yystack_[0].value.syntaxNode) );
  g_collector.insert( (yylhs.value.stmtListNode) );
}
#line 614 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 11:
#line 147 "flang_parser.y" // lalr1.cc:847
    {
  (yystack_[1].value.stmtListNode)->addStmt( (yystack_[0].value.syntaxNode) );
}
#line 622 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 12:
#line 151 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.syntaxNode) = (yystack_[0].value.funcNode);
}
#line 630 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 13:
#line 153 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.syntaxNode) = (yystack_[0].value.classNode);
}
#line 638 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 14:
#line 157 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.syntaxNode) = NULL;
}
#line 646 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 15:
#line 159 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.syntaxNode) = (yystack_[1].value.expNode);
}
#line 654 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 16:
#line 161 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.syntaxNode) = new PrintNode( (yystack_[1].value.expNode) );
  (yylhs.value.syntaxNode)->setLineNum( (yystack_[2].value.lineNum) );
  g_collector.insert( (yylhs.value.syntaxNode) );
}
#line 664 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 17:
#line 165 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.syntaxNode) = new ReturnNode( (yystack_[1].value.expNode) );
  (yylhs.value.syntaxNode)->setLineNum( (yystack_[2].value.lineNum) );
  g_collector.insert( (yylhs.value.syntaxNode) );
}
#line 674 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 18:
#line 169 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.syntaxNode) = new ReturnNode();
  (yylhs.value.syntaxNode)->setLineNum( (yystack_[1].value.lineNum) );
  g_collector.insert( (yylhs.value.syntaxNode) );
}
#line 684 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 19:
#line 173 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.syntaxNode) = new BreakNode();
  (yylhs.value.syntaxNode)->setLineNum( (yystack_[1].value.lineNum) );
  g_collector.insert( (yylhs.value.syntaxNode) );
}
#line 694 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 20:
#line 177 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.syntaxNode) = (yystack_[1].value.declareNode);
}
#line 702 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 21:
#line 179 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.syntaxNode) = (yystack_[0].value.ifNode);
}
#line 710 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 22:
#line 181 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.syntaxNode) = (yystack_[0].value.whileNode);
}
#line 718 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 23:
#line 185 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.expNode) = new IntNode( (yystack_[0].value.intVal) );
  (yylhs.value.expNode)->setLineNum( scanner.lineno() );
  g_collector.insert( (yylhs.value.expNode) );
}
#line 728 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 24:
#line 189 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.expNode) = new BoolNode(true);
  (yylhs.value.expNode)->setLineNum(scanner.lineno());
  g_collector.insert( (yylhs.value.expNode) );
}
#line 738 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 25:
#line 193 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.expNode) = new BoolNode(false);
  (yylhs.value.expNode)->setLineNum( scanner.lineno() );
  g_collector.insert( (yylhs.value.expNode) );
}
#line 748 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 26:
#line 197 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.expNode) = new StringNode( getStrVal((yystack_[0].value.strIdx)) );
  (yylhs.value.expNode)->setLineNum( scanner.lineno() );
  g_collector.insert( (yylhs.value.expNode) );
}
#line 758 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 27:
#line 201 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.expNode) = new CharNode((yystack_[0].value.charVal));
  (yylhs.value.expNode)->setLineNum( scanner.lineno() );
  g_collector.insert( (yylhs.value.expNode) );
}
#line 768 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 28:
#line 205 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.expNode) = new VarRefNode( getStrVal((yystack_[0].value.strIdx)) );
  (yylhs.value.expNode)->setLineNum( scanner.lineno() );
  g_collector.insert( (yylhs.value.expNode) );
}
#line 778 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 29:
#line 209 "flang_parser.y" // lalr1.cc:847
    {
  VarRefNode* var = new VarRefNode(getStrVal((yystack_[2].value.strIdx)));
  var->setLineNum(scanner.lineno());
  g_collector.insert( var );
  (yylhs.value.expNode) = new AssignNode( var, (yystack_[0].value.expNode) );
  (yylhs.value.expNode)->setLineNum( scanner.lineno() );
  g_collector.insert( (yylhs.value.expNode) );
}
#line 791 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 30:
#line 216 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.expNode) = new AddNode( (yystack_[2].value.expNode), (yystack_[0].value.expNode) );
  (yylhs.value.expNode)->setLineNum( scanner.lineno() );
  g_collector.insert( (yylhs.value.expNode) );
}
#line 801 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 31:
#line 220 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.expNode) = new SubNode( (yystack_[2].value.expNode), (yystack_[0].value.expNode) );
  (yylhs.value.expNode)->setLineNum( scanner.lineno() );
  g_collector.insert( (yylhs.value.expNode) );
}
#line 811 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 32:
#line 224 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.expNode) = new MulNode( (yystack_[2].value.expNode), (yystack_[0].value.expNode) );
  (yylhs.value.expNode)->setLineNum( scanner.lineno() );
  g_collector.insert( (yylhs.value.expNode) );
}
#line 821 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 33:
#line 228 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.expNode) = new DivNode( (yystack_[2].value.expNode), (yystack_[0].value.expNode) );
  (yylhs.value.expNode)->setLineNum( scanner.lineno() );
  g_collector.insert( (yylhs.value.expNode) );
}
#line 831 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 34:
#line 232 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.expNode) = new LtNode( (yystack_[2].value.expNode), (yystack_[0].value.expNode) );
  (yylhs.value.expNode)->setLineNum( scanner.lineno() );
  g_collector.insert( (yylhs.value.expNode) );
}
#line 841 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 35:
#line 236 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.expNode) = new AndNode( (yystack_[2].value.expNode), (yystack_[0].value.expNode) );
  (yylhs.value.expNode)->setLineNum( scanner.lineno() );
  g_collector.insert( (yylhs.value.expNode) );
}
#line 851 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 36:
#line 240 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.expNode) = new EqNode( (yystack_[2].value.expNode), (yystack_[0].value.expNode) );
  (yylhs.value.expNode)->setLineNum( scanner.lineno() );
  g_collector.insert( (yylhs.value.expNode) );
}
#line 861 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 37:
#line 244 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.expNode) = (yystack_[1].value.expNode);
}
#line 869 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 38:
#line 246 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.expNode) = (yystack_[0].value.callNode);
}
#line 877 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 39:
#line 248 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.expNode) = new NewNode( getStrVal((yystack_[0].value.strIdx)) );
  g_collector.insert( (yylhs.value.expNode) );
}
#line 886 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 40:
#line 253 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.declareNode) = (yystack_[1].value.declareNode);
  (yystack_[0].value.assignNode)->setVarDataTypeNode( (yystack_[1].value.declareNode)->getDataTypeNode() );
  (yylhs.value.declareNode)->addDeclare( (yystack_[0].value.assignNode) );
  (yylhs.value.declareNode)->setLineNum( scanner.lineno() );
}
#line 897 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 41:
#line 260 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.declareNode) = (yystack_[2].value.declareNode);
  (yystack_[1].value.assignNode)->setVarDataTypeNode( (yystack_[2].value.declareNode)->getDataTypeNode() );
  (yylhs.value.declareNode)->addDeclare( (yystack_[1].value.assignNode) );
  (yylhs.value.declareNode)->setLineNum( scanner.lineno() );
}
#line 908 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 42:
#line 265 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.declareNode) = new DeclareNode();
  (yylhs.value.declareNode)->setDataTypeNode((yystack_[0].value.dataTypeNode));
  (yylhs.value.declareNode)->setLineNum( scanner.lineno() );
  g_collector.insert( (yylhs.value.declareNode) );
}
#line 919 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 43:
#line 272 "flang_parser.y" // lalr1.cc:847
    {
  VarNode* var = new VarDeclareNode( getStrVal((yystack_[0].value.strIdx)) );
  var->setLineNum( scanner.lineno() );
  g_collector.insert( var );
  (yylhs.value.assignNode) = new AssignNode( var );
  (yylhs.value.assignNode)->setLineNum( scanner.lineno() );
  g_collector.insert( (yylhs.value.assignNode) );
}
#line 932 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 44:
#line 279 "flang_parser.y" // lalr1.cc:847
    {
  VarNode* var = new VarDeclareNode( getStrVal((yystack_[2].value.strIdx)));
  var->setLineNum( scanner.lineno() );
  g_collector.insert( var );
  (yylhs.value.assignNode) = new AssignNode( var, (yystack_[0].value.expNode) );
  (yylhs.value.assignNode)->setLineNum( scanner.lineno() );
  g_collector.insert( (yylhs.value.assignNode) );
}
#line 945 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 45:
#line 288 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.dataTypeNode) = INT_TYPE_NODE;
}
#line 953 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 46:
#line 290 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.dataTypeNode) = BOOL_TYPE_NODE;
}
#line 961 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 47:
#line 292 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.dataTypeNode) = CHAR_TYPE_NODE;
}
#line 969 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 48:
#line 294 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.dataTypeNode) = STRING_TYPE_NODE;
}
#line 977 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 49:
#line 296 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.dataTypeNode) = new ClassTypeNode( getStrVal((yystack_[0].value.strIdx)) );
  (yylhs.value.dataTypeNode)->setLineNum( scanner.lineno());
  g_collector.insert( (yylhs.value.dataTypeNode) );
}
#line 987 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 50:
#line 306 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.ifNode) = new IfNode( (yystack_[8].value.expNode), (yystack_[5].value.syntaxNode), (yystack_[1].value.syntaxNode) );
  (yylhs.value.ifNode)->setLineNum( (yystack_[10].value.lineNum) );
  g_collector.insert( (yylhs.value.ifNode) );
}
#line 997 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 51:
#line 310 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.ifNode) = new IfNode( (yystack_[6].value.expNode), (yystack_[3].value.syntaxNode), (yystack_[0].value.syntaxNode) );
  (yylhs.value.ifNode)->setLineNum( (yystack_[8].value.lineNum) );
  g_collector.insert( (yylhs.value.ifNode) );
}
#line 1007 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 52:
#line 314 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.ifNode) = new IfNode( (yystack_[6].value.expNode), (yystack_[4].value.syntaxNode), (yystack_[1].value.syntaxNode) );
  (yylhs.value.ifNode)->setLineNum( (yystack_[8].value.lineNum) );
  g_collector.insert( (yylhs.value.ifNode) );
}
#line 1017 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 53:
#line 318 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.ifNode) = new IfNode( (yystack_[4].value.expNode), (yystack_[2].value.syntaxNode), (yystack_[0].value.syntaxNode) );
  (yylhs.value.ifNode)->setLineNum( (yystack_[6].value.lineNum) );
  g_collector.insert( (yylhs.value.ifNode) );
}
#line 1027 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 54:
#line 322 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.ifNode) = new IfNode( (yystack_[4].value.expNode), (yystack_[1].value.syntaxNode) );
  (yylhs.value.ifNode)->setLineNum( (yystack_[6].value.lineNum) );
  g_collector.insert( (yylhs.value.ifNode) );
}
#line 1037 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 55:
#line 326 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.ifNode) = new IfNode( (yystack_[2].value.expNode), (yystack_[0].value.syntaxNode) );
  (yylhs.value.ifNode)->setLineNum( (yystack_[4].value.lineNum) );
  g_collector.insert( (yylhs.value.ifNode) );
}
#line 1047 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 56:
#line 332 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.whileNode) = new WhileNode( (yystack_[4].value.expNode), (yystack_[1].value.syntaxNode) );
  (yylhs.value.whileNode)->setLineNum( (yystack_[6].value.lineNum) );
  g_collector.insert( (yylhs.value.whileNode) );
}
#line 1057 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 57:
#line 336 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.whileNode) = new WhileNode( (yystack_[2].value.expNode), (yystack_[0].value.syntaxNode) );
  (yylhs.value.whileNode)->setLineNum( (yystack_[4].value.lineNum) );
  g_collector.insert( (yylhs.value.whileNode) );
}
#line 1067 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 58:
#line 342 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.funcNode) = (yystack_[5].value.funcNode);
  (yylhs.value.funcNode)->setName( getStrVal((yystack_[7].value.strIdx)));
  (yylhs.value.funcNode)->setRetType((yystack_[3].value.dataTypeNode));
  (yylhs.value.funcNode)->setBody((yystack_[1].value.syntaxNode));
  (yylhs.value.funcNode)->setLineNum( (yystack_[8].value.lineNum) );
}
#line 1079 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 59:
#line 348 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.funcNode) = new GlobalFuncNode( getStrVal((yystack_[6].value.strIdx)), (yystack_[3].value.dataTypeNode), (yystack_[1].value.syntaxNode) );
  (yylhs.value.funcNode)->setLineNum( (yystack_[7].value.lineNum) );
  g_collector.insert( (yylhs.value.funcNode) );
}
#line 1089 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 60:
#line 354 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.dataTypeNode) = (yystack_[0].value.dataTypeNode);
}
#line 1097 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 61:
#line 356 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.dataTypeNode) = VOID_TYPE_NODE;
}
#line 1105 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 62:
#line 360 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.funcNode) = (yystack_[3].value.funcNode);
  (yylhs.value.funcNode)->addParam( VarNode( getStrVal( (yystack_[0].value.strIdx) ), (yystack_[1].value.dataTypeNode)) );
}
#line 1114 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 63:
#line 363 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.funcNode) = new GlobalFuncNode();
  (yylhs.value.funcNode)->addParam( VarNode( getStrVal( (yystack_[0].value.strIdx) ), (yystack_[1].value.dataTypeNode) ) );
  g_collector.insert( (yylhs.value.funcNode) );
}
#line 1124 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 64:
#line 369 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.callNode) = (yystack_[1].value.callNode);
  (yylhs.value.callNode)->setFuncName( getStrVal((yystack_[3].value.strIdx)) );
}
#line 1133 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 65:
#line 372 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.callNode) = (yystack_[1].value.callNode);
  (yylhs.value.callNode)->setLineNum( (yystack_[4].value.lineNum) );
  (yylhs.value.callNode)->setFuncName( getStrVal((yystack_[3].value.strIdx)) );
  (yylhs.value.callNode)->setMemberFuncHint( true );
  (yylhs.value.callNode)->setCallerName(getStrVal( (yystack_[5].value.strIdx) ));
}
#line 1145 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 66:
#line 378 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.callNode) = (yystack_[1].value.callNode);
  (yylhs.value.callNode)->setLineNum( (yystack_[4].value.lineNum) );
  (yylhs.value.callNode)->setFuncName( getStrVal((yystack_[3].value.strIdx)) );
  (yylhs.value.callNode)->setMemberFuncHint( true );
}
#line 1156 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 67:
#line 385 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.callNode) = (yystack_[0].value.callNode);
}
#line 1164 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 68:
#line 387 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.callNode) = new CallNode();
  g_collector.insert( (yylhs.value.callNode) );
}
#line 1173 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 69:
#line 392 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.callNode) = (yystack_[2].value.callNode);
  (yylhs.value.callNode)->addParam( (yystack_[0].value.expNode) );
  g_collector.insert( (yylhs.value.callNode) );
}
#line 1183 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 70:
#line 396 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.callNode) = new CallNode();
  (yylhs.value.callNode)->addParam( (yystack_[0].value.expNode) );
  (yylhs.value.callNode)->setLineNum( scanner.lineno() );
  g_collector.insert( (yylhs.value.callNode) );
}
#line 1194 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 71:
#line 403 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.classNode) = (yystack_[1].value.classNode);
  (yylhs.value.classNode)->setName( getStrVal((yystack_[3].value.strIdx)) );
  (yylhs.value.classNode)->setLineNum( (yystack_[4].value.lineNum) );
}
#line 1204 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 72:
#line 407 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.classNode) = (yystack_[1].value.classNode);
  (yylhs.value.classNode)->setParentName( getStrVal( (yystack_[3].value.strIdx) ) );
  (yylhs.value.classNode)->setName( getStrVal((yystack_[5].value.strIdx)) );
  (yylhs.value.classNode)->setLineNum( (yystack_[6].value.lineNum) );
}
#line 1215 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 73:
#line 414 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.classNode) = (yystack_[2].value.classNode);
  (yylhs.value.classNode)->addVarDeclare( (yystack_[1].value.declareNode) );
}
#line 1224 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 74:
#line 417 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.classNode) = (yystack_[1].value.classNode);
  // create a new class function to wrap a global function
  ClassFuncNode* classFunc = new ClassFuncNode( (yystack_[1].value.classNode), (yystack_[0].value.funcNode) );
  // add the function to the class
  (yylhs.value.classNode)->addFuncion( classFunc );
  g_collector.insert( classFunc );
  g_collector.collect( (yystack_[0].value.funcNode) );
}
#line 1238 "flang_parser.cpp" // lalr1.cc:847
    break;

  case 75:
#line 425 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.classNode) = new ClassNode();
  g_collector.insert( (yylhs.value.classNode) );
}
#line 1247 "flang_parser.cpp" // lalr1.cc:847
    break;


#line 1251 "flang_parser.cpp" // lalr1.cc:847
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yysyntax_error_ (yystack_[0].state,
                                           yyempty ? yyempty_ : yyla.type_get ()));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyempty)
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyempty = true;
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }


      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyempty)
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyempty)
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  FlangParser::error (const syntax_error& yyexc)
  {
    error (yyexc.what());
  }

  // Generate an error message.
  std::string
  FlangParser::yysyntax_error_ (state_type, symbol_number_type) const
  {
    return YY_("syntax error");
  }


  const signed char FlangParser::yypact_ninf_ = -97;

  const signed char FlangParser::yytable_ninf_ = -50;

  const short int
  FlangParser::yypact_[] =
  {
     265,   -97,   -97,   -97,    -5,   -30,   -27,   294,   -24,    14,
      16,   287,   -21,    37,   -97,   -97,   -97,   -97,   -97,   -97,
     -97,   294,    46,   265,   -97,   -97,   -97,   146,    17,    47,
     -97,   -97,   -97,   -97,   -97,   -97,   294,   294,    77,   294,
     294,   -22,   315,   -97,    44,   -35,   -97,   328,    79,   -97,
     184,   -97,   -97,   294,   294,   294,   294,   294,   294,   294,
     -97,   -97,    63,    48,   341,   341,    51,    64,    67,   223,
     303,   -97,   304,   -97,    82,   -97,    69,   -97,   351,   283,
      66,     6,     6,   -97,   -97,   294,   -97,   -97,   294,   294,
     109,   148,   -97,    10,   104,    38,    87,    90,   294,   341,
     341,    93,    55,   -97,    55,   112,   -97,    95,   -97,    10,
      10,   -97,    97,   -97,   -97,    98,   -97,    96,    55,   -97,
     101,   187,    55,   103,   135,   -97,   126,   -97,   -97,   -97,
     149,    55,   -97,   130,    55,   -97,   -97,   226,   131,   -97,
     132,    55,   -97,   -97,   -97,   133,   -97
  };

  const unsigned char
  FlangParser::yydefact_[] =
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

  const signed char
  FlangParser::yypgoto_[] =
  {
     -97,   -97,   -97,   -23,   -44,   -97,   -97,   -96,    -6,   -89,
     -97,   -97,   -54,   -97,   -97,   -86,    75,   -97,   -97,   -85,
     -97,   -97,    71
  };

  const signed char
  FlangParser::yydefgoto_[] =
  {
      -1,    22,    23,    24,   117,   118,    25,    26,    27,    28,
      29,    63,    30,    31,    32,    33,   107,    95,    34,    66,
      67,    35,    96
  };

  const short int
  FlangParser::yytable_[] =
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
      18,    19,   111,    92,   114,   116,   121,   125,     9,   122,
     127,   128,   135,    14,    15,    16,   130,   134,    19,    20,
      21,     1,     2,   102,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,   136,    53,   137,    54,   139,   143,   144,   146,    55,
      56,    57,    58,    59,   123,   126,    60,     0,    20,    21,
       1,     2,   104,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      53,     0,    54,     0,     0,     0,     0,    55,    56,    57,
      58,    59,     0,     0,     0,     0,    77,    20,    21,     1,
       2,   131,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    53,
       0,    54,     0,     0,     0,     0,    55,    56,    57,    58,
      59,     0,     0,     0,     0,    90,    20,    21,     1,     2,
     141,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,     0,
       1,     2,     0,     3,    41,     0,     0,     1,     2,     0,
       3,    41,    12,    13,     0,    20,    21,    17,    18,    12,
      13,    92,     0,     0,    17,    18,    55,    56,    57,    58,
      59,    14,    15,    16,     0,     0,    19,    46,    21,    53,
       0,    54,     0,     0,     0,    21,    55,    56,    57,    58,
      59,    53,     0,    54,     0,    91,    93,     0,    55,    56,
      57,    58,    59,     0,    53,    71,    54,     0,     0,     0,
       0,    55,    56,    57,    58,    59,     0,    53,    75,    54,
       0,     0,     0,     0,    55,    56,    57,    58,    59,    54,
       0,     0,     0,     0,    55,    56,    57,    58,    59
  };

  const short int
  FlangParser::yycheck_[] =
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
      21,    22,    45,     7,    44,    42,    24,    40,    12,    44,
      42,    45,     7,    17,    18,    19,    45,    44,    22,    40,
      41,     3,     4,    44,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    45,    26,    24,    28,    45,    45,    45,    45,    33,
      34,    35,    36,    37,   109,   114,    40,    -1,    40,    41,
       3,     4,    44,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      26,    -1,    28,    -1,    -1,    -1,    -1,    33,    34,    35,
      36,    37,    -1,    -1,    -1,    -1,    42,    40,    41,     3,
       4,    44,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    26,
      -1,    28,    -1,    -1,    -1,    -1,    33,    34,    35,    36,
      37,    -1,    -1,    -1,    -1,    42,    40,    41,     3,     4,
      44,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    -1,
       3,     4,    -1,     6,     7,    -1,    -1,     3,     4,    -1,
       6,     7,    15,    16,    -1,    40,    41,    20,    21,    15,
      16,     7,    -1,    -1,    20,    21,    33,    34,    35,    36,
      37,    17,    18,    19,    -1,    -1,    22,    40,    41,    26,
      -1,    28,    -1,    -1,    -1,    41,    33,    34,    35,    36,
      37,    26,    -1,    28,    -1,    42,    42,    -1,    33,    34,
      35,    36,    37,    -1,    26,    40,    28,    -1,    -1,    -1,
      -1,    33,    34,    35,    36,    37,    -1,    26,    40,    28,
      -1,    -1,    -1,    -1,    33,    34,    35,    36,    37,    28,
      -1,    -1,    -1,    -1,    33,    34,    35,    36,    37
  };

  const unsigned char
  FlangParser::yystos_[] =
  {
       0,     3,     4,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      40,    41,    49,    50,    51,    54,    55,    56,    57,    58,
      60,    61,    62,    63,    66,    69,    25,    41,    46,    41,
      41,     7,    56,    40,     7,     7,    40,    56,    46,     7,
      56,     0,    51,    26,    28,    33,    34,    35,    36,    37,
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

  const unsigned char
  FlangParser::yyr1_[] =
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

  const unsigned char
  FlangParser::yyr2_[] =
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


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const FlangParser::yytname_[] =
  {
  "$end", "error", "$undefined", "NUMBER", "CHARVAL", "BOOLVAL", "STR",
  "ID", "WHILE", "IF", "PRINT", "BREAK", "DEF", "CLASS", "RETURN", "THIS",
  "NEW", "BOOL", "CHAR", "INT", "TRUE", "FALSE", "STRING", "IFX", "ELSE",
  "'='", "AND", "OR", "EQ", "NE", "GE", "LE", "'>'", "'<'", "'+'", "'-'",
  "'*'", "'/'", "'!'", "UMINUS", "';'", "'('", "')'", "','", "'{'", "'}'",
  "'.'", "':'", "$accept", "program", "stmt_list", "stmt",
  "simple_program", "simple_stmt_list", "complex_stmt", "simple_stmt",
  "expr", "declare", "var_list", "declare_var", "type", "if_stmt",
  "while_stmt", "function", "ret_type", "func_param_list", "call",
  "call_param_list", "param_list", "class", "class_stmt_list", YY_NULLPTR
  };


  const unsigned short int
  FlangParser::yyrline_[] =
  {
       0,   112,   112,   115,   120,   125,   130,   132,   136,   138,
     142,   147,   151,   153,   157,   159,   161,   165,   169,   173,
     177,   179,   181,   185,   189,   193,   197,   201,   205,   209,
     216,   220,   224,   228,   232,   236,   240,   244,   246,   248,
     253,   260,   265,   272,   279,   288,   290,   292,   294,   296,
     302,   310,   314,   318,   322,   326,   332,   336,   342,   348,
     354,   356,   360,   363,   369,   372,   378,   385,   387,   392,
     396,   403,   407,   414,   417,   425
  };

  // Print the state stack on the debug stream.
  void
  FlangParser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  FlangParser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
  FlangParser::token_number_type
  FlangParser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    38,     2,     2,     2,     2,     2,     2,
      41,    42,    36,    34,    43,    35,    46,    37,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    47,    40,
      33,    25,    32,     2,     2,     2,     2,     2,     2,     2,
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
      26,    27,    28,    29,    30,    31,    39
    };
    const unsigned int user_token_number_max_ = 286;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

#line 5 "flang_parser.y" // lalr1.cc:1155
} // flang
#line 1721 "flang_parser.cpp" // lalr1.cc:1155
#line 430 "flang_parser.y" // lalr1.cc:1156


/* void yyerror(SyntaxNode* &program, const char* msg ){ */
  /* printf( "error at line %d : %s\n", scanner.lineno(), msg ); */
/* } */

void flang::FlangParser::error( const std::string &err_message ) {
   std::cerr << "Error: " << err_message << "\n";
}

int main(){

  /* PropertyConfigurator::configure("log4cxx.properties"); */
  /* LOG4CXX_INFO( g_logger, "start to parse program and build abstract syntax tree" ); */
  /* SyntaxTree* program = NULL; */
  /* yyparse( program ); */

  /* if( NULL == program ){ */
    /* LOG4CXX_INFO( g_logger, "program is null" ); */
    /* return 0; */
  /* } */

  /* LOG4CXX_INFO( g_logger, "abstract syntax tree built completed" ); */
  /* LOG4CXX_INFO( g_logger, "start to do type check" ); */

  /* TypeCheckVisitor typeCheckVisitor; */
  /* program->accept( typeCheckVisitor ); */
  /* typeCheckVisitor.printError(); */

  /* LOG4CXX_INFO( g_logger, "type check completed" ); */
  /* program = NULL; */

  return 0;
}


