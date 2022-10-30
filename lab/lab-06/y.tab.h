/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

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
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     LT_TOK = 258,
     GT_TOK = 259,
     EQ_TOK = 260,
     MINUS_TOK = 261,
     PLUS_TOK = 262,
     MULT_TOK = 263,
     DIV_TOK = 264,
     MOD_TOK = 265,
     BNOT_TOK = 266,
     NOT_TOK = 267,
     AND_TOK = 268,
     OR_TOK = 269,
     XOR_TOK = 270,
     LBRACE_TOK = 271,
     RBRACE_TOK = 272,
     LBRACKET_TOK = 273,
     RBRACKET_TOK = 274,
     LPAREN_TOK = 275,
     RPAREN_TOK = 276,
     SEMICOLON_TOK = 277,
     COMMA_TOK = 278,
     SINGLE_QUOTE_TOK = 279,
     DOUBLE_QUOTE_TOK = 280,
     MAIN_TOK = 281,
     WHILE_TOK = 282,
     DO_TOK = 283,
     FOR_TOK = 284,
     BREAK_TOK = 285,
     CONTINUE_TOK = 286,
     IF_TOK = 287,
     ELSE_TOK = 288,
     SWITCH_TOK = 289,
     CASE_TOK = 290,
     VOID_TOK = 291,
     INT_TOK = 292,
     FLOAT_TOK = 293,
     CHAR_TOK = 294,
     RETURN_TOK = 295,
     ID_TOK = 296,
     LT_EQ_TOK = 297,
     GT_EQ_TOK = 298,
     EQ_EQ_TOK = 299,
     PLUS_EQ_TOK = 300,
     MINUS_EQ_TOK = 301,
     MULT_EQ_TOK = 302,
     DIV_EQ_TOK = 303,
     MOD_EQ_TOK = 304,
     PLUS_PLUS_TOK = 305,
     MINUS_MINUS_TOK = 306,
     LOG_AND_TOK = 307,
     LOG_OR_TOK = 308,
     INTCONST = 309,
     FLOATCONST = 310,
     CHARCONST = 311,
     STRCONST = 312
   };
#endif
/* Tokens.  */
#define LT_TOK 258
#define GT_TOK 259
#define EQ_TOK 260
#define MINUS_TOK 261
#define PLUS_TOK 262
#define MULT_TOK 263
#define DIV_TOK 264
#define MOD_TOK 265
#define BNOT_TOK 266
#define NOT_TOK 267
#define AND_TOK 268
#define OR_TOK 269
#define XOR_TOK 270
#define LBRACE_TOK 271
#define RBRACE_TOK 272
#define LBRACKET_TOK 273
#define RBRACKET_TOK 274
#define LPAREN_TOK 275
#define RPAREN_TOK 276
#define SEMICOLON_TOK 277
#define COMMA_TOK 278
#define SINGLE_QUOTE_TOK 279
#define DOUBLE_QUOTE_TOK 280
#define MAIN_TOK 281
#define WHILE_TOK 282
#define DO_TOK 283
#define FOR_TOK 284
#define BREAK_TOK 285
#define CONTINUE_TOK 286
#define IF_TOK 287
#define ELSE_TOK 288
#define SWITCH_TOK 289
#define CASE_TOK 290
#define VOID_TOK 291
#define INT_TOK 292
#define FLOAT_TOK 293
#define CHAR_TOK 294
#define RETURN_TOK 295
#define ID_TOK 296
#define LT_EQ_TOK 297
#define GT_EQ_TOK 298
#define EQ_EQ_TOK 299
#define PLUS_EQ_TOK 300
#define MINUS_EQ_TOK 301
#define MULT_EQ_TOK 302
#define DIV_EQ_TOK 303
#define MOD_EQ_TOK 304
#define PLUS_PLUS_TOK 305
#define MINUS_MINUS_TOK 306
#define LOG_AND_TOK 307
#define LOG_OR_TOK 308
#define INTCONST 309
#define FLOATCONST 310
#define CHARCONST 311
#define STRCONST 312




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

