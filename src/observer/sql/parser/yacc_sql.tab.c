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
  
  CompOp comp[MAX_NUM];
  char id[MAX_NUM];
  size_t data_num;
  size_t sub_select_num;
  RelAttr attr_list_stack[MAX_NUM][MAX_NUM];
  size_t attr_list_length_stack[MAX_NUM];
  size_t attr_list_stack_top;
	Value value_list_stack[MAX_NUM][MAX_NUM];
	size_t value_list_length_stack[MAX_NUM];
  size_t value_list_stack_top;
  Condition condition_list_stack[MAX_NUM][MAX_NUM];
  size_t condition_list_length_stack[MAX_NUM];
  size_t condition_list_stack_top;
 size_t comp_length;

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
  for (int i=0; i<MAX_NUM; i++) {
	  context->attr_list_length_stack[i] = 0;
  }
//   size_t value_list_length_stack[MAX_NUM];
  context->value_list_stack_top = 0;
	for (int i=0; i<MAX_NUM; i++) {
	  context->value_list_length_stack[i] = 0;
  }
//   size_t condition_list_length_stack[MAX_NUM];
  context->condition_list_stack_top = 0;
  for (int i=0; i<MAX_NUM; i++) {
	  context->condition_list_length_stack[i] = 0;
  }
 context->comp_length=0;
  printf("parse sql failed. error=%s", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)


#line 156 "yacc_sql.tab.c" /* yacc.c:339  */

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
#line 153 "yacc_sql.y" /* yacc.c:355  */

  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  char *string;
  int number;
  float floats;
	char *position;

#line 275 "yacc_sql.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (void *scanner);

#endif /* !YY_YY_YACC_SQL_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 291 "yacc_sql.tab.c" /* yacc.c:358  */

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
#define YYLAST   387

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  69
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  150
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  359

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
       0,   184,   184,   186,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   210,   215,   220,   226,   232,   238,   244,   250,   256,
     263,   268,   274,   276,   280,   287,   294,   303,   305,   309,
     326,   342,   351,   354,   355,   356,   357,   358,   359,   360,
     361,   362,   363,   364,   365,   368,   377,   394,   396,   401,
     406,   408,   413,   416,   419,   423,   430,   440,   450,   494,
     536,   539,   544,   554,   562,   570,   578,   591,   604,   617,
     630,   643,   656,   668,   680,   696,   699,   709,   719,   729,
     742,   755,   768,   781,   794,   802,   815,   829,   831,   836,
     840,   845,   847,   860,   870,   880,   890,   900,   913,   917,
     927,   937,   947,   957,   967,   979,   981,   991,  1004,  1008,
    1018,  1032,  1036,  1042,  1066,  1089,  1112,  1137,  1161,  1185,
    1207,  1219,  1231,  1243,  1255,  1268,  1281,  1298,  1314,  1341,
    1366,  1394,  1395,  1396,  1397,  1398,  1399,  1400,  1401,  1405,
    1428
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
  "id_def_list", "id_def", "drop_index", "create_table", "attr_def_list",
  "attr_def", "number", "type", "ID_get", "insert", "muti_value_list",
  "muti_value", "value_list", "value", "delete", "update", "select",
  "join_list", "select_attr", "attr_list", "rel_list", "where", "order_by",
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

