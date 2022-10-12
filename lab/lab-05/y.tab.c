/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 2
#define YYMINOR 0
#define YYPATCH 20210808

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "parser.y"

#include "lex.yy.c"
#include "hash.c"
#include <stdbool.h>

void yyerror(char *);

void parsed(const char * msg) {
    printf("[line: %d] => %s syntax is OK\n", yylineno, msg);
}

int scope = 0;
int dtype = 0;
symbol_table *table;

void add_variable(symbol_table *t, char *name, int dtype) {
    symbol *var = create_symbol(name, dtype, scope, yylineno);
    insert_table(t, var);
}

bool is_declared(symbol_table *t, char *name) {
    symbol *var = lookup_table(t, name, scope);
    if (var == NULL) {
        return false;
    }
    return true;
}

void delete_variables(symbol_table *t) {
    remove_table(t, scope);
}

#line 54 "y.tab.c"

#if ! defined(YYSTYPE) && ! defined(YYSTYPE_IS_DECLARED)
/* Default: YYSTYPE is the semantic value type. */
typedef int YYSTYPE;
# define YYSTYPE_IS_DECLARED 1
#endif

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

#if !(defined(yylex) || defined(YYSTATE))
int YYLEX_DECL();
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define LT_TOK 257
#define GT_TOK 258
#define EQ_TOK 259
#define MINUS_TOK 260
#define PLUS_TOK 261
#define MULT_TOK 262
#define DIV_TOK 263
#define MOD_TOK 264
#define BNOT_TOK 265
#define NOT_TOK 266
#define AND_TOK 267
#define OR_TOK 268
#define XOR_TOK 269
#define LBRACE_TOK 270
#define RBRACE_TOK 271
#define LBRACKET_TOK 272
#define RBRACKET_TOK 273
#define LPAREN_TOK 274
#define RPAREN_TOK 275
#define SEMICOLON_TOK 276
#define COMMA_TOK 277
#define SINGLE_QUOTE_TOK 278
#define DOUBLE_QUOTE_TOK 279
#define MAIN_TOK 280
#define WHILE_TOK 281
#define DO_TOK 282
#define FOR_TOK 283
#define BREAK_TOK 284
#define CONTINUE_TOK 285
#define IF_TOK 286
#define ELSE_TOK 287
#define SWITCH_TOK 288
#define CASE_TOK 289
#define VOID_TOK 290
#define INT_TOK 291
#define FLOAT_TOK 292
#define CHAR_TOK 293
#define RETURN_TOK 294
#define ID_TOK 295
#define LT_EQ_TOK 296
#define GT_EQ_TOK 297
#define EQ_EQ_TOK 298
#define PLUS_EQ_TOK 299
#define MINUS_EQ_TOK 300
#define MULT_EQ_TOK 301
#define DIV_EQ_TOK 302
#define MOD_EQ_TOK 303
#define PLUS_PLUS_TOK 304
#define MINUS_MINUS_TOK 305
#define LOG_AND_TOK 306
#define LOG_OR_TOK 307
#define INTCONST 308
#define FLOATCONST 309
#define CHARCONST 310
#define STRCONST 311
#define YYERRCODE 256
typedef int YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    0,    0,    0,    0,    0,    4,    5,    2,    7,
    9,    9,    8,    8,    8,    8,    8,    1,    1,   13,
   13,   13,   13,   15,   16,   16,   14,    3,   20,   20,
   20,   21,   22,   22,   22,   17,   17,   17,   17,   17,
   17,   17,   17,   17,   17,   17,   17,   10,   10,   10,
   11,   12,   18,   18,   23,   23,   23,   23,   23,   23,
   23,   23,   23,   23,   24,   24,   24,   24,   24,   24,
    6,    6,    6,    6,   19,   19,
};
static const YYINT yylen[] = {                            2,
    2,    2,    2,    1,    1,    1,    1,    1,    5,    4,
    3,    0,    2,    2,    2,    2,    0,    2,    1,    1,
    1,    1,    1,    2,    4,    3,    3,    6,    4,    2,
    0,    4,    3,    1,    0,    1,    1,    1,    1,    1,
    1,    1,    3,    3,    3,    2,    2,    5,    7,    7,
    9,    5,    3,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    3,    1,
};
static const YYINT yydefred[] = {                         0,
    0,   42,   72,   71,   74,   73,    0,   76,   38,   39,
   40,   41,    0,    4,    5,    6,    0,    0,   19,   20,
   21,    0,   23,    0,   36,    0,    0,    0,    1,    2,
    3,    0,    0,   18,   65,   66,   67,   56,   55,   57,
   58,   59,   68,   69,   70,   60,   61,   62,   63,   64,
   46,   47,    0,    0,    0,    0,    0,   43,    0,   27,
    0,    0,    0,    0,    0,    0,    0,    0,   75,    0,
    0,    0,    0,    0,    0,   32,    7,   17,    9,    0,
    0,   33,    0,    0,   28,    0,    0,    0,   13,    0,
   17,    0,   14,   15,   16,   29,    0,    0,    0,    0,
    0,    8,   10,    0,    0,    0,    0,   11,    0,    0,
    0,   52,    0,    0,    0,    0,    0,   49,   50,    0,
   51,
};
static const YYINT yydgoto[] = {                         13,
   89,   15,   16,   78,  103,   90,   91,   83,   92,   93,
   94,   95,   18,   19,   20,   21,   22,   23,   27,   74,
   25,   68,   53,   59,
};
static const YYINT yysindex[] = {                        31,
 -241,    0,    0,    0,    0,    0, -241,    0,    0,    0,
    0,    0,   31,    0,    0,    0, -231, -272,    0,    0,
    0,  -11,    0, -238,    0, -130, -177,  -81,    0,    0,
    0, -265, -221,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, -241, -241, -241, -241, -263,    0, -241,    0,
 -252, -241, -197,  -11,  -11,  -11,  -71, -233,    0,  -11,
 -219,  -11, -240, -190, -241,    0,    0,    0,    0, -205,
 -219,    0,   25, -215,    0, -176, -170, -159,    0, -240,
    0, -127,    0,    0,    0,    0, -241, -203, -241, -243,
   25,    0,    0,  -11, -129, -128, -126,    0, -219, -203,
 -219,    0, -125, -137, -203, -246, -123,    0,    0, -219,
    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -214,    0,  -21,    0,    0, -140,    0,    0,    0,
    0,    0, -122,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, -120,    0,    0,    0,    0,
    0,    0,  -91, -163, -166, -150,  -79,    0,    0, -138,
    0, -135,    0,    0, -120,    0,    0,    0,    0,  -78,
    0,    0, -124,  -91,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, -133,
 -124,    0,    0,  -77,    0,    0,    0,    0,    0,    0,
    0,    0,    0, -264,    0,    0,    0,    0,    0,    0,
    0,
};
static const YYINT yygindex[] = {                         0,
   37,  140,  172,    0,    0,    2,  -68,  103,   98,   84,
    0,    0,  -90,    0,    0,    0,    4,  -16,    1,  117,
    0,  127,    0,  -22,
};
#define YYTABLESIZE 342
static const YYINT yytable[] = {                         54,
   24,   17,   79,   34,   26,   48,   48,  106,   61,   48,
   28,   48,   85,   24,   17,   62,   48,   33,   48,  113,
   55,   48,   71,   77,  117,   48,   48,   48,   48,   48,
   48,   69,    1,   57,    2,   56,   14,   62,   57,   88,
  112,   76,  114,   48,   48,   48,   48,  118,   32,   29,
   77,  121,   63,    8,    8,   57,   64,   65,   66,   67,
   22,   22,   70,    8,   73,   72,    9,   10,   11,   12,
    1,   84,    2,   80,    3,    4,    5,    6,   67,   69,
  105,   54,  107,   24,   81,   73,    3,    4,    5,    6,
  100,    8,    3,    4,    5,    6,   56,   97,   24,   57,
  104,   24,  104,   98,    9,   10,   11,   12,   45,   45,
   24,   44,   44,   44,   99,   24,   37,   37,   37,   37,
   37,   37,   37,   37,   26,   26,   35,   36,   37,   38,
   39,   40,   41,   42,   37,   37,   45,   45,   45,   25,
   25,   24,   24,  102,   58,  109,   12,  110,  111,  116,
  115,  120,   30,   24,   35,   37,   37,   37,   37,   37,
   37,   37,   37,   37,   37,   43,   44,   45,   46,   47,
   48,   49,   50,   51,   52,   35,   36,   37,   38,   39,
   40,   41,   42,   31,   31,   35,   36,   37,   38,   39,
   40,   41,   42,  101,   60,   34,   30,   54,  108,  119,
   96,   82,    0,    0,    0,   75,    0,    0,    0,    0,
    0,    0,    0,    0,   43,   44,   45,   46,   47,   48,
   49,   50,   51,   52,   43,   44,   45,   46,   47,   48,
   49,   50,   51,   52,    0,   37,   37,    0,   37,   37,
   37,   37,   37,    0,    0,   35,   36,   37,   38,   39,
   40,   41,   42,   37,   37,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   37,   37,   37,   37,   37,   37,
   37,   37,   37,   37,   43,   44,   45,   46,   47,   48,
   49,   50,   51,   52,   77,    0,    0,    0,    1,    0,
    2,    0,    0,    0,    1,   86,    2,   87,    0,    0,
   88,    0,    0,    0,    3,    4,    5,    6,    7,    8,
    3,    4,    5,    6,    7,    8,    0,    0,    0,    0,
    0,    0,    9,   10,   11,   12,    0,    0,    9,   10,
   11,   12,
};
static const YYINT yycheck[] = {                         22,
    0,    0,   71,  276,    1,  270,  271,   98,  274,  274,
    7,  276,   81,   13,   13,  259,  281,   17,  283,  110,
  259,  286,  275,  270,  115,  290,  291,  292,  293,  294,
  295,  295,  274,  277,  276,  274,    0,  259,  277,  286,
  109,  275,  111,  308,  309,  310,  311,  116,  280,   13,
  270,  120,  274,  295,  295,  277,   53,   54,   55,   56,
  275,  276,   59,  295,   63,   62,  308,  309,  310,  311,
  274,  277,  276,   73,  290,  291,  292,  293,   75,  295,
   97,  104,   99,   83,  275,   84,  290,  291,  292,  293,
   90,  295,  290,  291,  292,  293,  274,  274,   98,  277,
   97,  101,   99,  274,  308,  309,  310,  311,  275,  276,
  110,  275,  276,  277,  274,  115,  257,  258,  259,  260,
  261,  262,  263,  264,  275,  276,  257,  258,  259,  260,
  261,  262,  263,  264,  275,  276,  275,  276,  277,  275,
  276,  275,  276,  271,  275,  275,  271,  276,  275,  287,
  276,  275,   13,  276,  275,  296,  297,  298,  299,  300,
  301,  302,  303,  304,  305,  296,  297,  298,  299,  300,
  301,  302,  303,  304,  305,  257,  258,  259,  260,  261,
  262,  263,  264,  275,   13,  257,  258,  259,  260,  261,
  262,  263,  264,   91,  276,  275,  275,  275,  101,  116,
   84,   75,   -1,   -1,   -1,  277,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  296,  297,  298,  299,  300,  301,
  302,  303,  304,  305,  296,  297,  298,  299,  300,  301,
  302,  303,  304,  305,   -1,  257,  258,   -1,  260,  261,
  262,  263,  264,   -1,   -1,  257,  258,  259,  260,  261,
  262,  263,  264,  275,  276,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  296,  297,  298,  299,  300,  301,
  302,  303,  304,  305,  296,  297,  298,  299,  300,  301,
  302,  303,  304,  305,  270,   -1,   -1,   -1,  274,   -1,
  276,   -1,   -1,   -1,  274,  281,  276,  283,   -1,   -1,
  286,   -1,   -1,   -1,  290,  291,  292,  293,  294,  295,
  290,  291,  292,  293,  294,  295,   -1,   -1,   -1,   -1,
   -1,   -1,  308,  309,  310,  311,   -1,   -1,  308,  309,
  310,  311,
};
#define YYFINAL 13
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 311
#define YYUNDFTOKEN 338
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"LT_TOK","GT_TOK","EQ_TOK",
"MINUS_TOK","PLUS_TOK","MULT_TOK","DIV_TOK","MOD_TOK","BNOT_TOK","NOT_TOK",
"AND_TOK","OR_TOK","XOR_TOK","LBRACE_TOK","RBRACE_TOK","LBRACKET_TOK",
"RBRACKET_TOK","LPAREN_TOK","RPAREN_TOK","SEMICOLON_TOK","COMMA_TOK",
"SINGLE_QUOTE_TOK","DOUBLE_QUOTE_TOK","MAIN_TOK","WHILE_TOK","DO_TOK","FOR_TOK",
"BREAK_TOK","CONTINUE_TOK","IF_TOK","ELSE_TOK","SWITCH_TOK","CASE_TOK",
"VOID_TOK","INT_TOK","FLOAT_TOK","CHAR_TOK","RETURN_TOK","ID_TOK","LT_EQ_TOK",
"GT_EQ_TOK","EQ_EQ_TOK","PLUS_EQ_TOK","MINUS_EQ_TOK","MULT_EQ_TOK","DIV_EQ_TOK",
"MOD_EQ_TOK","PLUS_PLUS_TOK","MINUS_MINUS_TOK","LOG_AND_TOK","LOG_OR_TOK",
"INTCONST","FLOATCONST","CHARCONST","STRCONST",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : S",
"S : S statement",
"S : S main",
"S : S function",
"S : statement",
"S : main",
"S : function",
"open_paren : LBRACE_TOK",
"close_paren : RBRACE_TOK",
"main : datatype MAIN_TOK LPAREN_TOK RPAREN_TOK block",
"block : open_paren statements blocks close_paren",
"blocks : block statements blocks",
"blocks :",
"statements : statements statement",
"statements : statements if_statement",
"statements : statements for_statement",
"statements : statements while_statement",
"statements :",
"statement : operation SEMICOLON_TOK",
"statement : return_statement",
"operation : declaration",
"operation : assignment",
"operation : expression",
"operation : condition",
"declaration : datatype id_token",
"assignment : datatype id_token EQ_TOK expression",
"assignment : id_token EQ_TOK expression",
"return_statement : RETURN_TOK expression SEMICOLON_TOK",
"function : datatype id_token LPAREN_TOK params RPAREN_TOK block",
"params : datatype id_token COMMA_TOK params",
"params : datatype id_token",
"params :",
"function_call : id_token LPAREN_TOK args RPAREN_TOK",
"args : expression COMMA_TOK args",
"args : expression",
"args :",
"expression : function_call",
"expression : id_token",
"expression : INTCONST",
"expression : FLOATCONST",
"expression : CHARCONST",
"expression : STRCONST",
"expression : SEMICOLON_TOK",
"expression : LPAREN_TOK expression RPAREN_TOK",
"expression : expression arithmetic_op expression",
"expression : expression relational_op expression",
"expression : expression PLUS_PLUS_TOK",
"expression : expression MINUS_MINUS_TOK",
"if_statement : IF_TOK LPAREN_TOK condition RPAREN_TOK block",
"if_statement : IF_TOK LPAREN_TOK condition RPAREN_TOK block ELSE_TOK block",
"if_statement : IF_TOK LPAREN_TOK condition RPAREN_TOK block ELSE_TOK if_statement",
"for_statement : FOR_TOK LPAREN_TOK operation SEMICOLON_TOK operation SEMICOLON_TOK operation RPAREN_TOK block",
"while_statement : WHILE_TOK LPAREN_TOK condition RPAREN_TOK block",
"condition : expression relational_op expression",
"condition : expression",
"arithmetic_op : PLUS_TOK",
"arithmetic_op : MINUS_TOK",
"arithmetic_op : MULT_TOK",
"arithmetic_op : DIV_TOK",
"arithmetic_op : MOD_TOK",
"arithmetic_op : PLUS_EQ_TOK",
"arithmetic_op : MINUS_EQ_TOK",
"arithmetic_op : MULT_EQ_TOK",
"arithmetic_op : DIV_EQ_TOK",
"arithmetic_op : MOD_EQ_TOK",
"relational_op : LT_TOK",
"relational_op : GT_TOK",
"relational_op : EQ_TOK",
"relational_op : LT_EQ_TOK",
"relational_op : GT_EQ_TOK",
"relational_op : EQ_EQ_TOK",
"datatype : INT_TOK",
"datatype : VOID_TOK",
"datatype : CHAR_TOK",
"datatype : FLOAT_TOK",
"id_token : id_token COMMA_TOK ID_TOK",
"id_token : ID_TOK",

};
#endif

