/* A Bison parser, made by GNU Bison 1.875.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     AWKBEGIN = 258,
     AWKEND = 259,
     REGMATCH = 260,
     COMMENT = 261,
     IF = 262,
     ELSE = 263,
     WHILE = 264,
     EXIT = 265,
     EQ = 266,
     LE = 267,
     GE = 268,
     NE = 269,
     BOOLAND = 270,
     BOOLOR = 271,
     REGEX = 272,
     STRING = 273,
     NUM = 274,
     ID = 275
   };
#endif
#define AWKBEGIN 258
#define AWKEND 259
#define REGMATCH 260
#define COMMENT 261
#define IF 262
#define ELSE 263
#define WHILE 264
#define EXIT 265
#define EQ 266
#define LE 267
#define GE 268
#define NE 269
#define BOOLAND 270
#define BOOLOR 271
#define REGEX 272
#define STRING 273
#define NUM 274
#define ID 275




/* Copy the first part of user declarations.  */
#line 1 "awk.y"

	//This file belongs to yacc
	
    #include <stdlib.h>
    #include <math.h>
    #include <unistd.h>
    #include "customstring.h"
    #include "customio.h"
    #include "entry.h"

    extern int yylineno;
    extern int yylex();
    extern int DEBUG;
    
    void yyerror(char *s) {
		printstr_err(s); printstr_err(" on line "); 
		printint_err(yylineno); printstr_err("\n");
		//fprintf(stderr, "%s on line %d\n", s, yylineno);
		exit(SYNTAX_ERROR);
    }
    void printop(char *s) {
		if (DEBUG) fprintf(stderr, "Got %s\n", s);
	}
	void printrun(char* s) {
		if (DEBUG) fprintf(stderr, "Running %s\n", s);
	}
	
	void die(char* s, int exitcode) {
		fprintf(stderr, "%s\n", s);
		exit(exitcode);
	}
	
	void warning(char* s) {
		fprintf(stderr, "warning: %s\n", s);
	}
		
	char* type_by_enum[] = { "none", "singleop", "blockop", "exprop", "assignop", "value", "strvalue", "id", "binaryop", "unaryop", "ifop", "whileop", "funop", "regex" };

	//SOME ACTUALLY USEFUL STUFF
	
	
	entry* head;
	entry* awkbegin;
	entry* awkend;
	
	
	void rec_print(entry* a, int depth) {
		if (a == NULL) return;
		if (DEBUG == 0) return;

		for (int i = 0; i < depth; i++) printstr(" ");
		char* strbuf = (char*)calloc(50, sizeof(char));
		sprintf(strbuf, "%p %d %s %c ", a, a->type, type_by_enum[a->type], a->op);
		printstr(strbuf);
		free(strbuf);
		if (a->text != NULL) printstr(a->text);
		printstr("\n");
		for (int i = 0; i < a->argc; i++) {
			rec_print((entry*)((a->argv)[i]), depth + 1);
		}
	
	}

	entry* new_entry_0(){
		entry* tmp = (entry*)malloc(sizeof(entry));
		tmp->type = none;
		tmp->argc = 0;
		tmp->argv = (struct entry**)malloc(sizeof(entry*) * 5);
		tmp->text = "\0";
		tmp->op = '\0';
		tmp->op2 = '\0';
		return tmp;
	}
	entry* new_entry_1(entry* a) {
		entry* tmp = new_entry_0();
		tmp->argc = 1;
		(tmp->argv)[0] = a;
		return tmp;
	}
	entry* new_entry_2(entry* a, entry* b) {
		entry* tmp = new_entry_1(a);
		tmp->argc = 2;
		(tmp->argv)[1] = b;
		return tmp;
	}
	
	//OPERATORS
	entry* new_block_op_2(entry* a, entry* b) {
		entry* tmp = new_entry_2(a, b);
		tmp->type = blockop;
		return tmp;
	};
	
	//EXPRESSIONS
	entry* new_expr_op(entry* a) {
		entry* tmp = new_entry_1(a);
		tmp->type = exprop;
		return tmp;
	}
	entry* new_expr_value(entry* a) {
		entry* tmp = new_entry_1(a);
		tmp->type = value;
		return tmp;
	}
	entry* new_assign_op(entry* a, entry* b) {
		entry* tmp = new_entry_2(a, b);
		tmp->type = assignop;
		return tmp;
	}
	entry* new_binary_op(char op, entry* a, entry* b) {
		entry* tmp = new_entry_2(a, b);
		tmp->type = binaryop;
		tmp->op = op;
		return tmp;
	}
	entry* new_binary_op2(char op, char op2, entry* a, entry* b) {
		entry* tmp = new_entry_2(a, b);
		tmp->type = binaryop;
		tmp->op = op;
		tmp->op2 = op2;
		return tmp;
	}
	entry* new_unary_op(char op, entry* a) {
		entry* tmp = new_entry_1(a);
		tmp->type = unaryop;
		tmp-> op = op;
		return tmp;
	}
	entry* new_id_value(entry* a) {
		entry* tmp = new_entry_1(a);
		tmp->type = value;
		return tmp;
	}
	entry* new_if_op(entry* a, entry* b, entry* c) {
		entry* tmp = new_entry_2(a, b);
		tmp->type = ifop;
		tmp->argc = 3;
		(tmp->argv)[2] = c;
		return tmp;
	}
	entry* new_while_op(entry* a, entry* b) {
		entry* tmp = new_entry_2(a, b);
		tmp->type = whileop;
		return tmp;
	}
	entry* new_fun_op(entry* a, entry* b) {
		entry* tmp = new_entry_2(a, b);
		tmp->type = funop;
		return tmp;
	}
	entry* new_sub_fun_op(entry* a, entry* b, entry* c, entry* d) {
		entry* tmp = new_entry_2(a, b);
		tmp->type = funop;
		tmp->argc = 4;
		(tmp->argv)[2] = c;
		(tmp->argv)[3] = d;
		return tmp;
	}
	entry* new_regex() {
		entry* tmp = new_entry_0();
		tmp->type = regex;
		return tmp;
	}


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

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 291 "awk.tab.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  35
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   225

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  11
/* YYNRULES -- Number of rules. */
#define YYNRULES  43
/* YYNRULES -- Number of states. */
#define YYNSTATES  98

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   275

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    33,     2,     2,     2,     2,     2,     2,
      24,    25,    31,    29,    34,    30,     2,    32,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    23,
      28,    26,    27,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    21,     2,    22,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned char yyprhs[] =
{
       0,     0,     3,     5,    13,    21,    33,    35,    38,    42,
      45,    53,    59,    62,    68,    76,    82,    84,    86,    88,
      92,    95,    97,   101,   105,   109,   113,   117,   121,   125,
     129,   131,   135,   139,   141,   145,   149,   151,   154,   157,
     161,   163,   168,   176
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      36,     0,    -1,    37,    -1,     3,    21,    37,    22,    21,
      37,    22,    -1,    21,    37,    22,     4,    21,    37,    22,
      -1,     3,    21,    37,    22,    21,    37,    22,     4,    21,
      37,    22,    -1,    40,    -1,    37,    40,    -1,    21,    37,
      22,    -1,    41,    23,    -1,     7,    24,    41,    25,    38,
       8,    38,    -1,     9,    24,    41,    25,    38,    -1,    10,
      23,    -1,     7,    24,    41,    25,    40,    -1,     7,    24,
      41,    25,    38,     8,    39,    -1,     9,    24,    41,    25,
      39,    -1,    38,    -1,    39,    -1,    42,    -1,    20,    26,
      41,    -1,    20,    17,    -1,    43,    -1,    42,    11,    43,
      -1,    42,    12,    43,    -1,    42,    13,    43,    -1,    42,
      14,    43,    -1,    42,    15,    43,    -1,    42,    16,    43,
      -1,    42,    27,    43,    -1,    42,    28,    43,    -1,    44,
      -1,    43,    29,    44,    -1,    43,    30,    44,    -1,    45,
      -1,    44,    31,    45,    -1,    44,    32,    45,    -1,    19,
      -1,    30,    45,    -1,    33,    45,    -1,    24,    41,    25,
      -1,    20,    -1,    20,    24,    41,    25,    -1,    20,    24,
      20,    17,    34,    45,    25,    -1,    18,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned char yyrline[] =
{
       0,   183,   183,   184,   185,   186,   189,   190,   193,   194,
     195,   196,   197,   200,   201,   202,   205,   205,   207,   208,
     209,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     223,   224,   225,   228,   229,   230,   233,   234,   235,   236,
     237,   238,   239,   240
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "AWKBEGIN", "AWKEND", "REGMATCH", 
  "COMMENT", "IF", "ELSE", "WHILE", "EXIT", "EQ", "LE", "GE", "NE", 
  "BOOLAND", "BOOLOR", "REGEX", "STRING", "NUM", "ID", "'{'", "'}'", 
  "';'", "'('", "')'", "'='", "'>'", "'<'", "'+'", "'-'", "'*'", "'/'", 
  "'!'", "','", "$accept", "PROGRAM", "OPS", "OP1", "OP2", "OP", "EXPR", 
  "EXPR1", "EXPR2", "TERM", "VAL", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   123,   125,    59,    40,    41,    61,    62,    60,    43,
      45,    42,    47,    33,    44
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    35,    36,    36,    36,    36,    37,    37,    38,    38,
      38,    38,    38,    39,    39,    39,    40,    40,    41,    41,
      41,    42,    42,    42,    42,    42,    42,    42,    42,    42,
      43,    43,    43,    44,    44,    44,    45,    45,    45,    45,
      45,    45,    45,    45
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     7,     7,    11,     1,     2,     3,     2,
       7,     5,     2,     5,     7,     5,     1,     1,     1,     3,
       2,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     1,     2,     2,     3,
       1,     4,     7,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,     0,     0,     0,    43,    36,    40,     0,     0,
       0,     0,     0,     2,    16,    17,     6,     0,    18,    21,
      30,    33,     0,     0,     0,    12,    20,     0,     0,     0,
       0,     0,    40,    37,    38,     1,     7,     9,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    40,     0,    19,     0,     8,    39,    22,
      23,    24,    25,    26,    27,    28,    29,    31,    32,    34,
      35,     0,     0,     0,    20,    41,     8,     0,     0,    16,
      13,    11,    15,     0,     0,     0,     0,     0,     0,     3,
      10,    14,    42,     4,     0,     0,     0,     5
};

/* YYDEFGOTO[NTERM-NUM]. */
static const yysigned_char yydefgoto[] =
{
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -67
static const short yypact[] =
{
       8,   -20,     1,    33,   -19,   -67,   -67,   -14,   161,    34,
     168,   168,    13,   161,   -67,   -67,   -67,    36,    35,    -6,
       5,   -67,   161,    34,    34,   -67,   -67,   184,    34,   161,
      62,    40,    42,   -67,   -67,   -67,   -67,   -67,   168,   168,
     168,   168,   168,   168,   168,   168,   168,   168,   168,   168,
      81,    43,    48,    16,    50,   -67,    97,    56,   -67,    -6,
      -6,    -6,    -6,    -6,    -6,    -6,    -6,     5,     5,   -67,
     -67,    58,   161,   161,    55,   -67,   -67,    72,   161,    86,
     -67,   -67,   -67,   168,   161,   113,   161,    71,   129,    93,
     -67,   -67,   -67,   -67,    77,   161,   145,   -67
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
     -67,   -67,    -8,   -64,   -66,   -11,     7,   -67,   180,     9,
      -5
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned char yytable[] =
{
      30,    22,    36,    26,    25,    33,    34,    82,    79,    81,
      27,     1,    28,    35,    50,     2,    31,     3,     4,    36,
      91,    56,    90,    46,    47,    23,     5,     6,     7,     8,
      51,    52,     9,    74,    54,    55,    48,    49,    10,    36,
      27,    11,    28,    69,    70,    36,    38,    39,    40,    41,
      42,    43,     5,     6,     7,    67,    68,    24,     9,    37,
      77,    80,    44,    45,    10,    58,    27,    11,    72,     2,
      85,     3,     4,    73,    36,    75,    88,    36,    87,    78,
       5,     6,     7,    29,    57,    36,     9,    96,     2,    83,
       3,     4,    10,    84,    86,    11,    92,    94,    95,     5,
       6,     7,    29,    71,     2,     9,     3,     4,     0,     0,
       0,    10,     0,     0,    11,     5,     6,     7,    29,    76,
       2,     9,     3,     4,     0,     0,     0,    10,     0,     0,
      11,     5,     6,     7,    29,    89,     2,     9,     3,     4,
       0,     0,     0,    10,     0,     0,    11,     5,     6,     7,
      29,    93,     2,     9,     3,     4,     0,     0,     0,    10,
       0,     0,    11,     5,     6,     7,    29,    97,     2,     9,
       3,     4,     0,     0,     0,    10,     0,     0,    11,     5,
       6,     7,    29,     0,     0,     9,     5,     6,    32,     0,
       0,    10,     9,     0,    11,     0,     0,     0,    10,     0,
       0,    11,     5,     6,    53,     0,     0,     0,     9,     0,
       0,     0,     0,     0,    10,     0,     0,    11,    59,    60,
      61,    62,    63,    64,    65,    66
};

static const yysigned_char yycheck[] =
{
       8,    21,    13,    17,    23,    10,    11,    73,    72,    73,
      24,     3,    26,     0,    22,     7,     9,     9,    10,    30,
      86,    29,    86,    29,    30,    24,    18,    19,    20,    21,
      23,    24,    24,    17,    27,    28,    31,    32,    30,    50,
      24,    33,    26,    48,    49,    56,    11,    12,    13,    14,
      15,    16,    18,    19,    20,    46,    47,    24,    24,    23,
       4,    72,    27,    28,    30,    25,    24,    33,    25,     7,
      78,     9,    10,    25,    85,    25,    84,    88,    83,    21,
      18,    19,    20,    21,    22,    96,    24,    95,     7,    34,
       9,    10,    30,    21,     8,    33,    25,     4,    21,    18,
      19,    20,    21,    22,     7,    24,     9,    10,    -1,    -1,
      -1,    30,    -1,    -1,    33,    18,    19,    20,    21,    22,
       7,    24,     9,    10,    -1,    -1,    -1,    30,    -1,    -1,
      33,    18,    19,    20,    21,    22,     7,    24,     9,    10,
      -1,    -1,    -1,    30,    -1,    -1,    33,    18,    19,    20,
      21,    22,     7,    24,     9,    10,    -1,    -1,    -1,    30,
      -1,    -1,    33,    18,    19,    20,    21,    22,     7,    24,
       9,    10,    -1,    -1,    -1,    30,    -1,    -1,    33,    18,
      19,    20,    21,    -1,    -1,    24,    18,    19,    20,    -1,
      -1,    30,    24,    -1,    33,    -1,    -1,    -1,    30,    -1,
      -1,    33,    18,    19,    20,    -1,    -1,    -1,    24,    -1,
      -1,    -1,    -1,    -1,    30,    -1,    -1,    33,    38,    39,
      40,    41,    42,    43,    44,    45
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     3,     7,     9,    10,    18,    19,    20,    21,    24,
      30,    33,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    21,    24,    24,    23,    17,    24,    26,    21,
      37,    41,    20,    45,    45,     0,    40,    23,    11,    12,
      13,    14,    15,    16,    27,    28,    29,    30,    31,    32,
      37,    41,    41,    20,    41,    41,    37,    22,    25,    43,
      43,    43,    43,    43,    43,    43,    43,    44,    44,    45,
      45,    22,    25,    25,    17,    25,    22,     4,    21,    38,
      40,    38,    39,    34,    21,    37,     8,    45,    37,    22,
      38,    39,    25,    22,     4,    21,    37,    22
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrlab1

/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)         \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;
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
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (cinluded).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylineno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylineno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
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
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
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
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

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
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
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
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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
#line 183 "awk.y"
    { rec_print(yyvsp[0], 0); head = yyvsp[0]; awkbegin = NULL; awkend = NULL;;}
    break;

  case 3:
#line 184 "awk.y"
    { rec_print(yyvsp[-1], 0); head = yyvsp[-1]; awkbegin = yyvsp[-4]; awkend = NULL;;}
    break;

  case 4:
#line 185 "awk.y"
    { rec_print(yyvsp[-5], 0); head = yyvsp[-5]; awkbegin = NULL; awkend = yyvsp[-1];;}
    break;

  case 5:
#line 186 "awk.y"
    { rec_print(yyvsp[-5], 0); head = yyvsp[-5]; awkbegin = yyvsp[-8]; awkend = yyvsp[-1];;}
    break;

  case 7:
#line 190 "awk.y"
    { yyval = new_block_op_2(yyvsp[-1], yyvsp[0]);;}
    break;

  case 8:
#line 193 "awk.y"
    { yyval = yyvsp[-1]; printop("op in braces");;}
    break;

  case 9:
#line 194 "awk.y"
    { yyval = new_expr_op(yyvsp[-1]); printop("expression");;}
    break;

  case 10:
#line 195 "awk.y"
    { yyval = new_if_op(yyvsp[-4], yyvsp[-2], yyvsp[0]); printop("if/else 1");;}
    break;

  case 11:
#line 196 "awk.y"
    { yyval = new_while_op(yyvsp[-2], yyvsp[0]); printop("while 1");;}
    break;

  case 12:
#line 197 "awk.y"
    { /*$$ = new exitop();*/ printop("exit");;}
    break;

  case 13:
#line 200 "awk.y"
    { yyval = new_if_op(yyvsp[-2], yyvsp[0], NULL); printop("if");;}
    break;

  case 14:
#line 201 "awk.y"
    { yyval = new_if_op(yyvsp[-4], yyvsp[-2], yyvsp[0]); printop("if/else 2");;}
    break;

  case 15:
#line 202 "awk.y"
    { yyval = new_while_op(yyvsp[-2], yyvsp[0]); printop("while 2");;}
    break;

  case 19:
#line 208 "awk.y"
    { yyval = new_assign_op(yyvsp[-2], yyvsp[0]); printop("assign value");;}
    break;

  case 20:
#line 209 "awk.y"
    { yyval = new_binary_op('~', yyvsp[-1], yyvsp[0]); printop("regex match");;}
    break;

  case 22:
#line 213 "awk.y"
    { yyval = new_binary_op2('=', '=', yyvsp[-2], yyvsp[0]); printop("binary ==");;}
    break;

  case 23:
#line 214 "awk.y"
    { yyval = new_binary_op2('<', '=', yyvsp[-2], yyvsp[0]); printop("binary <=");;}
    break;

  case 24:
#line 215 "awk.y"
    { yyval = new_binary_op2('>', '=', yyvsp[-2], yyvsp[0]); printop("binary >=");;}
    break;

  case 25:
#line 216 "awk.y"
    { yyval = new_binary_op2('!', '=', yyvsp[-2], yyvsp[0]); printop("binary !=");;}
    break;

  case 26:
#line 217 "awk.y"
    { yyval = new_binary_op2('&', '&', yyvsp[-2], yyvsp[0]); printop("binary &&");;}
    break;

  case 27:
#line 218 "awk.y"
    { yyval = new_binary_op2('|', '|', yyvsp[-2], yyvsp[0]); printop("binary ||");;}
    break;

  case 28:
#line 219 "awk.y"
    { yyval = new_binary_op('>', yyvsp[-2], yyvsp[0]); printop("binary >");;}
    break;

  case 29:
#line 220 "awk.y"
    { yyval = new_binary_op('<', yyvsp[-2], yyvsp[0]); printop("binary <");;}
    break;

  case 31:
#line 224 "awk.y"
    { yyval = new_binary_op('+', yyvsp[-2], yyvsp[0]); printop("binary +");;}
    break;

  case 32:
#line 225 "awk.y"
    { yyval = new_binary_op('-', yyvsp[-2], yyvsp[0]);  printop("binary -");;}
    break;

  case 34:
#line 229 "awk.y"
    { yyval = new_binary_op('*', yyvsp[-2], yyvsp[0]);  printop("binary *");;}
    break;

  case 35:
#line 230 "awk.y"
    { yyval = new_binary_op('/', yyvsp[-2], yyvsp[0]);  printop("binary /");;}
    break;

  case 36:
#line 233 "awk.y"
    { yyval = new_expr_value(yyvsp[0]); printop("plain value");;}
    break;

  case 37:
#line 234 "awk.y"
    { yyval = new_unary_op('-', yyvsp[0]); printop("unary -");;}
    break;

  case 38:
#line 235 "awk.y"
    { yyval = new_unary_op('!', yyvsp[0]); printop("binary !");;}
    break;

  case 39:
#line 236 "awk.y"
    { yyval = yyvsp[-1]; ;}
    break;

  case 40:
#line 237 "awk.y"
    { yyval = new_id_value(yyvsp[0]); printop("value by id");;}
    break;

  case 41:
#line 238 "awk.y"
    { yyval=new_fun_op(yyvsp[-3], yyvsp[-1]); printop("funcall");;}
    break;

  case 42:
#line 239 "awk.y"
    { yyval = new_sub_fun_op(yyvsp[-6], yyvsp[-4], yyvsp[-3], yyvsp[-1]); printop("regexp funcall"); ;}
    break;

  case 43:
#line 240 "awk.y"
    { yyval = new_expr_value(yyvsp[0]); printop("string"); ;}
    break;


    }

/* Line 991 of yacc.c.  */
#line 1441 "awk.tab.c"

  yyvsp -= yylen;
  yyssp -= yylen;


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
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("syntax error, unexpected ") + 1;
	  yysize += yystrlen (yytname[yytype]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        {
	  /* Pop the error token.  */
          YYPOPSTACK;
	  /* Pop the rest of the stack.  */
	  while (yyss < yyssp)
	    {
	      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
	      yydestruct (yystos[*yyssp], yyvsp);
	      YYPOPSTACK;
	    }
	  YYABORT;
        }

      YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
      yydestruct (yytoken, &yylval);
      yychar = YYEMPTY;

    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab2;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
yyerrlab1:

  /* Suppress GCC warning that yyerrlab1 is unused when no action
     invokes YYERROR.  */
#if defined (__GNUC_MINOR__) && 2093 <= (__GNUC__ * 1000 + __GNUC_MINOR__)
  __attribute__ ((__unused__))
#endif


  goto yyerrlab2;


/*---------------------------------------------------------------.
| yyerrlab2 -- pop states until the error token can be shifted.  |
`---------------------------------------------------------------*/
yyerrlab2:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      yyvsp--;
      yystate = *--yyssp;

      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 243 "awk.y"