#define YYPACT_NINF -249

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-249)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -249,   137,  -249,    19,   116,   171,   -36,    38,    61,    29,
      59,    44,   120,   125,   129,   163,   179,    73,  -249,  -249,
    -249,  -249,  -249,  -249,  -249,  -249,  -249,  -249,  -249,  -249,
    -249,  -249,  -249,  -249,  -249,  -249,    94,   133,   191,   162,
     164,     7,  -249,   208,   211,   213,   215,   212,   242,   243,
    -249,   187,   188,   214,  -249,  -249,  -249,  -249,  -249,   216,
     233,   217,   192,   248,   251,   175,    56,  -249,   196,   197,
      84,   198,   199,  -249,  -249,   229,   228,   202,   201,   204,
     205,   230,  -249,  -249,    69,   250,   252,   253,   254,   249,
     249,     5,    10,    11,   255,    14,     3,   257,    -6,   269,
     235,   246,  -249,   258,    -5,   261,   219,   100,  -249,   220,
     221,   131,   222,  -249,  -249,   249,   223,   249,   224,   249,
     225,  -249,   249,   226,   227,   241,   228,   228,   138,   270,
     281,  -249,  -249,  -249,   127,  -249,   145,   259,   176,  -249,
     138,   285,   204,   274,    85,    90,   150,   151,  -249,   277,
     236,   278,   249,   249,    26,    33,   279,   280,    63,  -249,
     282,  -249,   283,  -249,   284,  -249,   286,   287,   239,   300,
     260,   288,   257,   302,   171,   256,  -249,  -249,  -249,  -249,
    -249,  -249,   262,    30,  -249,    13,   108,   119,    -6,  -249,
      -3,   228,   263,   258,   306,   264,  -249,   266,  -249,   267,
    -249,   268,  -249,   271,  -249,   291,   236,  -249,  -249,   249,
     265,   249,   272,   249,   249,   249,   273,   249,   249,   249,
     249,  -249,   275,  -249,   276,   289,   138,   294,   270,  -249,
     292,   170,  -249,   290,  -249,  -249,  -249,  -249,   293,  -249,
     298,  -249,   259,   299,  -249,   310,   311,  -249,  -249,  -249,
    -249,  -249,  -249,  -249,   297,   236,   312,   291,  -249,   313,
    -249,   316,  -249,  -249,  -249,   317,  -249,  -249,  -249,  -249,
      -6,   295,   296,   314,   288,  -249,  -249,   301,   122,    20,
    -249,  -249,   303,  -249,   304,  -249,  -249,  -249,   291,   333,
     319,   249,   249,   249,   259,    31,   305,  -249,  -249,   287,
     308,  -249,   320,  -249,  -249,  -249,  -249,  -249,  -249,   336,
    -249,  -249,  -249,   307,   321,   321,   309,   315,  -249,    80,
     228,  -249,   318,  -249,  -249,  -249,  -249,    76,   102,   322,
     323,  -249,   324,  -249,   321,   321,   325,  -249,   321,   321,
    -249,    91,   326,  -249,  -249,  -249,   107,  -249,  -249,   327,
    -249,  -249,   321,   321,  -249,   326,  -249,  -249,  -249
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
       0,    85,    72,     0,     0,     0,     0,     0,     0,     0,
      23,     0,     0,     0,    24,    25,    26,    22,    21,     0,
       0,     0,     0,     0,     0,     0,     0,    73,     0,     0,
       0,     0,     0,    29,    28,     0,    99,     0,     0,     0,
       0,     0,    27,    35,    85,     0,     0,     0,     0,    85,
      85,     0,     0,     0,     0,     0,    97,     0,     0,     0,
       0,     0,    55,    37,     0,     0,     0,     0,    86,     0,
       0,     0,     0,    74,    75,    85,     0,    85,     0,    85,
       0,    82,    85,     0,     0,     0,    99,    99,     0,    57,
       0,    65,    62,    63,     0,    64,     0,   121,     0,    66,
       0,     0,     0,     0,    43,    46,    49,    52,    41,    40,
       0,     0,    85,    85,     0,     0,     0,     0,     0,    76,
       0,    78,     0,    80,     0,    83,     0,    97,     0,     0,
     101,    60,     0,     0,     0,     0,   141,   142,   143,   144,
     145,   146,     0,     0,   147,     0,     0,     0,     0,   100,
       0,    99,     0,    37,     0,     0,    45,     0,    48,     0,
      51,     0,    54,     0,    34,    32,     0,    87,    88,    85,
       0,    85,     0,    85,    85,    85,     0,    85,    85,    85,
      85,    98,     0,    69,     0,   115,     0,     0,    57,    56,
       0,     0,   148,     0,   130,   125,   123,   136,     0,   134,
     126,   124,   121,   138,   140,     0,     0,    38,    36,    44,
      47,    50,    53,    42,     0,     0,     0,    32,    89,     0,
      91,     0,    93,    94,    95,     0,    77,    79,    81,    84,
       0,     0,     0,     0,    60,    59,    58,     0,     0,     0,
     131,   135,     0,   122,     0,    67,   150,    39,    32,     0,
       0,    85,    85,    85,   121,   108,     0,    68,    61,    97,
       0,   132,     0,   127,   137,   128,   139,    33,    30,     0,
      90,    92,    96,    70,   108,   108,     0,     0,   102,   118,
      99,   133,     0,    31,    71,   103,   104,   108,   108,     0,
       0,   116,     0,   129,   108,   108,     0,   109,   108,   108,
     105,   118,   118,   149,   110,   111,   108,   106,   107,     0,
     119,   117,   108,   108,   112,   118,   113,   114,   120
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -249,  -249,  -249,  -249,  -249,  -249,  -249,  -249,  -249,  -249,
    -249,  -249,  -249,  -242,  -197,  -249,  -249,   148,   206,  -249,
    -249,  -249,  -249,   115,   178,    77,  -124,  -249,  -249,  -249,
      39,   180,   -84,  -160,  -125,  -249,  -238,  -249,  -248,  -229,
    -185,  -128,  -173,  -249
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   256,   205,    29,    30,   143,   103,   254,
     149,   104,    31,   173,   129,   227,   136,    32,    33,    34,
     126,    47,    67,   127,    99,   225,   318,   273,   331,   189,
     137,   185,   138,    35
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
     108,   169,   170,   242,   171,   113,   114,   221,   187,   257,
     190,   130,   237,   283,   130,   290,   191,   244,   144,   145,
     146,   147,   124,   115,    48,    36,    65,    37,   117,   119,
     130,   159,   122,   161,   116,   163,    66,   130,   165,   118,
     120,   314,   315,   123,   209,    49,   307,   148,   131,   125,
     316,   211,   132,   133,   134,   210,   135,   243,   288,    51,
     317,   236,   212,   241,    50,   313,   245,   131,   207,   208,
      38,   132,   133,   235,   131,   135,   325,   326,   132,   133,
     302,   215,   135,   233,   234,   294,   334,   335,    65,   337,
     340,    52,   216,   350,   351,   316,   344,   345,   107,   329,
     347,   348,   274,   279,    53,   336,   304,   358,   354,   330,
     329,    59,   338,   339,   356,   357,    89,   352,   353,    90,
     349,   316,    39,    54,    40,   258,   316,   260,    55,   262,
     263,   264,    56,   266,   267,   268,   269,     2,   195,   320,
     196,     3,     4,   197,    93,   198,     5,    94,     6,     7,
       8,     9,    10,    11,    60,   303,   175,    12,    13,    14,
     152,   238,   239,   153,    15,    16,    57,   176,   177,   178,
     179,   180,   181,   131,    17,   300,   301,   132,   133,   240,
     182,   135,    58,   183,   184,   176,   177,   178,   179,   180,
     181,   156,   131,    61,   157,   332,   132,   133,   182,    62,
     135,   186,   184,   199,   201,   200,   202,   310,   311,   312,
     176,   177,   178,   179,   180,   181,   176,   177,   178,   179,
     180,   181,    63,   182,    64,    68,   278,   184,    69,   182,
      70,    41,    71,   184,    42,    84,    43,    44,    45,    46,
      85,    86,    87,    88,    72,    73,    74,    75,    76,    77,
      79,    82,    81,    80,    83,    78,    91,    92,    95,    96,
      97,    98,   100,   101,   102,   105,   106,   109,    65,   110,
     111,   112,   139,   121,   128,   140,   141,   142,   150,   151,
     154,   155,   158,   160,   162,   164,   166,   167,   168,   172,
     174,   192,   194,   188,   203,   206,   204,   213,   214,   222,
     217,   218,   219,   223,   220,   229,   124,   226,   224,   248,
     255,   270,   275,   285,   286,   287,   231,   297,   249,   232,
     250,   251,   252,   246,   277,   259,   271,   282,   284,   253,
     289,   291,   261,   265,   292,   293,   308,   309,   272,   323,
     316,   247,   343,   276,   280,   329,   296,   281,   193,   322,
     228,   298,   324,   125,   230,   295,     0,     0,     0,     0,
       0,   299,   321,   305,   306,   319,     0,     0,     0,   327,
       0,     0,     0,     0,     0,   328,     0,     0,   333,     0,
       0,     0,   341,   342,     0,   346,     0,   355
};

