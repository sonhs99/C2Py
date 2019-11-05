/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "yacc.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include <ParseTree.h>

extern int yylex();
extern int yylineno;
int yyerror(struct TreeNode ** pt, char const *str) { return 0; };

#line 76 "yacc.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "yacc.tab.h".  */
#ifndef YY_YY_YACC_TAB_H_INCLUDED
# define YY_YY_YACC_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
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
    IDENT = 259,
    ASS = 260,
    EQUAL = 261,
    NOTEQU = 262,
    GREATER = 263,
    EQUGRE = 264,
    LESS = 265,
    EQULESS = 266,
    IN = 267,
    ADD = 268,
    SUB = 269,
    MUL = 270,
    DIV = 271,
    UMINUS = 272,
    UPLUS = 273,
    NOT = 274,
    LPAREN = 275,
    RPAREN = 276,
    LBRACKET = 277,
    RBRACKET = 278,
    COMMA = 279,
    SEMICOLON = 280,
    COLON = 281,
    MAINPROG = 282,
    FUNCTION = 283,
    PROCEDURE = 284,
    BEG = 285,
    END = 286,
    IF = 287,
    ELIF = 288,
    ELSE = 289,
    NOP = 290,
    WHILE = 291,
    RETURN = 292,
    FOR = 293,
    INT = 294,
    FLOAT = 295
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 13 "yacc.y" /* yacc.c:355  */

    char * data;
	struct TreeNode * node;

#line 162 "yacc.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (struct TreeNode ** pt);

#endif /* !YY_YY_YACC_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 179 "yacc.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   474

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  103
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  190

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   295

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    41,    41,    47,    54,    61,    71,    75,    80,    83,
      84,    87,    88,    89,    95,    96,   100,   107,   108,   111,
     112,   115,   121,   125,   130,   134,   141,   142,   146,   149,
     150,   154,   158,   164,   167,   173,   174,   177,   178,   179,
     180,   181,   182,   186,   187,   188,   191,   196,   204,   208,
     209,   216,   217,   218,   224,   228,   235,   241,   250,   251,
     252,   258,   259,   265,   266,   269,   270,   271,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   296,   299,   302,   305,   308,
     311,   314,   317,   320,   323,   326,   329,   332,   335,   340,
     341,   342,   343,   344
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "IDENT", "ASS", "EQUAL",
  "NOTEQU", "GREATER", "EQUGRE", "LESS", "EQULESS", "IN", "ADD", "SUB",
  "MUL", "DIV", "UMINUS", "UPLUS", "NOT", "\"(\"", "\")\"", "\"[\"",
  "\"]\"", "\",\"", "\";\"", "\":\"", "MAINPROG", "FUNCTION", "PROCEDURE",
  "BEG", "END", "IF", "ELIF", "ELSE", "NOP", "WHILE", "RETURN", "FOR",
  "INT", "FLOAT", "$accept", "program", "declarations", "identifier_list",
  "init", "type", "standard_type", "subprograms", "subprogram",
  "subprogram_head", "args", "params", "block", "stmts", "stmt",
  "stmt_semi", "if", "elif", "else", "while", "for", "variable",
  "procedure", "expr_list", "exprs", "expr", "term", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295
};
# endif

#define YYPACT_NINF -146

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-146)))