#if YYDEBUG
int      yydebug;
#endif

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;
int      yynerrs;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 270 "parser.y"

void yyerror(char *s) {
	printf("SYNTAX ERROR: %s LINE NUMBER: %d\n", s, yylineno);
}

int main()
{
    table = create_table();

    if (yyparse()==0) printf("\nPARSING COMPLETED SUCCESSFULLY ✅\n");
    else printf("\nPARSING ERROR (at line no:  %d) ❌\n", yylineno);

    return(0);	

}
#line 465 "y.tab.c"

#if YYDEBUG
#include <stdio.h>	/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    /* yym is set below */
    /* yyn is set below */
    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        yychar = YYLEX;
        if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if (((yyn = yysindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if (((yyn = yyrindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag != 0) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab; /* redundant goto avoids 'unused label' warning */
yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if (((yyn = yysindex[*yystack.s_mark]) != 0) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym > 0)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);

    switch (yyn)
    {
case 7:
#line 130 "parser.y"
	{ scope++; }
#line 667 "y.tab.c"
break;
case 8:
#line 133 "parser.y"
	{ delete_variables(table); scope--; }
#line 672 "y.tab.c"
break;
case 9:
#line 137 "parser.y"
	{parsed("main function");}
#line 677 "y.tab.c"
break;
case 24:
#line 165 "parser.y"
	{
    parsed("declaration statement");
    add_variable(table, var_name, dtype);
    iterate_table(table);
}
#line 686 "y.tab.c"
break;
case 25:
#line 172 "parser.y"
	{
    add_variable(table, var_name, dtype);
    iterate_table(table);
    parsed("assignment statement");
}
#line 695 "y.tab.c"
break;
case 26:
#line 177 "parser.y"
	{
    if(!is_declared(table, var_name)) {
        yyerror("variable not declared");
        return 1;
    } 
    parsed("assignment statement");
}
#line 706 "y.tab.c"
break;
case 27:
#line 186 "parser.y"
	{parsed("return statement");}
#line 711 "y.tab.c"
break;
case 28:
#line 189 "parser.y"
	{parsed("function");}
#line 716 "y.tab.c"
break;
case 32:
#line 197 "parser.y"
	{parsed("function call");}
#line 721 "y.tab.c"
break;
case 37:
#line 206 "parser.y"
	{
    if(!is_declared(table, var_name)) {
        yyerror("variable not declared");
        return 1;
    }
                }
#line 731 "y.tab.c"
break;
case 48:
#line 224 "parser.y"
	{parsed("if statement");}
#line 736 "y.tab.c"
break;
case 49:
#line 225 "parser.y"
	{parsed("if-else statement");}
#line 741 "y.tab.c"
break;
case 50:
#line 226 "parser.y"
	{parsed("else-if statement");}
#line 746 "y.tab.c"
break;
case 51:
#line 229 "parser.y"
	{parsed("for statement");}
#line 751 "y.tab.c"
break;
case 52:
#line 232 "parser.y"
	{parsed("while statement");}
#line 756 "y.tab.c"
break;
case 71:
#line 259 "parser.y"
	{ dtype = INT_TOK; }
#line 761 "y.tab.c"
break;
case 72:
#line 260 "parser.y"
	{ dtype = VOID_TOK; }
#line 766 "y.tab.c"
break;
case 73:
#line 261 "parser.y"
	{ dtype = CHAR_TOK; }
#line 771 "y.tab.c"
break;
case 74:
#line 262 "parser.y"
	{ dtype = FLOAT_TOK; }
#line 776 "y.tab.c"
break;
#line 778 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            yychar = YYLEX;
            if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if (((yyn = yygindex[yym]) != 0) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