static const yytype_int16 yycheck[] =
{
      84,   126,   127,   188,   128,    89,    90,   167,   136,   206,
     138,    17,   185,   242,    17,   257,   140,   190,    23,    24,
      25,    26,    19,    18,    60,     6,    19,     8,    18,    18,
      17,   115,    18,   117,    29,   119,    29,    17,   122,    29,
      29,    10,    11,    29,    18,     7,   288,    52,    54,    46,
      19,    18,    58,    59,    60,    29,    62,    60,   255,    30,
      29,   185,    29,   187,     3,   294,   191,    54,   152,   153,
      51,    58,    59,    60,    54,    62,   314,   315,    58,    59,
      60,    18,    62,    53,    54,   270,    10,    11,    19,   327,
     328,    32,    29,   341,   342,    19,   334,   335,    29,    19,
     338,   339,   226,   231,    60,    29,   279,   355,   346,    29,
      19,    38,    10,    11,   352,   353,    60,    10,    11,    63,
      29,    19,     6,     3,     8,   209,    19,   211,     3,   213,
     214,   215,     3,   217,   218,   219,   220,     0,    53,   299,
      55,     4,     5,    53,    60,    55,     9,    63,    11,    12,
      13,    14,    15,    16,    60,   279,    29,    20,    21,    22,
      60,    53,    54,    63,    27,    28,     3,    40,    41,    42,
      43,    44,    45,    54,    37,    53,    54,    58,    59,    60,
      53,    62,     3,    56,    57,    40,    41,    42,    43,    44,
      45,    60,    54,    60,    63,   320,    58,    59,    53,     8,
      62,    56,    57,    53,    53,    55,    55,   291,   292,   293,
      40,    41,    42,    43,    44,    45,    40,    41,    42,    43,
      44,    45,    60,    53,    60,    17,    56,    57,    17,    53,
      17,    60,    17,    57,    63,    60,    65,    66,    67,    68,
      65,    66,    67,    68,    32,     3,     3,    60,    60,    35,
      17,     3,    60,    36,     3,    39,    60,    60,    60,    60,
      31,    33,    60,    62,    60,    60,    36,    17,    19,    17,
      17,    17,     3,    18,    17,    40,    30,    19,    17,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    47,    19,
       9,     6,    18,    34,    17,    17,    60,    18,    18,    60,
      18,    18,    18,     3,    18,     3,    19,    19,    48,     3,
      19,    36,    18,     3,     3,    18,    60,     3,    54,    57,
      54,    54,    54,    60,    32,    60,    50,    29,    29,    58,
      18,    18,    60,    60,    18,    18,     3,    18,    49,     3,
      19,   193,    18,   228,    54,    19,    50,    54,   142,    29,
     172,   274,   313,    46,   174,    60,    -1,    -1,    -1,    -1,
      -1,    60,    54,    60,    60,    60,    -1,    -1,    -1,    60,
      -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,    60,    -1,
      -1,    -1,    60,    60,    -1,    60,    -1,    60
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    70,     0,     4,     5,     9,    11,    12,    13,    14,
      15,    16,    20,    21,    22,    27,    28,    37,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    84,
      85,    91,    96,    97,    98,   112,     6,     8,    51,     6,
       8,    60,    63,    65,    66,    67,    68,   100,    60,     7,
       3,    30,    32,    60,     3,     3,     3,     3,     3,    38,
      60,    60,     8,    60,    60,    19,    29,   101,    17,    17,
      17,    17,    32,     3,     3,    60,    60,    35,    39,    17,
      36,    60,     3,     3,    60,    65,    66,    67,    68,    60,
      63,    60,    60,    60,    63,    60,    60,    31,    33,   103,
      60,    62,    60,    87,    90,    60,    36,    29,   101,    17,
      17,    17,    17,   101,   101,    18,    29,    18,    29,    18,
      29,    18,    18,    29,    19,    46,    99,   102,    17,    93,
      17,    54,    58,    59,    60,    62,    95,   109,   111,     3,
      40,    30,    19,    86,    23,    24,    25,    26,    52,    89,
      17,    60,    60,    63,    60,    60,    60,    63,    60,   101,
      60,   101,    60,   101,    60,   101,    60,    60,    47,   103,
     103,    95,    19,    92,     9,    29,    40,    41,    42,    43,
      44,    45,    53,    56,    57,   110,    56,   110,    34,   108,
     110,    95,     6,    87,    18,    53,    55,    53,    55,    53,
      55,    53,    55,    17,    60,    83,    17,   101,   101,    18,
      29,    18,    29,    18,    18,    18,    29,    18,    18,    18,
      18,   102,    60,     3,    48,   104,    19,    94,    93,     3,
     100,    60,    57,    53,    54,    60,    95,   111,    53,    54,
      60,    95,   109,    60,   111,   103,    60,    86,     3,    54,
      54,    54,    54,    58,    88,    19,    82,    83,   101,    60,
     101,    60,   101,   101,   101,    60,   101,   101,   101,   101,
      36,    50,    49,   106,    95,    18,    92,    32,    56,   110,
      54,    54,    29,   108,    29,     3,     3,    18,    83,    18,
      82,    18,    18,    18,   109,    60,    50,     3,    94,    60,
      53,    54,    60,    95,   111,    60,    60,    82,     3,    18,
     101,   101,   101,   108,    10,    11,    19,    29,   105,    60,
     102,    54,    29,     3,    99,   105,   105,    60,    60,    19,
      29,   107,   103,    60,    10,    11,    29,   105,    10,    11,
     105,    60,    60,    18,   105,   105,    60,   105,   105,    29,
     107,   107,    10,    11,   105,    60,   105,   105,   107
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    69,    70,    70,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    81,    82,    82,    83,    84,    85,    86,    86,    87,
      87,    87,    88,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    90,    91,    92,    92,    93,
      94,    94,    95,    95,    95,    95,    96,    97,    98,    98,
      99,    99,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   102,   102,   103,
     103,   104,   104,   104,   104,   104,   104,   104,   105,   105,
     105,   105,   105,   105,   105,   106,   106,   106,   107,   107,
     107,   108,   108,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   110,   110,   110,   110,   110,   110,   110,   110,   111,
     112
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     4,     3,     3,
      10,    11,     0,     3,     1,     4,     8,     0,     3,     5,
       2,     2,     1,     1,     3,     2,     1,     3,     2,     1,
       3,     2,     1,     3,     2,     1,     7,     0,     3,     4,
       0,     3,     1,     1,     1,     1,     5,     8,     9,     7,
       6,     7,     1,     2,     4,     4,     5,     7,     5,     7,
       5,     7,     4,     5,     7,     0,     3,     5,     5,     6,
       8,     6,     8,     6,     6,     6,     8,     0,     3,     0,
       3,     0,     4,     5,     5,     6,     7,     7,     0,     3,
       4,     4,     5,     6,     6,     0,     4,     6,     0,     3,
       5,     0,     3,     3,     3,     3,     3,     5,     5,     7,
       3,     4,     5,     6,     3,     4,     3,     5,     3,     5,
       3,     1,     1,     1,     1,     1,     1,     1,     2,     8,
       8
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
#line 210 "yacc_sql.y" /* yacc.c:1646  */
    {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1626 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 215 "yacc_sql.y" /* yacc.c:1646  */
    {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1634 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 220 "yacc_sql.y" /* yacc.c:1646  */
    {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1642 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 226 "yacc_sql.y" /* yacc.c:1646  */
    {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1650 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 232 "yacc_sql.y" /* yacc.c:1646  */
    {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1658 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 238 "yacc_sql.y" /* yacc.c:1646  */
    {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1666 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 244 "yacc_sql.y" /* yacc.c:1646  */
    {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1675 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 250 "yacc_sql.y" /* yacc.c:1646  */
    {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1683 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 256 "yacc_sql.y" /* yacc.c:1646  */
    {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1692 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 264 "yacc_sql.y" /* yacc.c:1646  */
    {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string));
		}
#line 1701 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 269 "yacc_sql.y" /* yacc.c:1646  */
    {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_unique_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string));
		}
#line 1710 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 276 "yacc_sql.y" /* yacc.c:1646  */
    {    }
#line 1716 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 281 "yacc_sql.y" /* yacc.c:1646  */
    {
			create_index_append_attribute(&CONTEXT->ssql->sstr.create_index,(yyvsp[0].string));
		}
#line 1724 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 288 "yacc_sql.y" /* yacc.c:1646  */
    {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1733 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 295 "yacc_sql.y" /* yacc.c:1646  */
    {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1745 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 305 "yacc_sql.y" /* yacc.c:1646  */
    {    }
#line 1751 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 310 "yacc_sql.y" /* yacc.c:1646  */
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
#line 1772 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 327 "yacc_sql.y" /* yacc.c:1646  */
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
#line 1792 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 343 "yacc_sql.y" /* yacc.c:1646  */
    {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, CHARS, 4096);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 1803 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 351 "yacc_sql.y" /* yacc.c:1646  */
    {(yyval.number) = (yyvsp[0].number);}
#line 1809 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 354 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=INTS; }
#line 1815 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 355 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=INTS; }
#line 1821 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 356 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=INTS_NULLABLE; }
#line 1827 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 357 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=CHARS; }
#line 1833 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 358 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=CHARS; }
#line 1839 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 359 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=CHARS_NULLABLE; }
#line 1845 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 360 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=FLOATS; }
#line 1851 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 361 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=FLOATS; }
#line 1857 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 362 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=FLOATS_NULLABLE; }
#line 1863 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 363 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=DATES; }
#line 1869 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 364 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=DATES; }
#line 1875 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 365 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=DATES_NULLABLE; }
#line 1881 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 369 "yacc_sql.y" /* yacc.c:1646  */
    {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1890 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 378 "yacc_sql.y" /* yacc.c:1646  */
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
#line 1910 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 396 "yacc_sql.y" /* yacc.c:1646  */
    { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1918 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 401 "yacc_sql.y" /* yacc.c:1646  */
    {
		CONTEXT->data_num++;
	}
#line 1926 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 408 "yacc_sql.y" /* yacc.c:1646  */
    { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1934 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 413 "yacc_sql.y" /* yacc.c:1646  */
    {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1942 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 416 "yacc_sql.y" /* yacc.c:1646  */
    {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1950 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 419 "yacc_sql.y" /* yacc.c:1646  */
    {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1959 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 423 "yacc_sql.y" /* yacc.c:1646  */
    {
		// $1 = substr($1,1,strlen($1)-2);
  		// value_init_string(&CONTEXT->values[CONTEXT->value_length++], "null");
		  value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
	}
#line 1969 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 431 "yacc_sql.y" /* yacc.c:1646  */
    {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1981 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 441 "yacc_sql.y" /* yacc.c:1646  */
    {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1993 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 451 "yacc_sql.y" /* yacc.c:1646  */
    {
			printf("do select\n");
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			// selects_append_attributes(&CONTEXT->ssql->sstr.selection, CONTEXT->attr_list, CONTEXT->attr_list_length);
			// CONTEXT->cur_select = &CONTEXT->ssql->sstr.selection;
			int stack_top = CONTEXT->attr_list_stack_top;
			printf("select: attr stack_top:%d\n", stack_top);
			selects_append_attributes(&CONTEXT->ssql->sstr.selection, CONTEXT->attr_list_stack[stack_top], CONTEXT->attr_list_length_stack[stack_top]);
			CONTEXT->attr_list_stack_top--;
			
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-5].string));
			stack_top = CONTEXT->condition_list_stack_top;
			printf("select:stack_top:%d\n", stack_top);
			selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->condition_list_stack[stack_top], CONTEXT->condition_list_length_stack[stack_top]);
			// selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_list_stack_top--;
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
			//   size_t value_list_length_stack[MAX_NUM];
			CONTEXT->value_list_stack_top = 0;
			for (int i=0; i<MAX_NUM; i++) {
				CONTEXT->value_list_length_stack[i] = 0;
			}
			//   size_t condition_list_length_stack[MAX_NUM];
			CONTEXT->condition_list_stack_top = 0;
			for (int i=0; i<MAX_NUM; i++) {
				CONTEXT->condition_list_length_stack[i] = 0;
			}
			CONTEXT->comp_length=0;
			printf("do select end\n");
	}
#line 2041 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 495 "yacc_sql.y" /* yacc.c:1646  */
    {
		printf("do select end\n");
		int stack_top = CONTEXT->attr_list_stack_top;
			selects_append_attributes(&CONTEXT->ssql->sstr.selection, CONTEXT->attr_list_stack[stack_top], CONTEXT->attr_list_length_stack[stack_top]);
			CONTEXT->attr_list_stack_top--;
		// selects_append_attributes(&CONTEXT->ssql->sstr.selection, CONTEXT->attr_list, CONTEXT->attr_list_length);
		// CONTEXT->cur_select = &CONTEXT->ssql->sstr.selection;
		selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-3].string));
		stack_top = CONTEXT->condition_list_stack_top;
		printf("select:stack_top:%d\n", stack_top);
		selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->condition_list_stack[stack_top], CONTEXT->condition_list_length_stack[stack_top]);
		CONTEXT->condition_list_stack_top--;
		// selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);
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
		CONTEXT->value_list_stack_top = 0;
			for (int i=0; i<MAX_NUM; i++) {
				CONTEXT->value_list_length_stack[i] = 0;
			}
			//   size_t condition_list_length_stack[MAX_NUM];
			CONTEXT->condition_list_stack_top = 0;
			for (int i=0; i<MAX_NUM; i++) {
				CONTEXT->condition_list_length_stack[i] = 0;
			}
			CONTEXT->comp_length=0;
	}
#line 2084 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 536 "yacc_sql.y" /* yacc.c:1646  */
    {
		selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-3].string));
	}
#line 2092 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 539 "yacc_sql.y" /* yacc.c:1646  */
    {
		selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-4].string));
	}
#line 2100 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 544 "yacc_sql.y" /* yacc.c:1646  */
    {  
		printf("select *\n");
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
		// printf("select * end\n");
		}
#line 2115 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 554 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
		}
#line 2128 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 562 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
		}
