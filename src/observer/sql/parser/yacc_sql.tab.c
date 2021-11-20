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
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 2 "yacc_sql.y" /* yacc.c:339  */


#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.tab.h"
#include "sql/parser/lex.yy.h"
// #include "common/log/log.h" // 包含C++中的头文件

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ParserContext {
  Query * ssql;
  size_t select_length;
  size_t condition_length;
  size_t from_length;
  size_t value_length;
  Value values[MAX_NUM];
  Condition conditions[MAX_NUM];
  Selects sub_selects[MAX_NUM];
  
  CompOp comp;
  char id[MAX_NUM];
  size_t data_num;
  size_t sub_select_num;
  RelAttr attr_list_stack[MAX_NUM][MAX_NUM];
  size_t attr_list_length_stack[MAX_NUM];
  size_t attr_list_stack_top;
//   Selects *cur_select;
} ParserContext;

//获取子串
char *substr(const char *s,int n1,int n2)/*从s中提取下标为n1~n2的字符组成一个新字符串，然后返回这个新串的首地址*/
{
  char *sp = malloc(sizeof(char) * (n2 - n1 + 2));
  int i, j = 0;
  for (i = n1; i <= n2; i++) {
    sp[j++] = s[i];
  }
  sp[j] = 0;
  return sp;
}

void yyerror(yyscan_t scanner, const char *str)
{
  ParserContext *context = (ParserContext *)(yyget_extra(scanner));
  query_reset(context->ssql);
  context->ssql->flag = SCF_ERROR;
  context->condition_length = 0;
  context->from_length = 0;
  context->select_length = 0;
  context->value_length = 0;
  context->ssql->sstr.insertion.value_num = 0;
  context->data_num = 0;
  context->sub_select_num = 0;
  context->attr_list_stack_top = 0;
  printf("parse sql failed. error=%s", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)


#line 134 "yacc_sql.tab.c" /* yacc.c:339  */

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
   by #include "yacc_sql.tab.h".  */
#ifndef YY_YY_YACC_SQL_TAB_H_INCLUDED
# define YY_YY_YACC_SQL_TAB_H_INCLUDED
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
    SEMICOLON = 258,
    CREATE = 259,
    DROP = 260,
    TABLE = 261,
    TABLES = 262,
    INDEX = 263,
    SELECT = 264,
    ASC = 265,
    DESC = 266,
    SHOW = 267,
    SYNC = 268,
    INSERT = 269,
    DELETE = 270,
    UPDATE = 271,
    LBRACE = 272,
    RBRACE = 273,
    COMMA = 274,
    TRX_BEGIN = 275,
    TRX_COMMIT = 276,
    TRX_ROLLBACK = 277,
    INT_T = 278,
    STRING_T = 279,
    FLOAT_T = 280,
    DATE_T = 281,
    HELP = 282,
    EXIT = 283,
    DOT = 284,
    INTO = 285,
    VALUES = 286,
    FROM = 287,
    WHERE = 288,
    AND = 289,
    SET = 290,
    ON = 291,
    LOAD = 292,
    DATA = 293,
    INFILE = 294,
    EQ = 295,
    LT = 296,
    GT = 297,
    LE = 298,
    GE = 299,
    NE = 300,
    INNER = 301,
    JOIN = 302,
    ORDER = 303,
    GROUP = 304,
    BY = 305,
    UNIQUE = 306,
    TEXT_T = 307,
    NOT = 308,
    NULL_T = 309,
    NULLABLE = 310,
    IS_T = 311,
    IN_T = 312,
    NUMBER = 313,
    FLOAT = 314,
    ID = 315,
    PATH = 316,
    SSS = 317,
    STAR = 318,
    STRING_V = 319,
    MAX = 320,
    MIN = 321,
    COUNT = 322,
    AVG = 323
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 131 "yacc_sql.y" /* yacc.c:355  */

  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  char *string;
  int number;
  float floats;
	char *position;

#line 253 "yacc_sql.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (void *scanner);

#endif /* !YY_YY_YACC_SQL_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 269 "yacc_sql.tab.c" /* yacc.c:358  */

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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   364

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  69
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  144
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  347

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   323

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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   162,   162,   164,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   188,   193,   198,   204,   210,   216,   222,   228,   234,
     241,   246,   254,   261,   270,   272,   276,   293,   309,   318,
     321,   322,   323,   324,   325,   326,   327,   328,   329,   330,
     331,   332,   335,   344,   361,   363,   368,   373,   375,   380,
     383,   386,   390,   397,   407,   417,   447,   474,   477,   482,
     492,   500,   508,   516,   529,   542,   555,   568,   581,   594,
     606,   618,   634,   637,   647,   657,   667,   680,   693,   706,
     719,   732,   740,   753,   767,   769,   773,   775,   780,   782,
     789,   796,   803,   810,   817,   826,   828,   835,   842,   849,
     856,   863,   872,   874,   881,   890,   892,   899,   909,   911,
     917,   938,   958,   978,  1000,  1021,  1042,  1061,  1070,  1079,
    1088,  1097,  1107,  1117,  1140,  1166,  1167,  1168,  1169,  1170,
    1171,  1172,  1173,  1177,  1198
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SEMICOLON", "CREATE", "DROP", "TABLE",
  "TABLES", "INDEX", "SELECT", "ASC", "DESC", "SHOW", "SYNC", "INSERT",
  "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN",
  "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T", "FLOAT_T", "DATE_T",
  "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "SET",
  "ON", "LOAD", "DATA", "INFILE", "EQ", "LT", "GT", "LE", "GE", "NE",
  "INNER", "JOIN", "ORDER", "GROUP", "BY", "UNIQUE", "TEXT_T", "NOT",
  "NULL_T", "NULLABLE", "IS_T", "IN_T", "NUMBER", "FLOAT", "ID", "PATH",
  "SSS", "STAR", "STRING_V", "MAX", "MIN", "COUNT", "AVG", "$accept",
  "commands", "command", "exit", "help", "sync", "begin", "commit",
  "rollback", "drop_table", "show_tables", "desc_table", "create_index",
  "drop_index", "create_table", "attr_def_list", "attr_def", "number",
  "type", "ID_get", "insert", "muti_value_list", "muti_value",
  "value_list", "value", "delete", "update", "select", "join_list",
  "select_attr", "attr_list", "rel_list", "where", "order_by",
  "order_by_list", "group_by", "group_by_list", "condition_list",
  "condition", "comOp", "subselect", "load_data", YY_NULLPTR
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323
};
# endif

