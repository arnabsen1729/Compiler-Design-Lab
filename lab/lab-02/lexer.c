#include <stdio.h>

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

FILE *file;           // source file pointer
char lookahead = -1;  // lookahead character
int state;
int yylineno;

/**
 * @brief Returns the next non-whitespace character from the file.
 *
 * @return char
 */
char nextchar() {
    if (lookahead != -1) {
        char c = lookahead;
        lookahead = -1;
        return c;
    }

    char c = fgetc(file);

    if (feof(file)) {
        return '\0';
    }

    return c;
}

void set_lookahead(char c) {
    lookahead = c;
}

void fail() {
    printf("Lexical error at line %d\n", yylineno);
}

void logger(char *msg) {
    printf("[%s]\n", msg);
}

void state_reset() {
    state = 0;
}

int yylex() {
    while (1) {
        char c;
        switch (state) {
            case 0:  // initial state
                c = nextchar();
                if (c == 0) return EOF_TOK;

                if (c == BLANK || c == TAB || c == NEWLINE) {
                    state_reset();
                } else if (c == '<') {
                    state = 1;  //! token for "<"
                } else if (c == '=') {
                    state = 3;  //! token for "="
                } else if (c == '>') {
                    state = 4;  //! token for ">"
                } else
                    fail();
                break;
            case 1:  //! token for "<"
                c = nextchar();
                if (c == 0) return EOF_TOK;

                if (c == '=') {
                    state = 2;  //! token for "<="
                } else {
                    set_lookahead(c);
                    logger("LT_TOK");
                    state_reset();
                    return LT_TOK;
                }
                break;
            case 2:  //! token for "<="
                logger("LT_EQ_TOK");
                state_reset();
                return LT_EQ_TOK;
            case 3:  //! token for "="
                c = nextchar();
                if (c == 0) return EOF_TOK;

                if (c == '=') {
                    state = 16;  //! token for "=="
                } else {
                    set_lookahead(c);
                    logger("EQ_TOK");
                    state_reset();
                    return EQ_TOK;
                }
                break;
            case 4:  //! token for ">"
                c = nextchar();
                if (c == 0) return EOF_TOK;

                if (c == '=') {
                    state = 5;  //! token for ">="
                } else {
                    set_lookahead(c);
                    logger("GT_TOK");
                    state_reset();
                    return GT_TOK;
                }
                break;
            case 5:  //! token for ">="
                logger("GT_EQ_TOK");
                state_reset();
                return GT_EQ_TOK;
            case 16:  //! token for "=="
                logger("EQ_EQ_TOK");
                state_reset();
                return EQ_EQ_TOK;
            default:
                fail();
                return -1;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <source-file>\n", argv[0]);
        return 1;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error: could not open file %s\n", argv[1]);
        return 1;
    }

    int token;
    while (!feof(file)) {
        token = yylex();
        printf("%d\n", token);
    }

    return 0;
}