#line 2141 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 570 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
		}
#line 2154 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 578 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2172 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 591 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2190 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 604 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2208 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 617 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2226 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 630 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2244 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 643 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2262 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 656 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2279 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 668 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2296 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 680 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2313 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 696 "yacc_sql.y" /* yacc.c:1646  */
    {
		CONTEXT->attr_list_stack_top++;
	}
#line 2321 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 699 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2336 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 709 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2351 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 719 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2366 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 729 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2384 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 742 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2402 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 755 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2420 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 768 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2438 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 781 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2456 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 794 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			relation_attr_init(&attr, NULL, "COUNT(*)");
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
	}
#line 2469 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 802 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2487 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 815 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2505 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 831 "yacc_sql.y" /* yacc.c:1646  */
    {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		  }
#line 2513 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 836 "yacc_sql.y" /* yacc.c:1646  */
    {
		CONTEXT->condition_list_stack_top++;
		printf("condition_list: condition_list_stack_top++: %d\n", CONTEXT->condition_list_stack_top);
	}
#line 2522 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 840 "yacc_sql.y" /* yacc.c:1646  */
    {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2530 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 847 "yacc_sql.y" /* yacc.c:1646  */
    {	
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-1].string));
			Condition condition;
			condition_init(&condition, ORDER_BY_ASC, 1, &left_attr, NULL, 1, &left_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									// CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									// &condition);
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
	}