#define YYPACT_NINF -313

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-313)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -313,   138,  -313,    11,    42,   144,   -42,    29,    46,    56,
      81,    65,   136,   152,   184,   193,   194,   103,  -313,  -313,
    -313,  -313,  -313,  -313,  -313,  -313,  -313,  -313,  -313,  -313,
    -313,  -313,  -313,  -313,  -313,  -313,   148,   157,   210,   159,
     162,    12,  -313,   203,   204,   206,   207,   195,   222,   223,
    -313,   168,   169,   196,  -313,  -313,  -313,  -313,  -313,   191,
     215,   197,   174,   232,   233,    69,    49,  -313,   177,   178,
     101,   179,   180,  -313,  -313,   211,   208,   183,   182,   185,
     186,   212,  -313,  -313,    71,   230,   234,   235,   236,   231,
     231,    16,    28,    48,   237,    52,    -8,   239,    61,   246,
     214,   227,  -313,   240,     2,   241,   200,   122,  -313,   201,
     202,   135,   205,  -313,  -313,   231,   209,   231,   213,   231,
     216,  -313,   231,   217,   218,   219,   208,   208,    86,   244,
    -313,  -313,  -313,   127,  -313,    31,   238,  -313,    86,   258,
     185,   249,   121,   133,   160,   161,  -313,   251,   220,   253,
     231,   231,    60,    64,   256,   257,    67,  -313,   261,  -313,
     263,  -313,   264,  -313,   265,   252,   224,   282,   242,   267,
     239,   284,   228,  -313,  -313,  -313,  -313,  -313,  -313,   243,
     -41,  -313,    -7,   -10,   119,    61,  -313,   208,   229,   240,
     288,   245,  -313,   247,  -313,   248,  -313,   250,  -313,   254,
     274,   255,  -313,  -313,   231,   259,   231,   260,   231,   231,
     231,   262,   231,   231,   231,   231,  -313,   269,  -313,   266,
     268,    86,   275,   244,  -313,   149,  -313,   270,  -313,   285,
    -313,  -313,  -313,   271,  -313,   277,  -313,   238,   292,   293,
    -313,  -313,  -313,  -313,  -313,  -313,  -313,   279,   295,   289,
    -313,   290,  -313,   291,  -313,  -313,  -313,   296,  -313,  -313,
    -313,  -313,    61,   272,   273,   300,   267,  -313,  -313,   109,
       5,  -313,   144,  -313,   276,  -313,  -313,  -313,  -313,  -313,
     307,   231,   231,   231,   238,    10,   278,  -313,  -313,   280,
    -313,   297,  -313,  -313,   281,  -313,  -313,  -313,  -313,  -313,
     283,   299,   299,   286,   287,  -313,    75,  -313,   294,   298,
    -313,  -313,  -313,    13,    95,   301,   302,  -313,  -313,   252,
     299,   299,   303,  -313,   299,   299,  -313,    82,   308,   208,
    -313,  -313,    97,  -313,  -313,   304,  -313,  -313,   310,   299,
     299,  -313,   308,  -313,  -313,  -313,  -313
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    20,
      19,    14,    15,    16,    17,     9,    10,    11,    12,    13,
       8,     5,     7,     6,     4,    18,     0,     0,     0,     0,
       0,    82,    69,     0,     0,     0,     0,     0,     0,     0,
      23,     0,     0,     0,    24,    25,    26,    22,    21,     0,
       0,     0,     0,     0,     0,     0,     0,    70,     0,     0,
       0,     0,     0,    29,    28,     0,    96,     0,     0,     0,
       0,     0,    27,    32,    82,     0,     0,     0,     0,    82,
      82,     0,     0,     0,     0,     0,    94,     0,     0,     0,
       0,     0,    52,    34,     0,     0,     0,     0,    83,     0,
       0,     0,     0,    71,    72,    82,     0,    82,     0,    82,
       0,    79,    82,     0,     0,     0,    96,    96,     0,    54,
      62,    59,    60,     0,    61,     0,   118,    63,     0,     0,
       0,     0,    40,    43,    46,    49,    38,    37,     0,     0,
      82,    82,     0,     0,     0,     0,     0,    73,     0,    75,
       0,    77,     0,    80,     0,    94,     0,     0,    98,    57,
       0,     0,     0,   135,   136,   137,   138,   139,   140,     0,
       0,   141,     0,     0,     0,     0,    97,    96,     0,    34,
       0,     0,    42,     0,    45,     0,    48,     0,    51,     0,
       0,     0,    84,    85,    82,     0,    82,     0,    82,    82,
      82,     0,    82,    82,    82,    82,    95,     0,    66,     0,
     112,     0,     0,    54,    53,     0,   142,     0,   127,     0,
     122,   120,   133,     0,   131,   123,   121,   118,     0,     0,
      35,    33,    41,    44,    47,    50,    39,     0,     0,     0,
      86,     0,    88,     0,    90,    91,    92,     0,    74,    76,
      78,    81,     0,     0,     0,     0,    57,    56,    55,     0,
       0,   128,     0,   132,     0,   119,    64,   144,    36,    30,
       0,    82,    82,    82,   118,   105,     0,    65,    58,     0,
     129,     0,   124,   134,     0,   125,    31,    87,    89,    93,
      67,   105,   105,     0,     0,    99,   115,   130,     0,     0,
      68,   100,   101,   105,   105,     0,     0,   113,   126,    94,
     105,   105,     0,   106,   105,   105,   102,   115,   115,    96,
     107,   108,   105,   103,   104,     0,   116,   114,     0,   105,
     105,   109,   115,   143,   110,   111,   117
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -313,  -313,  -313,  -313,  -313,  -313,  -313,  -313,  -313,  -313,
    -313,  -313,  -313,  -313,  -313,   132,   171,  -313,  -313,  -313,
    -313,   107,   163,    73,  -124,  -313,  -313,  -313,    35,    59,
     -82,  -162,  -126,  -313,  -222,  -313,  -312,  -228,  -179,  -130,
      70,  -313
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,   141,   103,   247,   147,   104,
      31,   171,   129,   222,   135,    32,    33,    34,   126,    47,
      67,   127,    99,   220,   305,   265,   317,   186,   136,   182,
     232,    35
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
     167,   168,   108,   216,   169,   184,   237,   113,   114,   275,
     229,   124,   227,   228,   187,   336,   337,    36,    48,    37,
     301,   302,   229,   320,   321,   142,   143,   144,   145,   303,
     346,    65,   303,   157,   115,   159,    49,   161,   125,   304,
     163,    66,   322,   233,   234,   116,   117,   130,    39,    50,
      40,   131,   132,   230,   146,   134,   300,   118,   231,   130,
     236,   238,    38,   131,   132,   291,   119,   134,   202,   203,
     122,   173,   174,   175,   176,   177,   178,   120,   204,   311,
     312,   123,   206,   284,   179,   210,    51,   183,   181,   205,
      65,   323,   326,   207,   315,   270,   211,   266,   330,   331,
     107,   315,   333,   334,   316,   324,   325,   339,   340,    89,
     341,   335,    90,    52,   303,   130,   303,   344,   345,   131,
     132,   133,   250,   134,   252,    53,   254,   255,   256,    84,
     258,   259,   260,   261,    85,    86,    87,    88,     2,    54,
     130,    59,     3,     4,   131,   132,   292,     5,   134,     6,
       7,     8,     9,    10,    11,    55,   172,   329,    12,    13,
      14,    93,   289,   290,    94,    15,    16,   173,   174,   175,
     176,   177,   178,   130,   191,    17,   192,   131,   132,   235,
     179,   134,   150,   180,   181,   151,   193,    56,   194,   173,
     174,   175,   176,   177,   178,   154,    57,    58,   155,   297,
     298,   299,   179,   338,    41,   269,   181,    42,    60,    43,
      44,    45,    46,   195,   197,   196,   198,    61,    62,    63,
      68,    69,    64,    70,    71,    73,    74,    72,    75,    76,
      78,    77,    79,    80,    81,    82,    83,    91,    92,    95,
      96,    98,    97,   100,   101,   102,   105,   109,   106,   137,
      65,   110,   111,   112,   138,   121,   128,   139,   148,   140,
     149,   152,   153,   170,   188,   156,   166,   190,   199,   158,
     201,   124,   185,   160,   208,   209,   162,   164,   165,   212,
     200,   213,   214,   215,   217,   218,   221,   224,   225,   239,
     219,   241,   248,   267,   272,   276,   277,   278,   279,   242,
     226,   243,   244,   287,   245,   262,   274,   280,   281,   282,
     296,   189,   246,   309,   283,   249,   263,   264,   303,   251,
     253,   240,   257,   286,   271,   273,   308,   315,   343,   125,
     268,   294,   285,   223,   307,   310,   295,     0,   306,   288,
     293,     0,     0,     0,     0,     0,   313,   314,     0,     0,
       0,     0,     0,     0,   318,     0,     0,     0,   319,     0,
       0,   327,   328,   332,   342
};