#define YYTABLE_NINF -81

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      25,    18,    13,    68,     3,  -146,   -32,  -146,  -146,    62,
      91,    97,   -32,   -32,    62,    85,  -146,    62,   104,   133,
      22,   136,    62,    62,  -146,   121,   121,  -146,   -32,  -146,
      84,   118,   -32,   -32,     4,  -146,  -146,    91,   130,   131,
      64,  -146,  -146,    -2,   261,   269,   283,   419,  -146,  -146,
     435,  -146,    91,  -146,  -146,  -146,  -146,    10,     5,   -32,
     -32,   419,  -146,   419,   419,   419,  -146,     1,    64,    23,
    -146,  -146,  -146,   435,   419,   419,  -146,  -146,  -146,  -146,
    -146,  -146,   245,   291,   305,   313,   327,   335,   349,   357,
     371,   379,   393,   401,   415,  -146,   -32,   -32,  -146,  -146,
    -146,  -146,   117,   139,   435,   447,  -146,  -146,  -146,  -146,
    -146,    48,  -146,   205,   226,  -146,  -146,  -146,   458,  -146,
      96,  -146,    96,  -146,    96,  -146,    96,  -146,    96,  -146,
      96,  -146,    96,  -146,    35,  -146,    35,  -146,  -146,  -146,
    -146,   134,   135,    64,    64,    64,    64,   371,  -146,  -146,
     419,   419,  -146,  -146,    91,    91,   125,   125,   127,   127,
     161,  -146,  -146,  -146,  -146,   419,   127,   127,    20,  -146,
    -146,    64,    64,   183,  -146,  -146,    64,    64,   127,   127,
      64,    64,  -146,  -146,  -146,  -146,   125,   125,  -146,  -146
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     8,     0,     1,     8,    17,    18,    20,
       0,    14,     8,     8,    20,     0,     5,    20,     0,    12,
       0,     0,    20,    20,     3,    28,    28,    19,     8,    21,
       0,     9,     8,     8,     0,     4,     2,     0,    25,    24,
      36,    13,    99,    58,     0,     0,     0,     0,   100,   101,
      11,    68,     0,     7,     6,    16,    15,     0,     0,     0,
       0,     0,    45,     0,     0,     0,    39,     0,    36,     0,
      40,    41,    42,    43,    64,     0,    96,    81,    97,    82,
      98,    83,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    10,     0,     0,    27,    26,
      23,    22,     0,     0,    44,     0,    34,    33,    35,    38,
      37,     0,    63,     0,     0,   103,   102,    84,    69,    89,
      74,    90,    75,    85,    70,    86,    71,    87,    72,    88,
      73,    95,    80,    91,    76,    92,    77,    93,    78,    94,
      79,    30,    29,     0,     0,     0,     0,     0,    62,    61,
       0,     0,    60,    59,     0,     0,    49,    49,    52,    52,
       0,    67,    66,    32,    31,     0,    52,    52,     0,    55,
      54,     0,     0,     0,    47,    46,     0,     0,    52,    52,
       0,     0,    53,    51,    57,    56,    49,    49,    50,    48
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -146,  -146,    -3,    -9,  -146,     9,    54,    59,  -146,  -146,
     137,   -39,   146,   110,  -106,  -146,  -146,  -145,   -87,  -146,
    -146,  -146,  -146,  -146,   -14,   -30,  -146
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     9,    57,    31,    10,    11,    16,    17,    18,
      38,    58,    66,    67,    68,    69,    70,   166,   169,    71,
      72,    48,    49,   111,   112,    73,    51
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      50,    20,   106,    14,    12,    55,    98,     7,     8,    22,
      23,    96,   167,     5,    77,    79,    81,    82,    74,     3,
      75,   176,     4,    32,   109,    40,    99,    56,    13,    53,
      54,   102,   107,   103,   104,   105,    97,   156,   157,   158,
     159,   188,   189,    95,   113,   114,   177,    33,   110,   148,
      93,    94,     1,   118,   120,   122,   124,   126,   128,   130,
     132,   134,   136,   138,   140,   178,   179,    42,    43,   149,
     182,   183,   170,    24,   186,   187,    27,    44,    45,   174,
     175,    35,    36,    46,    47,    41,    25,    42,    43,    26,
      15,   184,   185,     6,    28,    19,    61,    44,    45,    62,
      63,    64,    65,    46,    47,   141,   142,     7,     8,    91,
      92,    93,    94,   100,   101,   163,   164,   160,   143,    21,
     113,   113,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    28,   173,   161,   162,    30,    34,
     145,    37,    52,   144,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    59,    60,   165,   154,
     155,   168,   171,    39,    29,   146,   -80,   -80,   -80,   -80,
     -80,   -80,   -80,   -80,    91,    92,    93,    94,   108,     0,
       0,     0,     0,     0,   180,     0,     0,   172,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
       0,     0,     0,     0,     0,     0,   150,     0,     0,   181,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,     0,     0,     0,     0,   -65,   152,     0,   151,
       0,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,     0,     0,     0,   115,     0,     0,   153,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    76,     0,    42,    43,   116,     0,     0,     0,
      78,     0,    42,    43,    44,    45,     0,     0,     0,     0,
      46,    47,    44,    45,    80,     0,    42,    43,    46,    47,
       0,     0,   117,     0,    42,    43,    44,    45,     0,     0,
       0,     0,    46,    47,    44,    45,   119,     0,    42,    43,
      46,    47,     0,     0,   121,     0,    42,    43,    44,    45,
       0,     0,     0,     0,    46,    47,    44,    45,   123,     0,
      42,    43,    46,    47,     0,     0,   125,     0,    42,    43,
      44,    45,     0,     0,     0,     0,    46,    47,    44,    45,
     127,     0,    42,    43,    46,    47,     0,     0,   129,     0,
      42,    43,    44,    45,     0,     0,     0,     0,    46,    47,
      44,    45,   131,     0,    42,    43,    46,    47,     0,     0,
     133,     0,    42,    43,    44,    45,     0,     0,     0,     0,
      46,    47,    44,    45,   135,     0,    42,    43,    46,    47,
       0,     0,   137,     0,    42,    43,    44,    45,     0,     0,
       0,     0,    46,    47,    44,    45,   139,     0,    42,    43,
      46,    47,    42,    43,     0,     0,     0,     0,    44,    45,
       0,     0,    44,    45,    46,    47,     0,     0,    46,    47,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    83,    84,    85,    86,    87,    88,    89,   147,
      91,    92,    93,    94,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94
};