#line 2548 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 860 "yacc_sql.y" /* yacc.c:1646  */
    {	
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			Condition condition;
			condition_init(&condition, ORDER_BY_ASC, 1, &left_attr, NULL, 1, &left_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
	}
#line 2563 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 870 "yacc_sql.y" /* yacc.c:1646  */
    {	
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			Condition condition;
			condition_init(&condition, ORDER_BY_DESC, 1, &left_attr, NULL, 1, &left_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
	}
#line 2578 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 880 "yacc_sql.y" /* yacc.c:1646  */
    {	
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-3].string), (yyvsp[-1].string));
			Condition condition;
			condition_init(&condition, ORDER_BY_ASC, 1, &left_attr, NULL, 1, &left_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
			}
#line 2593 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 890 "yacc_sql.y" /* yacc.c:1646  */
    {	
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Condition condition;
			condition_init(&condition, ORDER_BY_ASC, 1, &left_attr, NULL, 1, &left_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
			}
#line 2608 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 900 "yacc_sql.y" /* yacc.c:1646  */
    {	
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Condition condition;
			condition_init(&condition, ORDER_BY_DESC, 1, &left_attr, NULL, 1, &left_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
			}
#line 2623 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 913 "yacc_sql.y" /* yacc.c:1646  */
    {
		CONTEXT->condition_list_stack_top++;
		printf("condition_list: condition_list_stack_top++: %d\n", CONTEXT->condition_list_stack_top);
	}
#line 2632 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 917 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-1].string));
			Condition condition;
			condition_init(&condition, ORDER_BY_ASC, 1, &left_attr, NULL, 1, &left_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
	}
#line 2647 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 927 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			Condition condition;
			condition_init(&condition, ORDER_BY_ASC, 1, &left_attr, NULL, 1, &left_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
	}
#line 2662 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 937 "yacc_sql.y" /* yacc.c:1646  */
    {
		RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			Condition condition;
			condition_init(&condition, ORDER_BY_DESC, 1, &left_attr, NULL, 1, &left_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
	}
#line 2677 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 947 "yacc_sql.y" /* yacc.c:1646  */
    {
		RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-3].string), (yyvsp[-1].string));
			Condition condition;
			condition_init(&condition, ORDER_BY_ASC, 1, &left_attr, NULL, 1, &left_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
	}
#line 2692 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 957 "yacc_sql.y" /* yacc.c:1646  */
    {
		RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Condition condition;
			condition_init(&condition, ORDER_BY_ASC, 1, &left_attr, NULL, 1, &left_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
	}
#line 2707 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 967 "yacc_sql.y" /* yacc.c:1646  */
    {
		RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Condition condition;
			condition_init(&condition, ORDER_BY_DESC, 1, &left_attr, NULL, 1, &left_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
	}
#line 2722 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 981 "yacc_sql.y" /* yacc.c:1646  */
    {	
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-1].string));
			Condition condition;
			condition_init(&condition, GROUP_BY, 1, &left_attr, NULL, 1, &left_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
	}
#line 2737 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 991 "yacc_sql.y" /* yacc.c:1646  */
    {	
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-3].string), (yyvsp[-1].string));
			Condition condition;
			condition_init(&condition, GROUP_BY, 1, &left_attr, NULL, 1, &left_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
			}
