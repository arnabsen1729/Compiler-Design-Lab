#define EOF_TOK 0
#define BLANK ' '
#define NEWLINE '\n'
#define TAB '\t'

/* Single Character Lexemes */

// [ Relational & Assingment Operators ]
#define LT_TOK '<'
#define GT_TOK '>'
#define EQ_TOK '='

// [ Arithmetic Operators ]
#define MINUS_TOK '-'
#define PLUS_TOK '+'
#define MULT_TOK '*'
#define DIV_TOK '/'
#define MOD_TOK '%'

// [ Bitwise Operators ]
#define BNOT_TOK '~'
#define NOT_TOK '!'
#define AND_TOK '&'
#define OR_TOK '|'
#define XOR_TOK '^'

// [Delimiters]
#define LBRACE_TOK '{'
#define RBRACE_TOK '}'
#define LBRACKET_TOK '['
#define RBRACKET_TOK ']'
#define LPAREN_TOK '('
#define RPAREN_TOK ')'
#define SEMICOLON_TOK ';'

/* Reserved words */
#define WHILE_TOK 256
#define FOR_TOK 257
#define IF_TOK 258
#define ELSE_TOK 259
#define INT_TOK 260
#define FLOAT_TOK 261
#define CHAR_TOK 262
#define RETURN_TOK 263

/* Multi-Character Lexemes */

// [Relational Operators]

#define LT_EQ_TOK 280
#define GT_EQ_TOK 281
#define EQ_EQ_TOK 282

// [Arithmetic Assignment Operators]

#define PLUS_EQ_TOK 283
#define MINUS_EQ_TOK 284
#define MULT_EQ_TOK 285
#define DIV_EQ_TOK 286
#define MOD_EQ_TOK 287

// [ Logical Operators ]

#define LOG_AND_TOK 288
#define LOG_OR_TOK 289

/* Identifier, constants..*/
#define ID_TOK 350
#define INTCONST 351
#define FLOATCONST 352
#define CHARCONST 353
#define STRCONST 354