static const yytype_int16 yycheck[] =
{
     126,   127,    84,   165,   128,   135,   185,    89,    90,   237,
      17,    19,    53,    54,   138,   327,   328,     6,    60,     8,
      10,    11,    17,    10,    11,    23,    24,    25,    26,    19,
     342,    19,    19,   115,    18,   117,     7,   119,    46,    29,
     122,    29,    29,    53,    54,    29,    18,    54,     6,     3,
       8,    58,    59,    60,    52,    62,   284,    29,   182,    54,
     184,   187,    51,    58,    59,    60,    18,    62,   150,   151,
      18,    40,    41,    42,    43,    44,    45,    29,    18,   301,
     302,    29,    18,   262,    53,    18,    30,    56,    57,    29,
      19,   313,   314,    29,    19,   225,    29,   221,   320,   321,
      29,    19,   324,   325,    29,    10,    11,    10,    11,    60,
     332,    29,    63,    32,    19,    54,    19,   339,   340,    58,
      59,    60,   204,    62,   206,    60,   208,   209,   210,    60,
     212,   213,   214,   215,    65,    66,    67,    68,     0,     3,
      54,    38,     4,     5,    58,    59,   270,     9,    62,    11,
      12,    13,    14,    15,    16,     3,    29,   319,    20,    21,
      22,    60,    53,    54,    63,    27,    28,    40,    41,    42,
      43,    44,    45,    54,    53,    37,    55,    58,    59,    60,
      53,    62,    60,    56,    57,    63,    53,     3,    55,    40,
      41,    42,    43,    44,    45,    60,     3,     3,    63,   281,
     282,   283,    53,   329,    60,    56,    57,    63,    60,    65,
      66,    67,    68,    53,    53,    55,    55,    60,     8,    60,
      17,    17,    60,    17,    17,     3,     3,    32,    60,    60,
      39,    35,    17,    36,    60,     3,     3,    60,    60,    60,
      60,    33,    31,    60,    62,    60,    60,    17,    36,     3,
      19,    17,    17,    17,    40,    18,    17,    30,    17,    19,
      60,    60,    60,    19,     6,    60,    47,    18,    17,    60,
      17,    19,    34,    60,    18,    18,    60,    60,    60,    18,
      60,    18,    18,    18,    60,     3,    19,     3,    60,    60,
      48,     3,    18,    18,     9,     3,     3,    18,     3,    54,
      57,    54,    54,     3,    54,    36,    29,    18,    18,    18,
       3,   140,    58,    32,    18,    60,    50,    49,    19,    60,
      60,   189,    60,    50,    54,    54,    29,    19,    18,    46,
     223,   272,    60,   170,    54,   300,    60,    -1,    60,   266,
     270,    -1,    -1,    -1,    -1,    -1,    60,    60,    -1,    -1,
      -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,    60,    -1,
      -1,    60,    60,    60,    60
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    70,     0,     4,     5,     9,    11,    12,    13,    14,
      15,    16,    20,    21,    22,    27,    28,    37,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    89,    94,    95,    96,   110,     6,     8,    51,     6,
       8,    60,    63,    65,    66,    67,    68,    98,    60,     7,
       3,    30,    32,    60,     3,     3,     3,     3,     3,    38,
      60,    60,     8,    60,    60,    19,    29,    99,    17,    17,
      17,    17,    32,     3,     3,    60,    60,    35,    39,    17,
      36,    60,     3,     3,    60,    65,    66,    67,    68,    60,
      63,    60,    60,    60,    63,    60,    60,    31,    33,   101,
      60,    62,    60,    85,    88,    60,    36,    29,    99,    17,
      17,    17,    17,    99,    99,    18,    29,    18,    29,    18,
      29,    18,    18,    29,    19,    46,    97,   100,    17,    91,
      54,    58,    59,    60,    62,    93,   107,     3,    40,    30,
      19,    84,    23,    24,    25,    26,    52,    87,    17,    60,
      60,    63,    60,    60,    60,    63,    60,    99,    60,    99,
      60,    99,    60,    99,    60,    60,    47,   101,   101,    93,
      19,    90,    29,    40,    41,    42,    43,    44,    45,    53,
      56,    57,   108,    56,   108,    34,   106,    93,     6,    85,
      18,    53,    55,    53,    55,    53,    55,    53,    55,    17,
      60,    17,    99,    99,    18,    29,    18,    29,    18,    18,
      18,    29,    18,    18,    18,    18,   100,    60,     3,    48,
     102,    19,    92,    91,     3,    60,    57,    53,    54,    17,
      60,    93,   109,    53,    54,    60,    93,   107,   101,    60,
      84,     3,    54,    54,    54,    54,    58,    86,    18,    60,
      99,    60,    99,    60,    99,    99,    99,    60,    99,    99,
      99,    99,    36,    50,    49,   104,    93,    18,    90,    56,
     108,    54,     9,    54,    29,   106,     3,     3,    18,     3,
      18,    18,    18,    18,   107,    60,    50,     3,    92,    53,
      54,    60,    93,   109,    98,    60,     3,    99,    99,    99,
     106,    10,    11,    19,    29,   103,    60,    54,    29,    32,
      97,   103,   103,    60,    60,    19,    29,   105,    60,    60,
      10,    11,    29,   103,    10,    11,   103,    60,    60,   100,
     103,   103,    60,   103,   103,    29,   105,   105,   101,    10,
      11,   103,    60,    18,   103,   103,   105
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    69,    70,    70,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    81,    82,    83,    84,    84,    85,    85,    85,    86,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    88,    89,    90,    90,    91,    92,    92,    93,
      93,    93,    93,    94,    95,    96,    96,    97,    97,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,   100,   100,   101,   101,   102,   102,
     102,   102,   102,   102,   102,   103,   103,   103,   103,   103,
     103,   103,   104,   104,   104,   105,   105,   105,   106,   106,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   108,   108,   108,   108,   108,
     108,   108,   108,   109,   110
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     4,     3,     3,
       9,    10,     4,     8,     0,     3,     5,     2,     2,     1,
       1,     3,     2,     1,     3,     2,     1,     3,     2,     1,
       3,     2,     1,     7,     0,     3,     4,     0,     3,     1,
       1,     1,     1,     5,     8,     9,     7,     6,     7,     1,
       2,     4,     4,     5,     7,     5,     7,     5,     7,     4,
       5,     7,     0,     3,     5,     5,     6,     8,     6,     8,
       6,     6,     6,     8,     0,     3,     0,     3,     0,     4,
       5,     5,     6,     7,     7,     0,     3,     4,     4,     5,
       6,     6,     0,     4,     6,     0,     3,     5,     0,     3,
       3,     3,     3,     3,     5,     5,     7,     3,     4,     5,
       6,     3,     4,     3,     5,     1,     1,     1,     1,     1,
       1,     1,     2,     8,     8
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
      yyerror (scanner, YY_("syntax error: cannot back up")); \
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
                  Type, Value, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, void *scanner)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (scanner);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, void *scanner)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, scanner);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule, void *scanner)
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
                                              , scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, scanner); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, void *scanner)
{
  YYUSE (yyvaluep);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *scanner)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

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
      yychar = yylex (&yylval, scanner);
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
        case 21:
#line 188 "yacc_sql.y" /* yacc.c:1646  */
    {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1594 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 193 "yacc_sql.y" /* yacc.c:1646  */
    {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1602 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 198 "yacc_sql.y" /* yacc.c:1646  */
    {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1610 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 204 "yacc_sql.y" /* yacc.c:1646  */
    {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1618 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 210 "yacc_sql.y" /* yacc.c:1646  */
    {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1626 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 216 "yacc_sql.y" /* yacc.c:1646  */
    {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1634 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 222 "yacc_sql.y" /* yacc.c:1646  */
    {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1643 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 228 "yacc_sql.y" /* yacc.c:1646  */
    {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1651 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 234 "yacc_sql.y" /* yacc.c:1646  */
    {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1660 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 242 "yacc_sql.y" /* yacc.c:1646  */
    {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].string));
		}
#line 1669 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 247 "yacc_sql.y" /* yacc.c:1646  */
    {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_unique_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].string));
		}
#line 1678 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 255 "yacc_sql.y" /* yacc.c:1646  */
    {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1687 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 262 "yacc_sql.y" /* yacc.c:1646  */
    {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1699 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 272 "yacc_sql.y" /* yacc.c:1646  */
    {    }
#line 1705 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 277 "yacc_sql.y" /* yacc.c:1646  */
    {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-3].number), (yyvsp[-1].number));
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
			if ((yyvsp[-3].number) == INTS_NULLABLE || (yyvsp[-3].number) == FLOATS_NULLABLE || (yyvsp[-3].number) == CHARS_NULLABLE || (yyvsp[-3].number) == DATES_NULLABLE) {
				attr_info_init(&attribute, "NULL", IF_NULL, 4);
				create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
				CONTEXT->value_length++;
			}
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			
		}
#line 1726 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 294 "yacc_sql.y" /* yacc.c:1646  */
    {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[0].number), 4);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
			if ((yyvsp[0].number) == INTS_NULLABLE || (yyvsp[0].number) == FLOATS_NULLABLE || (yyvsp[0].number) == CHARS_NULLABLE || (yyvsp[0].number) == DATES_NULLABLE) {
				attr_info_init(&attribute, "NULL", IF_NULL, 4);
				create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
				CONTEXT->value_length++;
			}
		}