#line 2752 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 1004 "yacc_sql.y" /* yacc.c:1646  */
    {
		CONTEXT->condition_list_stack_top++;
		printf("condition_list: condition_list_stack_top++: %d\n", CONTEXT->condition_list_stack_top);
	}
#line 2761 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 1008 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-1].string));
			Condition condition;
			condition_init(&condition, GROUP_BY, 1, &left_attr, NULL, 1, &left_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
	}
#line 2776 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 1018 "yacc_sql.y" /* yacc.c:1646  */
    {
		RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-3].string), (yyvsp[-1].string));
			Condition condition;
			condition_init(&condition, GROUP_BY, 1, &left_attr, NULL, 1, &left_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
	}
#line 2791 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 1032 "yacc_sql.y" /* yacc.c:1646  */
    {
		// CONTEXT->condition_list_stack_top++;
		// printf("condition_list: condition_list_stack_top++: %d\n", CONTEXT->condition_list_stack_top);
	}
#line 2800 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 1036 "yacc_sql.y" /* yacc.c:1646  */
    {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2808 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 1043 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp[CONTEXT->comp_length-1], 1, &left_attr, NULL, 0, NULL, right_value);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name = NULL;
			// $$->left_attr.attribute_name= $1;
			// $$->comp = CONTEXT->comp[CONTEXT->comp_length-1];
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
#line 2836 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 1067 "yacc_sql.y" /* yacc.c:1646  */
    {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp[(CONTEXT->comp_length--)-1], 0, NULL, left_value, 0, NULL, right_value);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp = CONTEXT->comp[CONTEXT->comp_length-1];
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
#line 2863 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 1090 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp[(CONTEXT->comp_length--)-1], 1, &left_attr, NULL, 1, &right_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=$1;
			// $$->comp = CONTEXT->comp[(CONTEXT->comp_length--)-1];
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;

		}