static const yytype_int16 yycheck[] =
{
      30,    10,     1,     6,     1,     1,     1,    39,    40,    12,
      13,     1,   157,     0,    44,    45,    46,    47,    20,     1,
      22,     1,     4,     1,     1,    28,    21,    23,    25,    32,
      33,    61,    31,    63,    64,    65,    26,   143,   144,   145,
     146,   186,   187,    52,    74,    75,    26,    25,    25,     1,
      15,    16,    27,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,   171,   172,     3,     4,    21,
     176,   177,   159,    14,   180,   181,    17,    13,    14,   166,
     167,    22,    23,    19,    20,     1,     1,     3,     4,     4,
      28,   178,   179,    25,    30,     4,    32,    13,    14,    35,
      36,    37,    38,    19,    20,    96,    97,    39,    40,    13,
      14,    15,    16,    59,    60,   154,   155,   147,     1,    22,
     150,   151,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    30,   165,   150,   151,     5,     3,
       1,    20,    24,    26,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    26,    26,    33,    25,
      25,    34,     1,    26,    18,    26,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    68,    -1,
      -1,    -1,    -1,    -1,     1,    -1,    -1,    26,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    26,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    -1,    -1,    -1,    -1,    21,     1,    -1,    24,
      -1,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    -1,    -1,    -1,     1,    -1,    -1,    23,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,     1,    -1,     3,     4,    21,    -1,    -1,    -1,
       1,    -1,     3,     4,    13,    14,    -1,    -1,    -1,    -1,
      19,    20,    13,    14,     1,    -1,     3,     4,    19,    20,
      -1,    -1,     1,    -1,     3,     4,    13,    14,    -1,    -1,
      -1,    -1,    19,    20,    13,    14,     1,    -1,     3,     4,
      19,    20,    -1,    -1,     1,    -1,     3,     4,    13,    14,
      -1,    -1,    -1,    -1,    19,    20,    13,    14,     1,    -1,
       3,     4,    19,    20,    -1,    -1,     1,    -1,     3,     4,
      13,    14,    -1,    -1,    -1,    -1,    19,    20,    13,    14,
       1,    -1,     3,     4,    19,    20,    -1,    -1,     1,    -1,
       3,     4,    13,    14,    -1,    -1,    -1,    -1,    19,    20,
      13,    14,     1,    -1,     3,     4,    19,    20,    -1,    -1,
       1,    -1,     3,     4,    13,    14,    -1,    -1,    -1,    -1,
      19,    20,    13,    14,     1,    -1,     3,     4,    19,    20,
      -1,    -1,     1,    -1,     3,     4,    13,    14,    -1,    -1,
      -1,    -1,    19,    20,    13,    14,     1,    -1,     3,     4,
      19,    20,     3,     4,    -1,    -1,    -1,    -1,    13,    14,
      -1,    -1,    13,    14,    19,    20,    -1,    -1,    19,    20,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    27,    42,     1,     4,     0,    25,    39,    40,    43,
      46,    47,     1,    25,    43,    28,    48,    49,    50,     4,
      44,    22,    43,    43,    48,     1,     4,    48,    30,    53,
       5,    45,     1,    25,     3,    48,    48,    20,    51,    51,
      43,     1,     3,     4,    13,    14,    19,    20,    62,    63,
      66,    67,    24,    43,    43,     1,    23,    44,    52,    26,
      26,    32,    35,    36,    37,    38,    53,    54,    55,    56,
      57,    60,    61,    66,    20,    22,     1,    66,     1,    66,
       1,    66,    66,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    44,     1,    26,     1,    21,
      47,    47,    66,    66,    66,    66,     1,    31,    54,     1,
      25,    64,    65,    66,    66,     1,    21,     1,    66,     1,
      66,     1,    66,     1,    66,     1,    66,     1,    66,     1,
      66,     1,    66,     1,    66,     1,    66,     1,    66,     1,
      66,    46,    46,     1,    26,     1,    26,    12,     1,    21,
       1,    24,     1,    23,    25,    25,    55,    55,    55,    55,
      66,    65,    65,    52,    52,    33,    58,    58,    34,    59,
      59,     1,    26,    66,    59,    59,     1,    26,    55,    55,
       1,    26,    55,    55,    59,    59,    55,    55,    58,    58
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    41,    42,    42,    42,    42,    43,    43,    43,    44,
      44,    45,    45,    45,    46,    46,    46,    47,    47,    48,
      48,    49,    50,    50,    50,    50,    51,    51,    51,    52,
      52,    52,    52,    53,    53,    54,    54,    55,    55,    55,
      55,    55,    55,    56,    56,    56,    57,    57,    58,    58,
      58,    59,    59,    59,    60,    60,    61,    61,    62,    62,
      62,    63,    63,    64,    64,    65,    65,    65,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    67,
      67,    67,    67,    67
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     5,     5,     4,     4,     4,     0,     2,
       4,     2,     0,     2,     1,     4,     4,     1,     1,     2,
       0,     2,     5,     5,     3,     3,     3,     3,     0,     3,
       3,     5,     5,     4,     4,     2,     0,     2,     2,     1,
       1,     1,     1,     1,     2,     1,     6,     6,     5,     0,
       5,     3,     0,     3,     5,     5,     7,     7,     1,     4,
       4,     4,     4,     1,     0,     1,     3,     3,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     2,     1,
       1,     1,     3,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (pt, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, pt); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, struct TreeNode ** pt)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (pt);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, struct TreeNode ** pt)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, pt);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule, struct TreeNode ** pt)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              , pt);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, pt); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
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
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
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

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, struct TreeNode ** pt)
{
  YYUSE (yyvaluep);
  YYUSE (pt);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (struct TreeNode ** pt)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
      yychar = yylex ();
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

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
#line 41 "yacc.y" /* yacc.c:1646  */
    {
		(yyval.node) = CreatePT(Root, (yyvsp[-3].data), 
			CreatePT(List, "list", (yyvsp[-1].node), (yyvsp[0].node))
		, NULL);
		*pt = (yyval.node);
	}
#line 1449 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 47 "yacc.y" /* yacc.c:1646  */
    {
		fprintf(stderr, "line (%d) : \'Ident\' is missing\n", yylineno);
		(yyval.node) = CreatePT(Root, NULL, 
			CreatePT(List, "list", (yyvsp[-1].node), (yyvsp[0].node))
		, NULL);
		*pt = (yyval.node);
	}
#line 1461 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 54 "yacc.y" /* yacc.c:1646  */
    {
		fprintf(stderr, "line (%d) : \';\' is missing\n", yylineno);
		(yyval.node) = CreatePT(Root, (yyvsp[-3].data), 
			CreatePT(List, "list", (yyvsp[-1].node), (yyvsp[0].node))
		, NULL);
		*pt = (yyval.node);
	}
#line 1473 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 61 "yacc.y" /* yacc.c:1646  */
    {
		fprintf(stderr, "line (%d) : \'Ident\' is missing\n", yylineno);
		fprintf(stderr, "line (%d) : \';\' is missing\n", yylineno);
		(yyval.node) = CreatePT(Root, NULL, 
			CreatePT(List, "list", (yyvsp[-1].node), (yyvsp[0].node))
		, NULL);
		*pt = (yyval.node);
	}
#line 1486 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 71 "yacc.y" /* yacc.c:1646  */
    {
		(yyvsp[-3].node)->sibling = (yyvsp[-2].node);
		(yyval.node) = CreatePT(Decl, "decl", (yyvsp[-3].node), (yyvsp[0].node));
	}
#line 1495 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 75 "yacc.y" /* yacc.c:1646  */
    {
		fprintf(stderr, "line (%d) : \';\' is missing\n", yylineno);
		(yyvsp[-3].node)->sibling = (yyvsp[-2].node);
		(yyval.node) = CreatePT(Decl, "decl", (yyvsp[-3].node), (yyvsp[0].node));
	}
#line 1505 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 80 "yacc.y" /* yacc.c:1646  */
    { (yyval.node) = CreatePT(Void, "void", NULL, NULL); }
#line 1511 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 83 "yacc.y" /* yacc.c:1646  */
    { (yyval.node) = CreatePT(Ident, (yyvsp[-1].data), (yyvsp[0].node), NULL); }
#line 1517 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 84 "yacc.y" /* yacc.c:1646  */
    { (yyval.node) = CreatePT(Ident, (yyvsp[-3].data), NULL, (yyvsp[0].node)); }
#line 1523 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 87 "yacc.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node);}
#line 1529 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 88 "yacc.y" /* yacc.c:1646  */
    { (yyval.node) = CreatePT(Void, NULL, NULL, NULL); }
#line 1535 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 89 "yacc.y" /* yacc.c:1646  */
    {
		fprintf(stderr, "line (%d) : \'expr\' is missing\n", yylineno);
		(yyval.node) = CreatePT(Void, NULL, NULL, NULL); 
	}
#line 1544 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 95 "yacc.y" /* yacc.c:1646  */
    { (yyval.node) = CreatePT(Type, "type", (yyvsp[0].node), NULL); }
#line 1550 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 96 "yacc.y" /* yacc.c:1646  */
    {
		(yyvsp[-3].node)->sibling = CreatePT(Num, (yyvsp[-1].data), NULL, NULL);
		(yyval.node) = CreatePT(Type, "type", (yyvsp[-3].node), NULL);
	}
#line 1559 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 100 "yacc.y" /* yacc.c:1646  */
    {
		fprintf(stderr, "line (%d) : \']\' is missing\n", yylineno);
		(yyvsp[-3].node)->sibling = CreatePT(Num, (yyvsp[-1].data), NULL, NULL);
		(yyval.node) = CreatePT(Type, "type", (yyvsp[-3].node), NULL);
	}
#line 1569 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 107 "yacc.y" /* yacc.c:1646  */
    { (yyval.node) = CreatePT(Int, "int", NULL, NULL); }
#line 1575 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 108 "yacc.y" /* yacc.c:1646  */
    { (yyval.node) = CreatePT(Float, "float", NULL, NULL); }
#line 1581 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 111 "yacc.y" /* yacc.c:1646  */
    {(yyval.node) = CreatePT(List, "list", (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1587 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 112 "yacc.y" /* yacc.c:1646  */
    { (yyval.node) = CreatePT(Void, "void", NULL, NULL); }
#line 1593 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 115 "yacc.y" /* yacc.c:1646  */
    {
		(yyvsp[-1].node)->child->sibling->sibling = (yyvsp[0].node);
		(yyval.node) = (yyvsp[-1].node);
	}
#line 1602 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 121 "yacc.y" /* yacc.c:1646  */
    {
		(yyvsp[-2].node)->sibling = (yyvsp[0].node);
		(yyval.node) = CreatePT(Func, (yyvsp[-3].data), (yyvsp[-2].node), NULL);
	}
#line 1611 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 125 "yacc.y" /* yacc.c:1646  */
    {
		fprintf(stderr, "line (%d) : \'Ident\' is missing\n", yylineno);
		(yyvsp[-2].node)->sibling = (yyvsp[0].node);
		(yyval.node) = CreatePT(Func, NULL, (yyvsp[-2].node), NULL);
	}
#line 1621 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 130 "yacc.y" /* yacc.c:1646  */
    { 
		(yyvsp[0].node)->sibling = CreatePT(Void, "void", NULL, NULL);
		(yyval.node) = CreatePT(Func, (yyvsp[-1].data), (yyvsp[0].node), NULL); 
	}
#line 1630 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 134 "yacc.y" /* yacc.c:1646  */
    { 
		fprintf(stderr, "line (%d) : \'Ident\' is missing\n", yylineno);
		(yyvsp[0].node)->sibling = CreatePT(Void, "void", NULL, NULL);
		(yyval.node) = CreatePT(Func, NULL, (yyvsp[0].node), NULL); 
	}
#line 1640 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 141 "yacc.y" /* yacc.c:1646  */
    { (yyval.node) = CreatePT(List, "list", (yyvsp[-1].node), NULL);}
#line 1646 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 142 "yacc.y" /* yacc.c:1646  */
    {
		fprintf(stderr, "line (%d) : \')\' is missing\n", yylineno);
		(yyval.node) = CreatePT(List, "list", (yyvsp[-1].node), NULL);
	}
#line 1655 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 146 "yacc.y" /* yacc.c:1646  */
    { (yyval.node) = CreatePT(Void, "void", NULL, NULL); }
#line 1661 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 149 "yacc.y" /* yacc.c:1646  */
    { (yyvsp[0].node)->sibling = (yyvsp[-2].node); (yyval.node) = CreatePT(Param, "param", (yyvsp[0].node),NULL);}
#line 1667 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 150 "yacc.y" /* yacc.c:1646  */
    { 
		fprintf(stderr, "line (%d) : \':\' is missing\n", yylineno);
		(yyvsp[0].node)->sibling = (yyvsp[-2].node); (yyval.node) = CreatePT(Param, "param", (yyvsp[0].node), NULL);
	}
#line 1676 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 154 "yacc.y" /* yacc.c:1646  */
    { 
		(yyvsp[-2].node)->sibling = (yyvsp[-4].node);
		(yyval.node) = CreatePT(Param, "param", (yyvsp[-2].node), (yyvsp[0].node)); 
	}
#line 1685 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 158 "yacc.y" /* yacc.c:1646  */
    { 
		fprintf(stderr, "line (%d) : \':\' is missing\n", yylineno);
		(yyvsp[-2].node)->sibling = (yyvsp[-4].node); (yyval.node) = CreatePT(Param, "param", (yyvsp[-2].node), (yyvsp[0].node));
	}
#line 1694 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 164 "yacc.y" /* yacc.c:1646  */
    { 
		(yyval.node) = CreatePT(Block, "block", (yyvsp[-1].node), (yyvsp[-2].node)); 
	}
#line 1702 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 167 "yacc.y" /* yacc.c:1646  */
    {
		fprintf(stderr, "line (%d) : \'end\' is missing\n", yylineno);
		(yyval.node) = CreatePT(Block, "block", (yyvsp[-1].node), (yyvsp[-2].node));
	}
#line 1711 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 173 "yacc.y" /* yacc.c:1646  */
    { (yyvsp[-1].node)->sibling = (yyvsp[0].node); (yyval.node) = (yyvsp[-1].node); }
#line 1717 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 174 "yacc.y" /* yacc.c:1646  */
    { (yyval.node) = NULL; }
#line 1723 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 177 "yacc.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 1729 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 178 "yacc.y" /* yacc.c:1646  */
    { fprintf(stderr, "line (%d) : \';\' is missing\n", yylineno);}
#line 1735 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 187 "yacc.y" /* yacc.c:1646  */
    { (yyval.node) = CreatePT(Return, "return", (yyvsp[0].node), NULL); }
#line 1741 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 188 "yacc.y" /* yacc.c:1646  */
    { (yyval.node) = CreatePT(Nop, "nop", NULL, NULL); }
#line 1747 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 191 "yacc.y" /* yacc.c:1646  */
    {
		(yyvsp[-4].node)->sibling = (yyvsp[-2].node);
		(yyvsp[-2].node)->sibling = CreatePT(List, "list", (yyvsp[-1].node), (yyvsp[0].node));
		(yyval.node) = CreatePT(If, "if", (yyvsp[-4].node), NULL);
	}
#line 1757 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 196 "yacc.y" /* yacc.c:1646  */
    {
		fprintf(stderr, "line (%d) : \':\' is required\n", yylineno);
		(yyvsp[-4].node)->sibling = (yyvsp[-2].node);
		(yyvsp[-2].node)->sibling = CreatePT(List, "list", (yyvsp[-1].node), (yyvsp[0].node));
		(yyval.node) = CreatePT(If, "if", (yyvsp[-4].node), NULL);
	}
#line 1768 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 204 "yacc.y" /* yacc.c:1646  */
    {
		(yyvsp[-3].node)->sibling = (yyvsp[-1].node);
		(yyval.node) = CreatePT(Elif, "elif", (yyvsp[-3].node), (yyvsp[0].node));
	}
#line 1777 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 208 "yacc.y" /* yacc.c:1646  */
    { (yyval.node) = CreatePT(Void, "void", NULL, NULL); }
#line 1783 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 209 "yacc.y" /* yacc.c:1646  */
    {
		fprintf(stderr, "line (%d) : \':\' is required\n", yylineno);
		(yyvsp[-3].node)->sibling = (yyvsp[-1].node);
		(yyval.node) = CreatePT(Elif, "elif", (yyvsp[-3].node), (yyvsp[0].node));
	}
#line 1793 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 216 "yacc.y" /* yacc.c:1646  */
    { (yyval.node) = CreatePT(Else, "else", (yyvsp[0].node), NULL); }
#line 1799 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 217 "yacc.y" /* yacc.c:1646  */
    { (yyval.node) = CreatePT(Void, "void", NULL, NULL); }
#line 1805 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 218 "yacc.y" /* yacc.c:1646  */
    { 
		fprintf(stderr, "line (%d) : \':\' is required\n", yylineno);
		(yyval.node) = CreatePT(Else, "else", (yyvsp[0].node), NULL); 
	}
#line 1814 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 224 "yacc.y" /* yacc.c:1646  */
    {
		(yyvsp[-3].node)->sibling = (yyvsp[-1].node); (yyvsp[-1].node)->sibling = (yyvsp[0].node);
		(yyval.node) = CreatePT(While, "while", (yyvsp[-3].node), NULL);
	}
#line 1823 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 228 "yacc.y" /* yacc.c:1646  */
    {
		fprintf(stderr, "line (%d) : \':\' is required\n", yylineno);
		(yyvsp[-3].node)->sibling = (yyvsp[-1].node); (yyvsp[-1].node)->sibling = (yyvsp[0].node);
		(yyval.node) = CreatePT(While, "while", (yyvsp[-3].node), NULL);
	}
#line 1833 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 235 "yacc.y" /* yacc.c:1646  */
    {
		(yyvsp[-5].node)->sibling = (yyvsp[-3].node); (yyvsp[-1].node)->sibling = (yyvsp[0].node);
		(yyval.node) = CreatePT(For, "for", 
			CreatePT(In, "in", (yyvsp[-5].node), (yyvsp[-1].node)),
			NULL);
	}
#line 1844 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 241 "yacc.y" /* yacc.c:1646  */
    {
		fprintf(stderr, "line (%d) : \':\' is required\n", yylineno);
		(yyvsp[-5].node)->sibling = (yyvsp[-3].node); (yyvsp[-1].node)->sibling = (yyvsp[0].node);
		(yyval.node) = CreatePT(For, "for", 
			CreatePT(In, "in", (yyvsp[-5].node), (yyvsp[-1].node)),
			NULL);
	}
#line 1856 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 250 "yacc.y" /* yacc.c:1646  */
    { (yyval.node) = CreatePT(Var, (yyvsp[0].data), NULL, NULL); }
#line 1862 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 251 "yacc.y" /* yacc.c:1646  */
    { (yyval.node) = CreatePT(Var, (yyvsp[-3].data), (yyvsp[-1].node), NULL); }
#line 1868 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 252 "yacc.y" /* yacc.c:1646  */
    { 
		fprintf(stderr, "line (%d) : \']\' is required\n", yylineno);
		(yyval.node) = CreatePT(Var, (yyvsp[-3].data), (yyvsp[-1].node), NULL);
	}
#line 1877 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 258 "yacc.y" /* yacc.c:1646  */
    { (yyval.node) = CreatePT(Proc, (yyvsp[-3].data), (yyvsp[-1].node), NULL); }
#line 1883 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 259 "yacc.y" /* yacc.c:1646  */
    {
		fprintf(stderr, "line (%d) : \')\' is required\n", yylineno);
		(yyval.node) = CreatePT(Proc, (yyvsp[-3].data), (yyvsp[-1].node), NULL);
	}
#line 1892 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 265 "yacc.y" /* yacc.c:1646  */
    { (yyval.node) = CreatePT(List, "List", (yyvsp[0].node), NULL); }
#line 1898 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 266 "yacc.y" /* yacc.c:1646  */
    { (yyval.node) = CreatePT(Void, "void", NULL, NULL); }
#line 1904 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 270 "yacc.y" /* yacc.c:1646  */
    { (yyvsp[-2].node)->sibling = (yyvsp[0].node); (yyval.node) = (yyvsp[-2].node); }
#line 1910 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 271 "yacc.y" /* yacc.c:1646  */
    {
		fprintf(stderr, "line (%d) : \',\' is missing\n", yylineno);
		(yyvsp[-2].node)->sibling = (yyvsp[0].node); (yyval.node) = (yyvsp[-2].node);
	}
#line 1919 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 278 "yacc.y" /* yacc.c:1646  */
    { (yyvsp[-2].node)->sibling = (yyvsp[0].node); (yyval.node) = CreatePT(Assign, "=", (yyvsp[-2].node), NULL); }
#line 1925 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 279 "yacc.y" /* yacc.c:1646  */
    { (yyvsp[-2].node)->sibling = (yyvsp[0].node); (yyval.node) = CreatePT(Greater, "<", (yyvsp[-2].node), NULL); }
#line 1931 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 280 "yacc.y" /* yacc.c:1646  */
    { (yyvsp[-2].node)->sibling = (yyvsp[0].node); (yyval.node) = CreatePT(EquGre, "<=", (yyvsp[-2].node), NULL); }
#line 1937 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 281 "yacc.y" /* yacc.c:1646  */
    { (yyvsp[-2].node)->sibling = (yyvsp[0].node); (yyval.node) = CreatePT(Less, ">", (yyvsp[-2].node), NULL); }
#line 1943 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 282 "yacc.y" /* yacc.c:1646  */
    { (yyvsp[-2].node)->sibling = (yyvsp[0].node); (yyval.node) = CreatePT(EquLess, ">=", (yyvsp[-2].node), NULL); }
#line 1949 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 283 "yacc.y" /* yacc.c:1646  */
    { (yyvsp[-2].node)->sibling = (yyvsp[0].node); (yyval.node) = CreatePT(Equ, "==", (yyvsp[-2].node), NULL); }
#line 1955 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 284 "yacc.y" /* yacc.c:1646  */
    { (yyvsp[-2].node)->sibling = (yyvsp[0].node); (yyval.node) = CreatePT(NotEqu, "!=", (yyvsp[-2].node), NULL); }
#line 1961 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 285 "yacc.y" /* yacc.c:1646  */
    { (yyvsp[-2].node)->sibling = (yyvsp[0].node); (yyval.node) = CreatePT(Plus, "+", (yyvsp[-2].node), NULL); }
#line 1967 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 286 "yacc.y" /* yacc.c:1646  */
    { (yyvsp[-2].node)->sibling = (yyvsp[0].node); (yyval.node) = CreatePT(Minus, "-", (yyvsp[-2].node), NULL); }
#line 1973 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 287 "yacc.y" /* yacc.c:1646  */
    { (yyvsp[-2].node)->sibling = (yyvsp[0].node); (yyval.node) = CreatePT(Mul, "*", (yyvsp[-2].node), NULL); }
#line 1979 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 288 "yacc.y" /* yacc.c:1646  */
    { (yyvsp[-2].node)->sibling = (yyvsp[0].node); (yyval.node) = CreatePT(Div, "/", (yyvsp[-2].node), NULL); }
#line 1985 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 289 "yacc.y" /* yacc.c:1646  */
    { (yyvsp[-2].node)->sibling = (yyvsp[0].node); (yyval.node) = CreatePT(In, "in", (yyvsp[-2].node), NULL); }
#line 1991 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 290 "yacc.y" /* yacc.c:1646  */
    { (yyval.node) = CreatePT(Pos, "+", (yyvsp[0].node), NULL); }
#line 1997 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 291 "yacc.y" /* yacc.c:1646  */
    { (yyval.node) = CreatePT(Neg, "-", (yyvsp[0].node), NULL); }
#line 2003 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 292 "yacc.y" /* yacc.c:1646  */
    { (yyval.node) = CreatePT(Not, "!", (yyvsp[0].node), NULL); }
#line 2009 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 293 "yacc.y" /* yacc.c:1646  */
    { 
		fprintf(stderr, "line (%d) : \'expr\' is required\n", yylineno);
		(yyvsp[-2].node)->sibling =  CreatePT(Void, "void", NULL, NULL); (yyval.node) = CreatePT(Assign, "=", (yyvsp[-2].node), NULL); }
#line 2017 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 296 "yacc.y" /* yacc.c:1646  */
    { 
		fprintf(stderr, "line (%d) : \'expr\' is required\n", yylineno);
		(yyvsp[-2].node)->sibling =  CreatePT(Void, "void", NULL, NULL); (yyval.node) = CreatePT(Greater, "<", (yyvsp[-2].node), NULL); }
#line 2025 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 299 "yacc.y" /* yacc.c:1646  */
    { 
		fprintf(stderr, "line (%d) : \'expr\' is required\n", yylineno);
		(yyvsp[-2].node)->sibling =  CreatePT(Void, "void", NULL, NULL); (yyval.node) = CreatePT(EquGre, "<=", (yyvsp[-2].node), NULL); }
#line 2033 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 302 "yacc.y" /* yacc.c:1646  */
    { 
		fprintf(stderr, "line (%d) : \'expr\' is required\n", yylineno);
		(yyvsp[-2].node)->sibling = CreatePT(Void, "void", NULL, NULL); (yyval.node) = CreatePT(Less, ">", (yyvsp[-2].node), NULL); }
#line 2041 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 305 "yacc.y" /* yacc.c:1646  */
    { 
		fprintf(stderr, "line (%d) : \'expr\' is required\n", yylineno);
		(yyvsp[-2].node)->sibling = CreatePT(Void, "void", NULL, NULL); (yyval.node) = CreatePT(EquLess, ">=", (yyvsp[-2].node), NULL); }
#line 2049 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 308 "yacc.y" /* yacc.c:1646  */
    { 
		fprintf(stderr, "line (%d) : \'expr\' is required\n", yylineno);
		(yyvsp[-2].node)->sibling = CreatePT(Void, "void", NULL, NULL); (yyval.node) = CreatePT(Equ, "==", (yyvsp[-2].node), NULL); }
#line 2057 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 311 "yacc.y" /* yacc.c:1646  */
    {
		fprintf(stderr, "line (%d) : \'expr\' is required\n", yylineno);
		(yyvsp[-2].node)->sibling = CreatePT(Void, "void", NULL, NULL); (yyval.node) = CreatePT(NotEqu, "!=", (yyvsp[-2].node), NULL); }
#line 2065 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 314 "yacc.y" /* yacc.c:1646  */
    { 
		fprintf(stderr, "line (%d) : \'expr\' is required\n", yylineno);
		(yyvsp[-2].node)->sibling = CreatePT(Void, "void", NULL, NULL); (yyval.node) = CreatePT(Plus, "+", (yyvsp[-2].node), NULL); }
#line 2073 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 317 "yacc.y" /* yacc.c:1646  */
    { 
		fprintf(stderr, "line (%d) : \'expr\' is required\n", yylineno);
		(yyvsp[-2].node)->sibling = CreatePT(Void, "void", NULL, NULL); (yyval.node) = CreatePT(Minus, "-", (yyvsp[-2].node), NULL); }
#line 2081 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 320 "yacc.y" /* yacc.c:1646  */
    { 
		fprintf(stderr, "line (%d) : \'expr\' is required\n", yylineno);
		(yyvsp[-2].node)->sibling = CreatePT(Void, "void", NULL, NULL); (yyval.node) = CreatePT(Mul, "*", (yyvsp[-2].node), NULL); }
#line 2089 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 323 "yacc.y" /* yacc.c:1646  */
    { 
		fprintf(stderr, "line (%d) : \'expr\' is required\n", yylineno);
		(yyvsp[-2].node)->sibling = CreatePT(Void, "void", NULL, NULL); (yyval.node) = CreatePT(Div, "/", (yyvsp[-2].node), NULL); }
#line 2097 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 326 "yacc.y" /* yacc.c:1646  */
    { 
		fprintf(stderr, "line (%d) : \'expr\' is required\n", yylineno);
		(yyvsp[-2].node)->sibling =  CreatePT(Void, "void", NULL, NULL); (yyval.node) = CreatePT(In, "in", (yyvsp[-2].node), NULL); }
#line 2105 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 329 "yacc.y" /* yacc.c:1646  */
    { 
		fprintf(stderr, "line (%d) : \'expr\' is required\n", yylineno);
		(yyval.node) = CreatePT(Pos, "+", CreatePT(Void, "void", NULL, NULL), NULL); }
#line 2113 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 332 "yacc.y" /* yacc.c:1646  */
    { 
		fprintf(stderr, "line (%d) : \'expr\' is required\n", yylineno);
		(yyval.node) = CreatePT(Neg, "-", CreatePT(Void, "void", NULL, NULL), NULL); }
#line 2121 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 335 "yacc.y" /* yacc.c:1646  */
    { 
		fprintf(stderr, "line (%d) : \'expr\' is required\n", yylineno);
		(yyval.node) = CreatePT(Not, "!", CreatePT(Void, "void", NULL, NULL), NULL); }
#line 2129 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 340 "yacc.y" /* yacc.c:1646  */
    { (yyval.node) = CreatePT(Num, (yyvsp[0].data), NULL, NULL); }
#line 2135 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 343 "yacc.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 2141 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 344 "yacc.y" /* yacc.c:1646  */
    { fprintf(stderr, "line (%d) : \')\' is required\n", yylineno); (yyval.node) = (yyvsp[-1].node); }
#line 2147 "yacc.tab.c" /* yacc.c:1646  */
    break;


#line 2151 "yacc.tab.c" /* yacc.c:1646  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (pt, YY_("syntax error"));
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
        yyerror (pt, yymsgp);
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
                      yytoken, &yylval, pt);
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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
                  yystos[yystate], yyvsp, pt);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (pt, YY_("memory exhausted"));
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
                  yytoken, &yylval, pt);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, pt);
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
  return yyresult;
}
#line 346 "yacc.y" /* yacc.c:1906  */