#line 1746 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 310 "yacc_sql.y" /* yacc.c:1646  */
    {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, CHARS, 4096);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 1757 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 318 "yacc_sql.y" /* yacc.c:1646  */
    {(yyval.number) = (yyvsp[0].number);}
#line 1763 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 321 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=INTS; }
#line 1769 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 322 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=INTS; }
#line 1775 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 323 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=INTS_NULLABLE; }
#line 1781 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 324 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=CHARS; }
#line 1787 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 325 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=CHARS; }
#line 1793 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 326 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=CHARS_NULLABLE; }
#line 1799 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 327 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=FLOATS; }
#line 1805 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 328 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=FLOATS; }
#line 1811 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 329 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=FLOATS_NULLABLE; }
#line 1817 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 330 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=DATES; }
#line 1823 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 331 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=DATES; }
#line 1829 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 332 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=DATES_NULLABLE; }
#line 1835 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 336 "yacc_sql.y" /* yacc.c:1646  */
    {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1844 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 345 "yacc_sql.y" /* yacc.c:1646  */
    {
			// CONTEXT->values[CONTEXT->value_length++] = *$6;

			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			// CONTEXT->ssql->sstr.insertion.relation_name = $3;
			// CONTEXT->ssql->sstr.insertion.value_num = CONTEXT->value_length;
			// for(i = 0; i < CONTEXT->value_length; i++){
			// 	CONTEXT->ssql->sstr.insertion.values[i] = CONTEXT->values[i];
      // }
			inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-4].string), CONTEXT->values, CONTEXT->value_length, CONTEXT->data_num);

      //临时变量清零
      CONTEXT->value_length=0;
	  CONTEXT->data_num=0;
    }
#line 1864 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 363 "yacc_sql.y" /* yacc.c:1646  */
    { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1872 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 368 "yacc_sql.y" /* yacc.c:1646  */
    {
		CONTEXT->data_num++;
	}
#line 1880 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 375 "yacc_sql.y" /* yacc.c:1646  */
    { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1888 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 380 "yacc_sql.y" /* yacc.c:1646  */
    {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1896 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 383 "yacc_sql.y" /* yacc.c:1646  */
    {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1904 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 386 "yacc_sql.y" /* yacc.c:1646  */
    {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1913 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 390 "yacc_sql.y" /* yacc.c:1646  */
    {
		// $1 = substr($1,1,strlen($1)-2);
  		// value_init_string(&CONTEXT->values[CONTEXT->value_length++], "null");
		  value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
	}
#line 1923 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 398 "yacc_sql.y" /* yacc.c:1646  */
    {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1935 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 408 "yacc_sql.y" /* yacc.c:1646  */
    {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1947 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 418 "yacc_sql.y" /* yacc.c:1646  */
    {
			// printf("do select\n");
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			// selects_append_attributes(&CONTEXT->ssql->sstr.selection, CONTEXT->attr_list, CONTEXT->attr_list_length);
			// CONTEXT->cur_select = &CONTEXT->ssql->sstr.selection;
			int stack_top = CONTEXT->attr_list_stack_top;
			selects_append_attributes(&CONTEXT->ssql->sstr.selection, CONTEXT->attr_list_stack[stack_top], CONTEXT->attr_list_length_stack[stack_top]);
			CONTEXT->attr_list_stack_top--;
			
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-5].string));

			selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);

			CONTEXT->ssql->flag=SCF_SELECT;//"select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->condition_length=0;
			CONTEXT->from_length=0;
			CONTEXT->select_length=0;
			CONTEXT->value_length = 0;
			CONTEXT->sub_select_num = 0;
			CONTEXT->sub_select_num = 0;
  			CONTEXT->attr_list_stack_top = 0;
			for (int i=0; i<MAX_NUM; i++) {
				CONTEXT->attr_list_length_stack[i] = 0;
			}
			// printf("do select end\n");
	}
#line 1981 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 448 "yacc_sql.y" /* yacc.c:1646  */
    {
		int stack_top = CONTEXT->attr_list_stack_top;
			selects_append_attributes(&CONTEXT->ssql->sstr.selection, CONTEXT->attr_list_stack[stack_top], CONTEXT->attr_list_length_stack[stack_top]);
			CONTEXT->attr_list_stack_top--;
		// selects_append_attributes(&CONTEXT->ssql->sstr.selection, CONTEXT->attr_list, CONTEXT->attr_list_length);
		// CONTEXT->cur_select = &CONTEXT->ssql->sstr.selection;
		selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-3].string));
		selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);
		CONTEXT->ssql->flag=SCF_SELECT;//"select";
		// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

		//临时变量清零
		CONTEXT->condition_length=0;
		CONTEXT->from_length=0;
		CONTEXT->select_length=0;
		CONTEXT->value_length = 0;
		CONTEXT->sub_select_num = 0;
		CONTEXT->sub_select_num = 0;
  		CONTEXT->attr_list_stack_top = 0;
		  for (int i=0; i<MAX_NUM; i++) {
				CONTEXT->attr_list_length_stack[i] = 0;
			}
	}