#line 2890 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 1113 "yacc_sql.y" /* yacc.c:1646  */
    {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp[(CONTEXT->comp_length--)-1], 0, NULL, left_value, 1, &right_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp=CONTEXT->comp[(CONTEXT->comp_length--)-1];
			
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;
		
		}
#line 2919 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 1138 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp[(CONTEXT->comp_length--)-1], 1, &left_attr, NULL, 0, NULL, right_value);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp=CONTEXT->comp[(CONTEXT->comp_length--)-1];
			// $$->right_is_attr = 0;   //属性值
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=NULL;
			// $$->right_value =*$5;			
							
    }
#line 2947 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 1162 "yacc_sql.y" /* yacc.c:1646  */
    {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp[(CONTEXT->comp_length--)-1], 0, NULL, left_value, 1, &right_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;//属性值
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp =CONTEXT->comp[(CONTEXT->comp_length--)-1];
			// $$->right_is_attr = 1;//属性
			// $$->right_attr.relation_name = $3;
			// $$->right_attr.attribute_name = $5;
									
    }
#line 2975 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 1186 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp[(CONTEXT->comp_length--)-1], 1, &left_attr, NULL, 1, &right_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;		//属性
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp =CONTEXT->comp[(CONTEXT->comp_length--)-1];
			// $$->right_is_attr = 1;		//属性
			// $$->right_attr.relation_name=$5;
			// $$->right_attr.attribute_name=$7;
    }
#line 3001 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 1207 "yacc_sql.y" /* yacc.c:1646  */
    {
		RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
			Condition condition;
			condition_init(&condition, IS, 1, &left_attr, NULL, 0, NULL, right_value);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
	}
#line 3018 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 1219 "yacc_sql.y" /* yacc.c:1646  */
    {
		RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-3].string));
			value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
			Condition condition;
			condition_init(&condition, IS_NOT, 1, &left_attr, NULL, 0, NULL, right_value);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
	}
#line 3035 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 1231 "yacc_sql.y" /* yacc.c:1646  */
    {
		RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
			Condition condition;
			condition_init(&condition, IS, 1, &left_attr, NULL, 0, NULL, right_value);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
	}
#line 3052 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 1243 "yacc_sql.y" /* yacc.c:1646  */
    {
		RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-5].string), (yyvsp[-3].string));
			value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
			Condition condition;
			condition_init(&condition, IS_NOT, 1, &left_attr, NULL, 0, NULL, right_value);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
	}
#line 3069 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 1256 "yacc_sql.y" /* yacc.c:1646  */
    {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
			Condition condition;
			condition_init(&condition, IS, 0, NULL, left_value, 0, NULL, right_value);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
		
		}
#line 3086 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 1269 "yacc_sql.y" /* yacc.c:1646  */
    {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
			Condition condition;
			condition_init(&condition, IS_NOT, 0, NULL, left_value, 0, NULL, right_value);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
		
		}
#line 3103 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 1282 "yacc_sql.y" /* yacc.c:1646  */
    {
			// printf("where sub\n");
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Selects *right_select = &CONTEXT->sub_selects[CONTEXT->sub_select_num - 1];

			Condition condition;
			select_condition_init(&condition, CONTEXT->comp[(CONTEXT->comp_length--)-1], 1, &left_attr, NULL, right_select);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
			// printf("where sub end\n");

		}
#line 3124 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 1299 "yacc_sql.y" /* yacc.c:1646  */
    {
			// printf("where sub\n");
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));

			Selects *right_select = &CONTEXT->sub_selects[CONTEXT->sub_select_num - 1];

			Condition condition;
			select_condition_init(&condition, CONTEXT->comp[(CONTEXT->comp_length--)-1], 1, &left_attr, NULL, right_select);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);

		}
#line 3144 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 1315 "yacc_sql.y" /* yacc.c:1646  */
    {
			printf("where sub\n");
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[0].string));

			Selects *right_select = &CONTEXT->sub_selects[CONTEXT->sub_select_num - 1];

			Condition condition;
			if (CONTEXT->comp[(CONTEXT->comp_length--)-1] == LESS_THAN) {
				CONTEXT->comp[CONTEXT->comp_length] = GREAT_THAN;
			} else if (CONTEXT->comp[(CONTEXT->comp_length--)-1] == GREAT_THAN) {
				CONTEXT->comp[CONTEXT->comp_length] = LESS_THAN;
			} else if (CONTEXT->comp[(CONTEXT->comp_length--)-1] == LESS_EQUAL) {
				CONTEXT->comp[CONTEXT->comp_length] = GREAT_EQUAL;
			} else if (CONTEXT->comp[(CONTEXT->comp_length--)-1] == GREAT_EQUAL) {
				CONTEXT->comp[CONTEXT->comp_length] = LESS_EQUAL;
			}
			select_condition_init(&condition, CONTEXT->comp[CONTEXT->comp_length], 1, &left_attr, NULL, right_select);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			printf("CONTEXT->condition_list_stack_top: %d\n", CONTEXT->condition_list_stack_top);
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
			// printf("where sub end\n");

		}
