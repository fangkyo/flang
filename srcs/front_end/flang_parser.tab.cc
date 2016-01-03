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

#line 37 "flang_parser.tab.cc" // lalr1.cc:399

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "flang_parser.tab.hh"

// User implementation prologue.

#line 51 "flang_parser.tab.cc" // lalr1.cc:407
// Unqualified %code blocks.
#line 26 "flang_parser.y" // lalr1.cc:408

#include <cstdio>
#include <iostream>
#include <string>

#include <log4cxx/logger.h>

#include "exception/exception.h"
#include "front_end/flang_scanner.h"

using namespace std;

#undef yylex
// Redefine the default yylex function used in parser
#define yylex scanner->yylex


#line 71 "flang_parser.tab.cc" // lalr1.cc:408


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

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


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

#line 6 "flang_parser.y" // lalr1.cc:474
namespace flang {
#line 157 "flang_parser.tab.cc" // lalr1.cc:474

  /// Build a parser object.
  FlangParser::FlangParser (FlangScanner* scanner_yyarg, SyntaxTree* syntax_tree_yyarg, std::string* filename_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      scanner (scanner_yyarg),
      syntax_tree (syntax_tree_yyarg),
      filename (filename_yyarg)
  {}

  FlangParser::~FlangParser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  FlangParser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
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
    , location (other.location)
  {
    value = other.value;
  }


  template <typename Base>
  inline
  FlangParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  FlangParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
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
    location = s.location;
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
    : super_type (s, that.location)
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
    location = that.location;
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
    switch (yysym.type_get ())
    {
            case 6: // STR_VAL

#line 93 "flang_parser.y" // lalr1.cc:599
        { delete ((yysym.value.str_val)); }
#line 340 "flang_parser.tab.cc" // lalr1.cc:599
        break;

      case 7: // ID

#line 93 "flang_parser.y" // lalr1.cc:599
        { delete ((yysym.value.str_val)); }
#line 347 "flang_parser.tab.cc" // lalr1.cc:599
        break;


      default:
        break;
    }
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
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
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

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    // User initialization code.
    #line 22 "flang_parser.y" // lalr1.cc:725
{
  yyla.location.begin.filename = yyla.location.end.filename = filename;
}

#line 483 "flang_parser.tab.cc" // lalr1.cc:725

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
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location));
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

      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 144 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.program_node) = new ProgramNode();
  (yylhs.value.program_node)->setLocation(yylhs.location);
  (yylhs.value.program_node)->setImportList((yystack_[1].value.import_list_node));
  (yylhs.value.program_node)->setStmtList((yystack_[0].value.stmt_list_node));
  syntax_tree->setRoot((yylhs.value.program_node));
}
#line 603 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 3:
#line 152 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.import_list_node) = (yystack_[1].value.import_list_node);
  (yylhs.value.import_list_node)->setLocation(yylhs.location);
  (yylhs.value.import_list_node)->addImport((yystack_[0].value.import_node));
}
#line 613 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 4:
#line 156 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.import_list_node) = new ImportListNode();
  (yylhs.value.import_list_node)->setLocation(yylhs.location);
}
#line 622 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 5:
#line 161 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.import_node) = new ImportNode();
  (yylhs.value.import_node)->setLocation(yylhs.location);
  (yylhs.value.import_node)->setPackageName((yystack_[0].value.name_node));
}
#line 632 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 6:
#line 165 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.import_node) = new ImportNode();
  (yylhs.value.import_node)->setLocation(yylhs.location);
  (yylhs.value.import_node)->setPackageName((yystack_[2].value.name_node));
  (yylhs.value.import_node)->setAlias((yystack_[0].value.simple_name_node));
}
#line 643 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 7:
#line 172 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.stmt_list_node) = (yystack_[1].value.stmt_list_node);
  (yylhs.value.stmt_list_node)->setLocation(yylhs.location);
  (yylhs.value.stmt_list_node)->addStatement((yystack_[0].value.stmt_node));
}
#line 653 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 8:
#line 176 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.stmt_list_node) = new StmtListNode();
  (yylhs.value.stmt_list_node)->setLocation(yylhs.location);
}
#line 662 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 9:
#line 181 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.stmt_node) = (yystack_[1].value.exp_node);
  (yylhs.value.stmt_node)->setLocation(yylhs.location);
}
#line 671 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 10:
#line 184 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.stmt_node) = new PrintNode((yystack_[1].value.exp_node));
  (yylhs.value.stmt_node)->setLocation(yylhs.location);
}
#line 680 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 11:
#line 187 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.stmt_node) = (yystack_[0].value.return_node);
  (yylhs.value.stmt_node)->setLocation(yylhs.location);
}
#line 689 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 12:
#line 190 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.stmt_node) = new BreakNode();
  (yylhs.value.stmt_node)->setLocation(yylhs.location);
}
#line 698 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 13:
#line 193 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.stmt_node) = new ContinueNode();
  (yylhs.value.stmt_node)->setLocation(yylhs.location);
}
#line 707 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 14:
#line 196 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.stmt_node) = (yystack_[1].value.var_decl_node);
  (yylhs.value.stmt_node)->setLocation(yylhs.location);
}
#line 716 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 15:
#line 199 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.stmt_node) = (yystack_[0].value.if_node);
  (yylhs.value.stmt_node)->setLocation(yylhs.location);
}
#line 725 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 16:
#line 202 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.stmt_node) = (yystack_[0].value.while_node);
  (yylhs.value.stmt_node)->setLocation(yylhs.location);
}
#line 734 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 17:
#line 205 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.stmt_node) = (yystack_[1].value.assign_node);
  (yylhs.value.stmt_node)->setLocation(yylhs.location);
}
#line 743 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 18:
#line 208 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.stmt_node) = (yystack_[0].value.func_node);
  (yylhs.value.stmt_node)->setLocation(yylhs.location);
}
#line 752 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 19:
#line 211 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.stmt_node) = (yystack_[0].value.class_node);
  (yylhs.value.stmt_node)->setLocation(yylhs.location);
}
#line 761 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 20:
#line 214 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.stmt_node) = (yystack_[0].value.block_node);
  (yylhs.value.stmt_node)->setLocation(yylhs.location);
}
#line 770 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 21:
#line 217 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.stmt_node) = new EmptyStmtNode();
  (yylhs.value.stmt_node)->setLocation(yylhs.location);
}
#line 779 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 22:
#line 222 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.return_node)= new ReturnNode();
  (yylhs.value.return_node)->setLocation(yylhs.location);
}
#line 788 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 23:
#line 225 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.return_node) = new ReturnNode((yystack_[1].value.exp_node));
  (yylhs.value.return_node)->setLocation(yylhs.location);
}
#line 797 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 24:
#line 230 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.block_node) = new BlockNode();
  (yylhs.value.block_node)->setStmtList((yystack_[1].value.stmt_list_node));
}
#line 806 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 25:
#line 235 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.exp_node) = new IntValNode((yystack_[0].value.int_val));
  (yylhs.value.exp_node)->setLocation(yylhs.location);
}
#line 815 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 26:
#line 238 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.exp_node) = new BoolValNode(true);
  (yylhs.value.exp_node)->setLocation(yylhs.location);
}
#line 824 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 27:
#line 241 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.exp_node) = new BoolValNode(false);
  (yylhs.value.exp_node)->setLocation(yylhs.location);
}
#line 833 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 28:
#line 244 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.exp_node) = new StringValNode(*((yystack_[0].value.str_val)));
  (yylhs.value.exp_node)->setLocation(yylhs.location);
}
#line 842 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 29:
#line 247 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.exp_node) = new CharValNode((yystack_[0].value.char_val));
  (yylhs.value.exp_node)->setLocation(yylhs.location);
}
#line 851 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 30:
#line 250 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.exp_node) = new DoubleValNode((yystack_[0].value.double_val));
  (yylhs.value.exp_node)->setLocation(yylhs.location);
}
#line 860 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 31:
#line 253 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.exp_node) = new BinaryExpNode(BinaryExpNode::OP_ADD, (yystack_[2].value.exp_node), (yystack_[0].value.exp_node));
  (yylhs.value.exp_node)->setLocation(yylhs.location);
}
#line 869 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 32:
#line 256 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.exp_node) = new BinaryExpNode(BinaryExpNode::OP_SUB, (yystack_[2].value.exp_node), (yystack_[0].value.exp_node));
  (yylhs.value.exp_node)->setLocation(yylhs.location);
}
#line 878 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 33:
#line 259 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.exp_node) = new BinaryExpNode(BinaryExpNode::OP_MUL, (yystack_[2].value.exp_node), (yystack_[0].value.exp_node));
  (yylhs.value.exp_node)->setLocation(yylhs.location);
}
#line 887 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 34:
#line 262 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.exp_node) = new BinaryExpNode(BinaryExpNode::OP_DIV, (yystack_[2].value.exp_node), (yystack_[0].value.exp_node));
  (yylhs.value.exp_node)->setLocation(yylhs.location);
}
#line 896 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 35:
#line 265 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.exp_node) = new BinaryExpNode(BinaryExpNode::OP_LT, (yystack_[2].value.exp_node), (yystack_[0].value.exp_node));
  (yylhs.value.exp_node)->setLocation(yylhs.location);
}
#line 905 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 36:
#line 268 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.exp_node) = new BinaryExpNode(BinaryExpNode::OP_AND, (yystack_[2].value.exp_node), (yystack_[0].value.exp_node));
  (yylhs.value.exp_node)->setLocation(yylhs.location);
}
#line 914 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 37:
#line 271 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.exp_node) = new BinaryExpNode(BinaryExpNode::OP_EQ, (yystack_[2].value.exp_node), (yystack_[0].value.exp_node));
  (yylhs.value.exp_node)->setLocation(yylhs.location);
}
#line 923 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 38:
#line 274 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.exp_node) = (yystack_[1].value.exp_node);
  (yylhs.value.exp_node)->setLocation(yylhs.location);
}
#line 932 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 39:
#line 277 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.exp_node) = new NewNode((yystack_[0].value.call_node));
  (yylhs.value.exp_node)->setLocation(yylhs.location);
}
#line 941 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 40:
#line 280 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.exp_node) = (yystack_[0].value.field_access_node);
  (yylhs.value.exp_node)->setLocation(yylhs.location);
}
#line 950 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 41:
#line 289 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.name_node) = (yystack_[0].value.simple_name_node);
  (yylhs.value.name_node)->setLocation(yylhs.location);
}
#line 959 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 42:
#line 292 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.name_node) = (yystack_[0].value.qualified_name_node);
  (yylhs.value.name_node)->setLocation(yylhs.location);
}
#line 968 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 43:
#line 297 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.qualified_name_node) = (yystack_[2].value.qualified_name_node);
  (yylhs.value.qualified_name_node)->setLocation(yylhs.location);
  (yylhs.value.qualified_name_node)->addSimpleName((yystack_[0].value.simple_name_node));
}
#line 978 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 44:
#line 301 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.qualified_name_node) = new QualifiedNameNode();
  (yylhs.value.qualified_name_node)->setLocation(yylhs.location);
  (yylhs.value.qualified_name_node)->addSimpleName((yystack_[2].value.simple_name_node));
  (yylhs.value.qualified_name_node)->addSimpleName((yystack_[0].value.simple_name_node));
}
#line 989 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 45:
#line 308 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.simple_name_node) = new SimpleNameNode(*(yystack_[0].value.str_val));
  (yylhs.value.simple_name_node)->setLocation(yylhs.location);
}
#line 998 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 46:
#line 313 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.field_access_node) = new FieldAccessNode();
  (yylhs.value.field_access_node)->setLocation(yylhs.location);
  (yylhs.value.field_access_node)->setExpression((yystack_[2].value.exp_node));
  (yylhs.value.field_access_node)->setFieldName((yystack_[0].value.simple_name_node));
}
#line 1009 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 47:
#line 318 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.field_access_node) = new FieldAccessNode();
  (yylhs.value.field_access_node)->setLocation(yylhs.location);
  (yylhs.value.field_access_node)->setFieldName((yystack_[0].value.simple_name_node));
}
#line 1019 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 48:
#line 324 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.var_decl_node) = (yystack_[2].value.var_decl_node);
  (yylhs.value.var_decl_node)->setLocation(yylhs.location);
  (yylhs.value.var_decl_node)->addVarDeclFragment((yystack_[0].value.var_decl_fragment_node));
}
#line 1029 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 49:
#line 328 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.var_decl_node) = new VarDeclNode();
  (yylhs.value.var_decl_node)->setLocation(yylhs.location);
  (yylhs.value.var_decl_node)->setDataType((yystack_[1].value.type_node));
  (yylhs.value.var_decl_node)->addVarDeclFragment((yystack_[0].value.var_decl_fragment_node));
}
#line 1040 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 50:
#line 335 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.var_decl_fragment_node) = new VarDeclFragmentNode(*(yystack_[2].value.str_val), (yystack_[0].value.exp_node));
  (yylhs.value.var_decl_fragment_node)->setLocation(yylhs.location);
}
#line 1049 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 51:
#line 338 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.var_decl_fragment_node) = new VarDeclFragmentNode(*(yystack_[0].value.str_val), nullptr);
  (yylhs.value.var_decl_fragment_node)->setLocation(yylhs.location);
}
#line 1058 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 52:
#line 343 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.assign_node) = new AssignNode((yystack_[2].value.exp_node), (yystack_[0].value.exp_node));
  (yylhs.value.assign_node)->setLocation(yylhs.location);
}
#line 1067 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 53:
#line 348 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.type_node) = new Int32TypeNode();
  (yylhs.value.type_node)->setLocation(yylhs.location);
}
#line 1076 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 54:
#line 351 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.type_node) = new Int64TypeNode();
  (yylhs.value.type_node)->setLocation(yylhs.location);
}
#line 1085 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 55:
#line 354 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.type_node) = new BoolTypeNode();
  (yylhs.value.type_node)->setLocation(yylhs.location);
}
#line 1094 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 56:
#line 357 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.type_node) = new CharTypeNode();
  (yylhs.value.type_node)->setLocation(yylhs.location);
}
#line 1103 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 57:
#line 360 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.type_node) = new StringTypeNode();
  (yylhs.value.type_node)->setLocation(yylhs.location);
}
#line 1112 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 58:
#line 363 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.type_node) = new DoubleTypeNode();
  (yylhs.value.type_node)->setLocation(yylhs.location);
}
#line 1121 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 59:
#line 366 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.type_node) = (yystack_[0].value.user_def_type_node);
  (yylhs.value.type_node)->setLocation(yylhs.location);
}
#line 1130 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 60:
#line 371 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.user_def_type_node) = new UserDefTypeNode();
  (yylhs.value.user_def_type_node)->setLocation(yylhs.location);
  std::unique_ptr<FieldAccessNode> field_access((yystack_[0].value.field_access_node));
  (yylhs.value.user_def_type_node)->setName(field_access->toNameNode());
}
#line 1141 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 61:
#line 384 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.if_node) = new IfNode((yystack_[4].value.exp_node), (yystack_[2].value.stmt_node), (yystack_[0].value.stmt_node));
  (yylhs.value.if_node)->setLocation(yylhs.location);
}
#line 1150 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 62:
#line 387 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.if_node) = new IfNode((yystack_[2].value.exp_node), (yystack_[0].value.stmt_node), nullptr);
  (yylhs.value.if_node)->setLocation(yylhs.location);
}
#line 1159 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 63:
#line 392 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.while_node) = new WhileNode((yystack_[2].value.exp_node), (yystack_[0].value.stmt_node));
  (yylhs.value.while_node)->setLocation(yylhs.location);
}
#line 1168 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 64:
#line 397 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.func_node) = new FuncNode();
  (yylhs.value.func_node)->setLocation(yylhs.location);
  (yylhs.value.func_node)->setName(*((yystack_[5].value.str_val)));
  (yylhs.value.func_node)->setParamDeclList((yystack_[3].value.param_decl_list_node));
  (yylhs.value.func_node)->setReturnType((yystack_[1].value.type_node));
  (yylhs.value.func_node)->setBody((yystack_[0].value.block_node));
}
#line 1181 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 65:
#line 404 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.func_node) = new FuncNode();
  (yylhs.value.func_node)->setLocation(yylhs.location);
  (yylhs.value.func_node)->setBody((yystack_[0].value.block_node));
  (yylhs.value.func_node)->setName(*(yystack_[4].value.str_val));
  (yylhs.value.func_node)->setReturnType((yystack_[1].value.type_node));
}
#line 1193 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 66:
#line 412 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.type_node) = (yystack_[0].value.type_node);
  (yylhs.value.type_node)->setLocation(yylhs.location);
}
#line 1202 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 67:
#line 415 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.type_node) = new VoidTypeNode();
  (yylhs.value.type_node)->setLocation(yylhs.location);
}
#line 1211 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 68:
#line 420 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.param_decl_list_node) = (yystack_[3].value.param_decl_list_node);
  (yylhs.value.param_decl_list_node)->setLocation(yylhs.location);
  VarDeclNode* var_decl_node = new VarDeclNode();
  VarDeclFragmentNode* var_decl_fragment_node = new
      VarDeclFragmentNode(*((yystack_[0].value.str_val)), nullptr);
  var_decl_node->setDataType((yystack_[1].value.type_node));
  var_decl_node->addVarDeclFragment(var_decl_fragment_node);
  (yylhs.value.param_decl_list_node)->addDeclaration(var_decl_node);
}
#line 1226 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 69:
#line 429 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.param_decl_list_node) = new ParamDeclListNode();
  (yylhs.value.param_decl_list_node)->setLocation(yylhs.location);
  VarDeclNode* var_decl_node = new VarDeclNode();
  VarDeclFragmentNode* var_decl_fragment_node = new
      VarDeclFragmentNode(*((yystack_[0].value.str_val)), nullptr);
  var_decl_node->setDataType((yystack_[1].value.type_node));
  var_decl_node->addVarDeclFragment(var_decl_fragment_node);
  (yylhs.value.param_decl_list_node)->addDeclaration(var_decl_node);
}
#line 1241 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 70:
#line 440 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.call_node) = new CallNode();
  (yylhs.value.call_node)->setLocation(yylhs.location);
  (yylhs.value.call_node)->setCaller((yystack_[5].value.exp_node));
  (yylhs.value.call_node)->setName((yystack_[3].value.simple_name_node));
  (yylhs.value.call_node)->setParamList((yystack_[1].value.param_list_node));
}
#line 1253 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 71:
#line 446 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.call_node) = new CallNode();
  (yylhs.value.call_node)->setLocation(yylhs.location);
  (yylhs.value.call_node)->setName((yystack_[3].value.simple_name_node));
  (yylhs.value.call_node)->setParamList((yystack_[1].value.param_list_node));
}
#line 1264 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 72:
#line 453 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.param_list_node) = (yystack_[2].value.param_list_node);
  (yylhs.value.param_list_node)->setLocation(yylhs.location);
  (yylhs.value.param_list_node)->addParameter((yystack_[0].value.exp_node));
}
#line 1274 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 73:
#line 457 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.param_list_node) = new ParamListNode();
  (yylhs.value.param_list_node)->setLocation(yylhs.location);
}
#line 1283 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 74:
#line 462 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.class_node) = new ClassNode();
  (yylhs.value.class_node)->setLocation(yylhs.location);
  (yylhs.value.class_node)->setName(*((yystack_[3].value.str_val)));
  (yylhs.value.class_node)->setBody((yystack_[1].value.class_body_node));
}
#line 1294 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 75:
#line 467 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.class_node) = new ClassNode();
  (yylhs.value.class_node)->setLocation(yylhs.location);
  (yylhs.value.class_node)->setSuperClass((yystack_[3].value.name_node));
  (yylhs.value.class_node)->setName(*((yystack_[5].value.str_val)));
  (yylhs.value.class_node)->setBody((yystack_[1].value.class_body_node));
}
#line 1306 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 76:
#line 475 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.class_body_node) = (yystack_[1].value.class_body_node);
  (yylhs.value.class_body_node)->setLocation(yylhs.location);
  (yylhs.value.class_body_node)->addDeclaration((yystack_[0].value.stmt_node));
}
#line 1316 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 77:
#line 479 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.class_body_node) = new ClassBodyNode();
  (yylhs.value.class_body_node)->setLocation(yylhs.location);
}
#line 1325 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 78:
#line 484 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.stmt_node) = (yystack_[1].value.var_decl_node);
  (yylhs.value.stmt_node)->setLocation(yylhs.location);
}
#line 1334 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 79:
#line 487 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.stmt_node) = (yystack_[0].value.func_node);
  (yylhs.value.stmt_node)->setLocation(yylhs.location);
}
#line 1343 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 80:
#line 490 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.stmt_node) = (yystack_[0].value.class_node);
  (yylhs.value.stmt_node)->setLocation(yylhs.location);
}
#line 1352 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 81:
#line 493 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.stmt_node) = (yystack_[0].value.constructor_node);
  (yylhs.value.stmt_node)->setLocation(yylhs.location);
}
#line 1361 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 82:
#line 496 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.stmt_node) = (yystack_[0].value.destructor_node);
  (yylhs.value.stmt_node)->setLocation(yylhs.location);
}
#line 1370 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 83:
#line 501 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.constructor_node) = new ConstructorNode();
  (yylhs.value.constructor_node)->setLocation(yylhs.location);
  (yylhs.value.constructor_node)->setParamDeclList((yystack_[2].value.param_decl_list_node));
  (yylhs.value.constructor_node)->setBody((yystack_[0].value.block_node));
}
#line 1381 "flang_parser.tab.cc" // lalr1.cc:847
    break;

  case 84:
#line 508 "flang_parser.y" // lalr1.cc:847
    {
  (yylhs.value.destructor_node) = new DestructorNode();
  (yylhs.value.destructor_node)->setLocation(yylhs.location);
  (yylhs.value.destructor_node)->setBody((yystack_[0].value.block_node));
}
#line 1391 "flang_parser.tab.cc" // lalr1.cc:847
    break;


#line 1395 "flang_parser.tab.cc" // lalr1.cc:847
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
        error (yyla.location, yysyntax_error_ (yystack_[0].state,
                                           yyempty ? yyempty_ : yyla.type_get ()));
      }


    yyerror_range[1].location = yyla.location;
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
    yyerror_range[1].location = yystack_[yylen - 1].location;
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

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

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
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  FlangParser::yysyntax_error_ (state_type, symbol_number_type) const
  {
    return YY_("syntax error");
  }


  const signed char FlangParser::yypact_ninf_ = -118;

  const signed char FlangParser::yytable_ninf_ = -61;

  const short int
  FlangParser::yypact_[] =
  {
    -118,    30,   -22,  -118,    25,  -118,   311,  -118,    12,   -10,
       0,  -118,  -118,  -118,  -118,    19,    29,    88,    33,    43,
      74,     4,    88,    46,  -118,  -118,  -118,  -118,  -118,  -118,
    -118,  -118,  -118,  -118,    88,  -118,  -118,  -118,   259,  -118,
      -5,   -33,    50,    83,  -118,  -118,  -118,  -118,  -118,    25,
      25,    25,    88,    88,   338,  -118,  -118,    48,   -31,  -118,
     355,   369,    49,  -118,  -118,   263,    82,    88,    88,    88,
      88,    88,    88,    88,    88,    25,  -118,  -118,    83,  -118,
      69,  -118,  -118,  -118,  -118,   136,   209,  -118,   214,  -118,
      25,  -118,    25,  -118,  -118,  -118,   382,    44,   166,    87,
       5,     5,    64,    64,  -118,  -118,    88,   311,   311,   343,
     382,   108,     1,   139,    71,    70,     6,   382,  -118,   104,
    -118,    89,  -118,   343,   343,    85,  -118,   128,   -21,  -118,
    -118,  -118,  -118,  -118,  -118,  -118,  -118,    88,   311,  -118,
      89,   141,   343,    99,  -118,   178,    10,   382,  -118,  -118,
    -118,    15,   100,  -118,  -118,    89,    89,  -118,  -118
  };

  const unsigned char
  FlangParser::yydefact_[] =
  {
       4,     0,     8,     1,     0,     3,     2,    45,     5,    42,
      41,    25,    29,    28,    30,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    55,    56,    57,    53,    54,    26,
      27,    58,    21,     8,     0,     7,    11,    20,     0,    47,
      40,     0,     0,     0,    59,    15,    16,    18,    19,     0,
       0,     0,     0,     0,     0,    40,    12,     0,     0,    22,
       0,     0,    47,    39,    13,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     9,    14,     0,    17,
      51,    49,     6,    43,    44,     0,     0,    10,     0,    77,
       0,    23,     0,    73,    24,    38,    52,    36,    37,    35,
      31,    32,    33,    34,    46,    48,     0,     0,     0,    67,
       0,     0,     0,     0,     0,    46,     0,    50,    63,    62,
      66,     0,    69,    67,     0,     0,    74,     0,     0,    79,
      80,    76,    81,    82,    77,    73,    71,     0,     0,    65,
       0,     0,     0,     0,    78,     0,     0,    72,    61,    64,
      68,     0,     0,    75,    70,     0,     0,    83,    84
  };

  const signed char
  FlangParser::yypgoto_[] =
  {
    -118,  -118,  -118,  -118,   117,   -92,  -118,  -117,     3,    67,
    -118,    14,    -6,  -112,    76,  -118,   -82,  -118,  -118,  -118,
    -110,    51,    24,  -118,    32,  -100,    35,  -118,  -118,  -118
  };

  const short int
  FlangParser::yydefgoto_[] =
  {
      -1,     1,     2,     5,     6,    35,    36,    37,   110,     8,
       9,    39,    55,    41,    81,    42,    43,    44,    45,    46,
      47,   121,   112,    63,   116,    48,   113,   131,   132,   133
  };

  const short int
  FlangParser::yytable_[] =
  {
      40,   128,   -60,   129,   139,     4,   111,    11,    12,    38,
      13,     7,    14,   130,    77,   118,   119,    89,    10,    78,
      54,    22,    90,   149,    60,    61,   144,   120,    29,    30,
       3,    78,     7,   128,    50,   129,    62,    66,   157,   158,
      49,   120,   141,   -60,    51,   130,   148,    73,    74,    75,
      57,    59,   123,   124,    34,    85,    86,   136,   137,    40,
     111,   154,   137,    82,    83,    84,   155,   124,    38,    52,
      96,    97,    98,    99,   100,   101,   102,   103,    69,    53,
      56,    58,    40,    70,    71,    72,    73,    74,    75,   104,
      80,    11,    12,    64,    13,     7,    14,    79,    88,    93,
     106,    40,    40,    40,    10,    22,   115,    40,    75,   117,
      38,    38,    29,    30,    68,   122,    69,    40,    40,   134,
     135,    70,    71,    72,    73,    74,    75,    71,    72,    73,
      74,    75,    40,    95,   138,   142,    40,    33,    34,    40,
     147,    38,    11,    12,   143,    13,     7,    14,   150,   152,
      65,   156,    19,    20,   105,   125,    22,   114,    24,    25,
      26,    27,    28,    29,    30,    31,   151,   146,    68,   145,
      69,     0,     0,     0,   140,    70,    71,    72,    73,    74,
      75,    11,    12,     0,    13,     7,    14,   107,   126,    34,
       0,    19,    20,   127,   125,    22,     0,    24,    25,    26,
      27,    28,    29,    30,    31,    70,    71,    72,    73,    74,
      75,     0,     0,     0,     0,     0,     0,    11,    12,     0,
      13,     7,    14,     0,     0,     0,     0,   153,    34,     0,
       0,    22,   127,    24,    25,    26,    27,    28,    29,    30,
      31,    68,     0,    69,     0,     0,     0,     0,    70,    71,
      72,    73,    74,    75,     0,     0,     0,     0,     0,     0,
     108,     0,     0,     0,    34,   109,    11,    12,     0,    13,
       7,    14,    15,    16,    17,    18,    19,    20,    21,     0,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      67,    68,     0,    69,     0,     0,     0,     0,    70,    71,
      72,    73,    74,    75,     0,     0,    76,     0,     0,     0,
      32,    33,    94,    34,    11,    12,     0,    13,     7,    14,
      15,    16,    17,    18,    19,    20,    21,     0,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,     0,     0,
       0,     0,     0,     0,     0,     0,    11,    12,     0,    13,
       7,    14,     0,     0,     0,     0,     0,     0,    32,    33,
      22,    34,    24,    25,    26,    27,    28,    29,    30,    31,
      68,     0,    69,     0,     0,     0,     0,    70,    71,    72,
      73,    74,    75,     0,     0,    87,     0,    68,     0,    69,
       0,     0,     0,    34,    70,    71,    72,    73,    74,    75,
       0,    68,    91,    69,     0,     0,     0,     0,    70,    71,
      72,    73,    74,    92,    68,     0,    69,     0,     0,     0,
       0,    70,    71,    72,    73,    74,    75
  };

  const short int
  FlangParser::yycheck_[] =
  {
       6,   113,     7,   113,   121,    27,    88,     3,     4,     6,
       6,     7,     8,   113,    47,   107,   108,    48,     4,    52,
      17,    17,    53,   140,    21,    22,    47,   109,    24,    25,
       0,    52,     7,   145,    44,   145,    22,    34,   155,   156,
      28,   123,   124,    48,    44,   145,   138,    42,    43,    44,
       7,    47,    51,    52,    50,    52,    53,    51,    52,    65,
     142,    51,    52,    49,    50,    51,    51,    52,    65,    50,
      67,    68,    69,    70,    71,    72,    73,    74,    34,    50,
      47,     7,    88,    39,    40,    41,    42,    43,    44,    75,
       7,     3,     4,    47,     6,     7,     8,    47,    50,    50,
      31,   107,   108,   109,    90,    17,    92,   113,    44,   106,
     107,   108,    24,    25,    32,     7,    34,   123,   124,    48,
      50,    39,    40,    41,    42,    43,    44,    40,    41,    42,
      43,    44,   138,    51,    30,    50,   142,    48,    50,   145,
     137,   138,     3,     4,    16,     6,     7,     8,     7,    50,
      33,    51,    13,    14,    78,    16,    17,    90,    19,    20,
      21,    22,    23,    24,    25,    26,   142,   135,    32,   134,
      34,    -1,    -1,    -1,   123,    39,    40,    41,    42,    43,
      44,     3,     4,    -1,     6,     7,     8,    51,    49,    50,
      -1,    13,    14,    54,    16,    17,    -1,    19,    20,    21,
      22,    23,    24,    25,    26,    39,    40,    41,    42,    43,
      44,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,    -1,
       6,     7,     8,    -1,    -1,    -1,    -1,    49,    50,    -1,
      -1,    17,    54,    19,    20,    21,    22,    23,    24,    25,
      26,    32,    -1,    34,    -1,    -1,    -1,    -1,    39,    40,
      41,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,
      51,    -1,    -1,    -1,    50,    51,     3,     4,    -1,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      31,    32,    -1,    34,    -1,    -1,    -1,    -1,    39,    40,
      41,    42,    43,    44,    -1,    -1,    47,    -1,    -1,    -1,
      47,    48,    49,    50,     3,     4,    -1,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,    -1,     6,
       7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,
      17,    50,    19,    20,    21,    22,    23,    24,    25,    26,
      32,    -1,    34,    -1,    -1,    -1,    -1,    39,    40,    41,
      42,    43,    44,    -1,    -1,    47,    -1,    32,    -1,    34,
      -1,    -1,    -1,    50,    39,    40,    41,    42,    43,    44,
      -1,    32,    47,    34,    -1,    -1,    -1,    -1,    39,    40,
      41,    42,    43,    44,    32,    -1,    34,    -1,    -1,    -1,
      -1,    39,    40,    41,    42,    43,    44
  };

  const unsigned char
  FlangParser::yystos_[] =
  {
       0,    56,    57,     0,    27,    58,    59,     7,    64,    65,
      66,     3,     4,     6,     8,     9,    10,    11,    12,    13,
      14,    15,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    47,    48,    50,    60,    61,    62,    63,    66,
      67,    68,    70,    71,    72,    73,    74,    75,    80,    28,
      44,    44,    50,    50,    63,    67,    47,     7,     7,    47,
      63,    63,    66,    78,    47,    59,    63,    31,    32,    34,
      39,    40,    41,    42,    43,    44,    47,    47,    52,    47,
       7,    69,    66,    66,    66,    63,    63,    47,    50,    48,
      53,    47,    44,    50,    49,    51,    63,    63,    63,    63,
      63,    63,    63,    63,    66,    69,    31,    51,    51,    51,
      63,    71,    77,    81,    64,    66,    79,    63,    60,    60,
      71,    76,     7,    51,    52,    16,    49,    54,    68,    75,
      80,    82,    83,    84,    48,    50,    51,    52,    30,    62,
      76,    71,    50,    16,    47,    81,    79,    63,    60,    62,
       7,    77,    50,    49,    51,    51,    51,    62,    62
  };

  const unsigned char
  FlangParser::yyr1_[] =
  {
       0,    55,    56,    57,    57,    58,    58,    59,    59,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    61,    61,    62,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    64,    64,    65,    65,    66,    67,    67,    68,    68,
      69,    69,    70,    71,    71,    71,    71,    71,    71,    71,
      72,    73,    73,    74,    75,    75,    76,    76,    77,    77,
      78,    78,    79,    79,    80,    80,    81,    81,    82,    82,
      82,    82,    82,    83,    84
  };

  const unsigned char
  FlangParser::yyr2_[] =
  {
       0,     2,     2,     2,     0,     2,     4,     2,     0,     2,
       3,     1,     2,     2,     2,     1,     1,     2,     1,     1,
       1,     1,     2,     3,     3,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       1,     1,     1,     3,     3,     1,     3,     1,     3,     2,
       3,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     7,     5,     5,     7,     6,     1,     0,     4,     2,
       6,     4,     3,     0,     5,     7,     2,     0,     2,     1,
       1,     1,     1,     5,     5
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const FlangParser::yytname_[] =
  {
  "$end", "error", "$undefined", "INT_VAL", "CHAR_VAL", "BOOL_VAL",
  "STR_VAL", "ID", "DOUBLE_VAL", "WHILE", "IF", "PRINT", "BREAK", "DEF",
  "CLASS", "RETURN", "THIS", "NEW", "CONTINUE", "BOOL_TYPE", "CHAR_TYPE",
  "STR_TYPE", "INT32_TYPE", "INT64_TYPE", "TRUE", "FALSE", "DOUBLE_TYPE",
  "IMPORT", "AS", "IFX", "ELSE", "'='", "AND", "OR", "EQ", "NE", "GE",
  "LE", "'>'", "'<'", "'+'", "'-'", "'*'", "'/'", "'.'", "'!'", "UMINUS",
  "';'", "'{'", "'}'", "'('", "')'", "','", "':'", "'~'", "$accept",
  "program", "import_list", "import", "stmt_list", "stmt", "return_stmt",
  "block", "expr", "name", "qualified_name", "simple_name", "field_access",
  "var_decl", "var_decl_fragment", "assignment", "type", "user_def_type",
  "if_stmt", "while_stmt", "function", "ret_type", "param_decl_list",
  "call", "param_list", "class", "class_body", "class_body_decl",
  "constructor", "destructor", YY_NULLPTR
  };


  const unsigned short int
  FlangParser::yyrline_[] =
  {
       0,   144,   144,   152,   156,   161,   165,   172,   176,   181,
     184,   187,   190,   193,   196,   199,   202,   205,   208,   211,
     214,   217,   222,   225,   230,   235,   238,   241,   244,   247,
     250,   253,   256,   259,   262,   265,   268,   271,   274,   277,
     280,   289,   292,   297,   301,   308,   313,   318,   324,   328,
     335,   338,   343,   348,   351,   354,   357,   360,   363,   366,
     371,   384,   387,   392,   397,   404,   412,   415,   420,   429,
     440,   446,   453,   457,   462,   467,   475,   479,   484,   487,
     490,   493,   496,   501,   508
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
       2,     2,     2,    45,     2,     2,     2,     2,     2,     2,
      50,    51,    42,    40,    52,    41,    44,    43,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    53,    47,
      39,    31,    38,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    48,     2,    49,    54,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    32,    33,    34,    35,
      36,    37,    46
    };
    const unsigned int user_token_number_max_ = 292;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

#line 6 "flang_parser.y" // lalr1.cc:1155
} // flang
#line 1888 "flang_parser.tab.cc" // lalr1.cc:1155
#line 514 "flang_parser.y" // lalr1.cc:1156


void flang::FlangParser::error(const flang::FlangParser::location_type& loc,
                               const std::string& msg) {
  Error err(loc);
  err.setMessage(msg);
  log4cxx::LoggerPtr logger(
      log4cxx::Logger::getLogger("flang.FlangParser"));
  LOG4CXX_ERROR(logger, err.getMessage());
}