#line 2009 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 474 "yacc_sql.y" /* yacc.c:1646  */
    {
		selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-3].string));
	}
#line 2017 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 477 "yacc_sql.y" /* yacc.c:1646  */
    {
		selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-4].string));
	}
#line 2025 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 482 "yacc_sql.y" /* yacc.c:1646  */
    {  
		// printf("select *\n");
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
		// printf("select * end\n");
		}
#line 2040 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 492 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
		}
#line 2053 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 500 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
		}
#line 2066 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 508 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
		}
#line 2079 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 516 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			char* s=malloc(sizeof(char)*(3+strlen((yyvsp[-2].string))+3));
			strcpy(s, "MAX(");
			// strcat(s, "(");
			strcat(s, (yyvsp[-2].string));
			strcat(s, ")");
			relation_attr_init(&attr, NULL, s);
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
	}
#line 2097 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 529 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			char* s=malloc(sizeof(char)*(3+strlen((yyvsp[-2].string))+3));
			strcpy(s, "MAX(");
			// strcat(s, "(");
			strcat(s, (yyvsp[-2].string));
			strcat(s, ")");
			relation_attr_init(&attr, (yyvsp[-4].string), s);
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
	}
#line 2115 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 542 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			char* s=malloc(sizeof(char)*(3+strlen((yyvsp[-2].string))+3));
			strcpy(s, "MIN(");
			// strcat(s, "(");
			strcat(s, (yyvsp[-2].string));
			strcat(s, ")");
			relation_attr_init(&attr, NULL, s);
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
	}
#line 2133 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 555 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			char* s=malloc(sizeof(char)*(3+strlen((yyvsp[-2].string))+3));
			strcpy(s, "MIN(");
			// strcat(s, "(");
			strcat(s, (yyvsp[-2].string));
			strcat(s, ")");
			relation_attr_init(&attr, (yyvsp[-4].string), s);
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
	}
#line 2151 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 568 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			char* s=malloc(sizeof(char)*(5+strlen((yyvsp[-2].string))+3));
			strcpy(s, "COUNT(");
			// strcat(s, "(");
			strcat(s, (yyvsp[-2].string));
			strcat(s, ")");
			relation_attr_init(&attr, NULL, s);
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
	}
#line 2169 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 581 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			char* s=malloc(sizeof(char)*(5+strlen((yyvsp[-2].string))+3));
			strcpy(s, "COUNT(");
			// strcat(s, "(");
			strcat(s, (yyvsp[-2].string));
			strcat(s, ")");
			relation_attr_init(&attr, (yyvsp[-4].string), s);
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
	}
#line 2187 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 594 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			// char* s=malloc(sizeof(char)*(strlen($1)+4));
			// strcpy(s, $1);
			// strcat(s, "(*)");
			// strcat(s, $3);
			relation_attr_init(&attr, NULL, "COUNT(*)");
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
	}
#line 2204 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 606 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			char* s=malloc(sizeof(char)*(3+strlen((yyvsp[-2].string))+3));
			strcpy(s, "AVG(");
			strcat(s, (yyvsp[-2].string));
			strcat(s, ")");
			relation_attr_init(&attr, NULL, s);
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
	}
#line 2221 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 618 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			char* s=malloc(sizeof(char)*(3+strlen((yyvsp[-2].string))+3));
			strcpy(s, "AVG(");
			strcat(s, (yyvsp[-2].string));
			strcat(s, ")");
			relation_attr_init(&attr, (yyvsp[-4].string), s);
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
	}
#line 2238 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 634 "yacc_sql.y" /* yacc.c:1646  */
    {
		CONTEXT->attr_list_stack_top++;
	}
#line 2246 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 637 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 2261 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 647 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 2276 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 657 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 2291 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 667 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			char* s=malloc(sizeof(char)*(3+strlen((yyvsp[-2].string))+3));
			strcpy(s, "MAX(");
			// strcat(s, "(");
			strcat(s, (yyvsp[-2].string));
			strcat(s, ")");
			relation_attr_init(&attr, NULL, s);
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
	}