#line 3175 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 1342 "yacc_sql.y" /* yacc.c:1646  */
    {
			// printf("where sub\n");
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Selects *right_select = &CONTEXT->sub_selects[CONTEXT->sub_select_num - 1];

			Condition condition;
			if (CONTEXT->comp[(CONTEXT->comp_length--)-1] == LESS_THAN) {
				CONTEXT->comp[CONTEXT->comp_length] = GREAT_THAN;
			} else if (CONTEXT->comp[(CONTEXT->comp_length--)-1] == GREAT_THAN) {
				CONTEXT->comp[CONTEXT->comp_length] = LESS_THAN;
			} else if (CONTEXT->comp[(CONTEXT->comp_length--)-1] == LESS_EQUAL) {
				CONTEXT->comp[CONTEXT->comp_length] = GREAT_EQUAL;
			} else if (CONTEXT->comp[(CONTEXT->comp_length--)-1] == GREAT_EQUAL) {
				CONTEXT->comp[CONTEXT->comp_length] = LESS_EQUAL;
			}
			select_condition_init(&condition, CONTEXT->comp[CONTEXT->comp_length], 1, &left_attr, NULL, right_select);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);

		}
#line 3204 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 1367 "yacc_sql.y" /* yacc.c:1646  */
    {
			// printf("where sub\n");
			// RelAttr left_attr;
			// relation_attr_init(&left_attr, $3, $5);
			Selects *left_select = &CONTEXT->sub_selects[CONTEXT->sub_select_num - 1];
			Selects *right_select = &CONTEXT->sub_selects[CONTEXT->sub_select_num - 2];

			Condition condition;
			// if (CONTEXT->comp[(CONTEXT->comp_length--)-1] == LESS_THAN) {
			// 	CONTEXT->comp[CONTEXT->comp_length] = GREAT_THAN;
			// } else if (CONTEXT->comp[(CONTEXT->comp_length--)-1] == GREAT_THAN) {
			// 	CONTEXT->comp[CONTEXT->comp_length] = LESS_THAN;
			// } else if (CONTEXT->comp[(CONTEXT->comp_length--)-1] == LESS_EQUAL) {
			// 	CONTEXT->comp[CONTEXT->comp_length] = GREAT_EQUAL;
			// } else if (CONTEXT->comp[(CONTEXT->comp_length--)-1] == GREAT_EQUAL) {
			// 	CONTEXT->comp[CONTEXT->comp_length] = LESS_EQUAL;
			// }
			select_condition_init_(&condition, CONTEXT->comp[(CONTEXT->comp_length--)-1], left_select, right_select);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);

		}
#line 3233 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 1394 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp[CONTEXT->comp_length++] = EQUAL_TO; }
#line 3239 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 1395 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp[CONTEXT->comp_length++] = LESS_THAN; }
#line 3245 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 1396 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp[CONTEXT->comp_length++] = GREAT_THAN; }
#line 3251 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 1397 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp[CONTEXT->comp_length++] = LESS_EQUAL; }
#line 3257 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 1398 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp[CONTEXT->comp_length++] = GREAT_EQUAL; }
#line 3263 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 1399 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp[CONTEXT->comp_length++] = NOT_EQUAL; }
#line 3269 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 1400 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp[CONTEXT->comp_length++] = IN; }
#line 3275 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 1401 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp[CONTEXT->comp_length++] = NOT_IN; }
#line 3281 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 1405 "yacc_sql.y" /* yacc.c:1646  */
    {
		printf("sub select\n");
		// selects_init_(&(CONTEXT->sub_selects[CONTEXT->sub_select_num]));
		// selects_move__(&(CONTEXT->sub_selects[CONTEXT->sub_select_num]), &CONTEXT->ssql->sstr.selection);
		// CONTEXT->cur_select = &(CONTEXT->sub_selects[CONTEXT->sub_select_num]);
		int stack_top = CONTEXT->attr_list_stack_top;
		selects_append_attributes(&CONTEXT->sub_selects[CONTEXT->sub_select_num], CONTEXT->attr_list_stack[stack_top], CONTEXT->attr_list_length_stack[stack_top]);
		CONTEXT->attr_list_length_stack[stack_top] = 0;
		CONTEXT->attr_list_stack_top--;
		// CONTEXT->attr_list_length = 0;
		
		selects_append_relation(&CONTEXT->sub_selects[CONTEXT->sub_select_num], (yyvsp[-3].string));
		stack_top = CONTEXT->condition_list_stack_top;
		printf("stack top %d  sub_select_num:%d CONTEXT->condition_list_length_stack[stack_top]:%d\n", stack_top, CONTEXT->sub_select_num, CONTEXT->condition_list_length_stack[stack_top]);
		selects_append_conditions(&CONTEXT->sub_selects[CONTEXT->sub_select_num], CONTEXT->condition_list_stack[stack_top], CONTEXT->condition_list_length_stack[stack_top]);
		CONTEXT->condition_list_stack_top--;
		CONTEXT->ssql->flag=SCF_SELECT;
		CONTEXT->sub_select_num++;
		// printf("subselect end\n");
	}
#line 3306 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 1429 "yacc_sql.y" /* yacc.c:1646  */
    {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 3315 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;


#line 3319 "yacc_sql.tab.c" /* yacc.c:1646  */
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
#line 1434 "yacc_sql.y" /* yacc.c:1906  */

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