#line 2309 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 680 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			char* s=malloc(sizeof(char)*(3+strlen((yyvsp[-2].string))+3));
			strcpy(s, "MAX(");
			// strcat(s, "(");
			strcat(s, (yyvsp[-2].string));
			strcat(s, ")");
			relation_attr_init(&attr, (yyvsp[-4].string), s);
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
	}
#line 2327 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 693 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			char* s=malloc(sizeof(char)*(3+strlen((yyvsp[-2].string))+3));
			strcpy(s, "MIN(");
			// strcat(s, "(");
			strcat(s, (yyvsp[-2].string));
			strcat(s, ")");
			relation_attr_init(&attr, NULL, s);
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
	}
#line 2345 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 706 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			char* s=malloc(sizeof(char)*(3+strlen((yyvsp[-2].string))+3));
			strcpy(s, "MIN(");
			// strcat(s, "(");
			strcat(s, (yyvsp[-2].string));
			strcat(s, ")");
			relation_attr_init(&attr, (yyvsp[-4].string), s);
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
	}
#line 2363 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 719 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			char* s=malloc(sizeof(char)*(5+strlen((yyvsp[-2].string))+3));
			strcpy(s, "COUNT(");
			// strcat(s, "(");
			strcat(s, (yyvsp[-2].string));
			strcat(s, ")");
			relation_attr_init(&attr, NULL, s);
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
	}
#line 2381 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 732 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			relation_attr_init(&attr, NULL, "COUNT(*)");
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
	}
#line 2394 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 740 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			char* s=malloc(sizeof(char)*(3+strlen((yyvsp[-2].string))+3));
			strcpy(s, "AVG(");
			// strcat(s, "(");
			strcat(s, (yyvsp[-2].string));
			strcat(s, ")");
			relation_attr_init(&attr, NULL, s);
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
	}
#line 2412 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 753 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			char* s=malloc(sizeof(char)*(3+strlen((yyvsp[-2].string))+3));
			strcpy(s, "AVG(");
			// strcat(s, "(");
			strcat(s, (yyvsp[-2].string));
			strcat(s, ")");
			relation_attr_init(&attr, (yyvsp[-4].string), s);
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
	}
#line 2430 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 769 "yacc_sql.y" /* yacc.c:1646  */
    {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		  }
#line 2438 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 775 "yacc_sql.y" /* yacc.c:1646  */
    {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2446 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 782 "yacc_sql.y" /* yacc.c:1646  */
    {	
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-1].string));
			Condition condition;
			condition_init(&condition, ORDER_BY_ASC, 1, &left_attr, NULL, 1, &left_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2458 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 789 "yacc_sql.y" /* yacc.c:1646  */
    {	
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			Condition condition;
			condition_init(&condition, ORDER_BY_ASC, 1, &left_attr, NULL, 1, &left_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2470 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 796 "yacc_sql.y" /* yacc.c:1646  */
    {	
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			Condition condition;
			condition_init(&condition, ORDER_BY_DESC, 1, &left_attr, NULL, 1, &left_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2482 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 803 "yacc_sql.y" /* yacc.c:1646  */
    {	
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-3].string), (yyvsp[-1].string));
			Condition condition;
			condition_init(&condition, ORDER_BY_ASC, 1, &left_attr, NULL, 1, &left_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			}
#line 2494 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 810 "yacc_sql.y" /* yacc.c:1646  */
    {	
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Condition condition;
			condition_init(&condition, ORDER_BY_ASC, 1, &left_attr, NULL, 1, &left_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			}
#line 2506 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 817 "yacc_sql.y" /* yacc.c:1646  */
    {	
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Condition condition;
			condition_init(&condition, ORDER_BY_DESC, 1, &left_attr, NULL, 1, &left_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			}
#line 2518 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 828 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-1].string));
			Condition condition;
			condition_init(&condition, ORDER_BY_ASC, 1, &left_attr, NULL, 1, &left_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2530 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 835 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			Condition condition;
			condition_init(&condition, ORDER_BY_ASC, 1, &left_attr, NULL, 1, &left_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2542 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 842 "yacc_sql.y" /* yacc.c:1646  */
    {
		RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			Condition condition;
			condition_init(&condition, ORDER_BY_DESC, 1, &left_attr, NULL, 1, &left_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2554 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 849 "yacc_sql.y" /* yacc.c:1646  */
    {
		RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-3].string), (yyvsp[-1].string));
			Condition condition;
			condition_init(&condition, ORDER_BY_ASC, 1, &left_attr, NULL, 1, &left_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2566 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 856 "yacc_sql.y" /* yacc.c:1646  */
    {
		RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Condition condition;
			condition_init(&condition, ORDER_BY_ASC, 1, &left_attr, NULL, 1, &left_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2578 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 863 "yacc_sql.y" /* yacc.c:1646  */
    {
		RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Condition condition;
			condition_init(&condition, ORDER_BY_DESC, 1, &left_attr, NULL, 1, &left_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2590 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 874 "yacc_sql.y" /* yacc.c:1646  */
    {	
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-1].string));
			Condition condition;
			condition_init(&condition, GROUP_BY, 1, &left_attr, NULL, 1, &left_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2602 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 881 "yacc_sql.y" /* yacc.c:1646  */
    {	
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-3].string), (yyvsp[-1].string));
			Condition condition;
			condition_init(&condition, GROUP_BY, 1, &left_attr, NULL, 1, &left_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			}
#line 2614 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 892 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-1].string));
			Condition condition;
			condition_init(&condition, GROUP_BY, 1, &left_attr, NULL, 1, &left_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2626 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 899 "yacc_sql.y" /* yacc.c:1646  */
    {
		RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-3].string), (yyvsp[-1].string));
			Condition condition;
			condition_init(&condition, GROUP_BY, 1, &left_attr, NULL, 1, &left_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2638 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 911 "yacc_sql.y" /* yacc.c:1646  */
    {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2646 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 918 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name = NULL;
			// $$->left_attr.attribute_name= $1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
#line 2671 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 939 "yacc_sql.y" /* yacc.c:1646  */
    {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
#line 2695 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 959 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;

		}
#line 2719 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 979 "yacc_sql.y" /* yacc.c:1646  */
    {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp=CONTEXT->comp;
			
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;
		
		}
#line 2745 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 1001 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp=CONTEXT->comp;
			// $$->right_is_attr = 0;   //属性值
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=NULL;
			// $$->right_value =*$5;			
							
    }
#line 2770 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 1022 "yacc_sql.y" /* yacc.c:1646  */
    {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;//属性值
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;//属性
			// $$->right_attr.relation_name = $3;
			// $$->right_attr.attribute_name = $5;
									
    }
#line 2795 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 1043 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;		//属性
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;		//属性
			// $$->right_attr.relation_name=$5;
			// $$->right_attr.attribute_name=$7;
    }
#line 2818 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 1061 "yacc_sql.y" /* yacc.c:1646  */
    {
		RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
			Condition condition;
			condition_init(&condition, IS, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2832 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 1070 "yacc_sql.y" /* yacc.c:1646  */
    {
		RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-3].string));
			value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
			Condition condition;
			condition_init(&condition, IS_NOT, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2846 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 1079 "yacc_sql.y" /* yacc.c:1646  */
    {
		RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
			Condition condition;
			condition_init(&condition, IS, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2860 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 1088 "yacc_sql.y" /* yacc.c:1646  */
    {
		RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-5].string), (yyvsp[-3].string));
			value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
			Condition condition;
			condition_init(&condition, IS_NOT, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2874 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 1098 "yacc_sql.y" /* yacc.c:1646  */
    {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
			Condition condition;
			condition_init(&condition, IS, 0, NULL, left_value, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		
		}
#line 2888 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 1108 "yacc_sql.y" /* yacc.c:1646  */
    {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
			Condition condition;
			condition_init(&condition, IS_NOT, 0, NULL, left_value, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		
		}
#line 2902 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 1118 "yacc_sql.y" /* yacc.c:1646  */
    {
			// printf("where sub\n");
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Selects *right_select = &CONTEXT->sub_selects[CONTEXT->sub_select_num - 1];

			Condition condition;
			select_condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, right_select);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name = NULL;
			// $$->left_attr.attribute_name= $1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;
			// printf("where sub end\n");

		}
#line 2929 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 1141 "yacc_sql.y" /* yacc.c:1646  */
    {
			// printf("where sub\n");
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));

			Selects *right_select = &CONTEXT->sub_selects[CONTEXT->sub_select_num - 1];

			Condition condition;
			select_condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, right_select);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name = NULL;
			// $$->left_attr.attribute_name= $1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;
			// printf("where sub end\n");

		}
#line 2956 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 1166 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp = EQUAL_TO; }
#line 2962 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 1167 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp = LESS_THAN; }
#line 2968 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 1168 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp = GREAT_THAN; }
#line 2974 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 1169 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp = LESS_EQUAL; }
#line 2980 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 1170 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp = GREAT_EQUAL; }
#line 2986 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 1171 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp = NOT_EQUAL; }
#line 2992 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 1172 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp = IN; }
#line 2998 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 1173 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp = NOT_IN; }
#line 3004 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 1177 "yacc_sql.y" /* yacc.c:1646  */
    {
		// printf("sub select\n");
		// selects_init_(&(CONTEXT->sub_selects[CONTEXT->sub_select_num]));
		// selects_move__(&(CONTEXT->sub_selects[CONTEXT->sub_select_num]), &CONTEXT->ssql->sstr.selection);
		// CONTEXT->cur_select = &(CONTEXT->sub_selects[CONTEXT->sub_select_num]);
		int stack_top = CONTEXT->attr_list_stack_top;
		selects_append_attributes(&CONTEXT->sub_selects[CONTEXT->sub_select_num], CONTEXT->attr_list_stack[stack_top], CONTEXT->attr_list_length_stack[stack_top]);
		CONTEXT->attr_list_stack_top--;
		// CONTEXT->attr_list_length = 0;
		
		selects_append_relation(&CONTEXT->sub_selects[CONTEXT->sub_select_num], (yyvsp[-3].string));

		selects_append_conditions(&CONTEXT->sub_selects[CONTEXT->sub_select_num], CONTEXT->conditions, CONTEXT->condition_length);

		CONTEXT->ssql->flag=SCF_SELECT;
		CONTEXT->sub_select_num++;
		// printf("subselect end\n");
	}
#line 3027 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 1199 "yacc_sql.y" /* yacc.c:1646  */
    {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 3036 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;


#line 3040 "yacc_sql.tab.c" /* yacc.c:1646  */
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
      yyerror (scanner, YY_("syntax error"));
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
        yyerror (scanner, yymsgp);
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
                      yytoken, &yylval, scanner);
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
                  yystos[yystate], yyvsp, scanner);
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
  yyerror (scanner, YY_("memory exhausted"));
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
                  yytoken, &yylval, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, scanner);
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
#line 1204 "yacc_sql.y" /* yacc.c:1906  */

//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, Query *sqls){
	ParserContext context;
	memset(&context, 0, sizeof(context));

	yyscan_t scanner;
	yylex_init_extra(&context, &scanner);
	context.ssql = sqls;
	scan_string(s, scanner);
	int result = yyparse(scanner);
	yylex_destroy(scanner);
	return result;
}
