#include <ctype.h>
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
                } else if (c == '+') {
                    state = 6;  //! token for "+"
                } else if (c == '-') {
                    state = 7;  //! token for "-"
                } else if (c == '/') {
                    state = 8;  //! token for "/"
                } else if (c == '*') {
                    state = 9;  //! token for "*"
                } else if (c == '%') {
                    state = 10;  //! token for "%"
                } else if (c == '&') {
                    state = 17;  //! token for "&"
                } else if (c == '|') {
                    state = 19;  //! token for "|"
                } else if (c == '!') {
                    state = 21;  //! token for "!"
                } else if (c == '^') {
                    state = 22;  //! token for "^"
                } else if (isdigit(c)) {
                    state = 23;  //! token for integer constant
                } else if (c == '(') {
                    state = 26;  //! token for "("
                } else if (c == ')') {
                    state = 27;  //! token for ")"
                } else if (c == '{') {
                    state = 29;  //! token for "{"
                } else if (c == '}') {
                    state = 30;  //! token for "}"
                } else if (c == '[') {
                    state = 28;  //! token for "["
                } else if (c == ']') {
                    state = 32;  //! token for "]"
                } else if (c == ';') {
                    state = 31;  //! token for ";"
                } else if (c == 'i') {
                    state = 34;  //! token for "int"
                } else if (c == '_' || isalpha(c)) {
                    state = 33;  //! token for identifier
                } else {
                    fail();
                }

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
            case 6:  //! token for "+"
                c = nextchar();
                if (c == 0) return EOF_TOK;

                if (c == '=') {
                    state = 11;  //! token for "+="
                } else {
                    logger("PLUS_TOK");
                    state_reset();
                    return PLUS_TOK;
                }
                break;
            case 7:  //! token for "-"
                c = nextchar();
                if (c == 0) return EOF_TOK;

                if (c == '=') {
                    state = 12;  //! token for "-="
                } else {
                    logger("MINUS_TOK");
                    state_reset();
                    return MINUS_TOK;
                }
                break;
            case 8:  //! token for "/"
                c = nextchar();
                if (c == 0) return EOF_TOK;

                if (c == '=') {
                    state = 13;  //! token for "/="
                } else {
                    logger("DIV_TOK");
                    state_reset();
                    return DIV_TOK;
                }
                break;
            case 9:  //! token for "*"
                c = nextchar();
                if (c == 0) return EOF_TOK;

                if (c == '=') {
                    state = 14;  //! token for "*="
                } else {
                    logger("MULT_TOK");
                    state_reset();
                    return MULT_TOK;
                }
                break;
            case 10:  //! token for "%"
                c = nextchar();
                if (c == 0) return EOF_TOK;

                if (c == '=') {
                    state = 15;  //! token for "%="
                } else {
                    logger("MOD_TOK");
                    state_reset();
                    return MOD_TOK;
                }
                break;
            case 11:  //! token for "+="
                logger("PLUS_EQ_TOK");
                state_reset();
                return PLUS_EQ_TOK;
            case 12:  //! token for "-="
                logger("MINUS_EQ_TOK");
                state_reset();
                return MINUS_EQ_TOK;
            case 13:  //! token for "/="
                logger("DIV_EQ_TOK");
                state_reset();
                return DIV_EQ_TOK;
            case 14:  //! token for "*="
                logger("MULT_EQ_TOK");
                state_reset();
                return MULT_EQ_TOK;
            case 15:  //! token for "%="
                logger("MOD_EQ_TOK");
                state_reset();
                return MOD_EQ_TOK;
            case 16:  //! token for "=="
                logger("EQ_EQ_TOK");
                state_reset();
                return EQ_EQ_TOK;
            case 17:  //! token for "&"
                c = nextchar();
                if (c == 0) return EOF_TOK;
                if (c == '&') {
                    state = 18;  //! token for "&&"
                } else {
                    set_lookahead(c);
                    logger("AND_TOK");
                    state_reset();
                    return AND_TOK;
                }
                break;
            case 18:  //! token for "&&"
                logger("LOG_AND_TOK");
                state_reset();
                return LOG_AND_TOK;
            case 19:  //! token for "|"
                c = nextchar();
                if (c == 0) return EOF_TOK;
                if (c == '|') {
                    state = 20;  //! token for "||"
                } else {
                    set_lookahead(c);
                    logger("OR_TOK");
                    state_reset();
                    return OR_TOK;
                }
                break;
            case 20:  //! token for "||"
                logger("LOG_OR_TOK");
                state_reset();
                return LOG_OR_TOK;
            case 21:  //! token for "!"
                logger("NOT_TOK");
                state_reset();
                return NOT_TOK;
            case 22:  //! token for "^"
                logger("XOR_TOK");
                state_reset();
                return XOR_TOK;
            case 23:
                c = nextchar();
                if (c == 0) return EOF_TOK;
                if (isdigit(c)) {
                    state = 23;  //! token for integer constant
                } else if (c == '.') {
                    state = 24;  //! token for float constant
                } else {
                    set_lookahead(c);
                    logger("INTCONST");
                    state_reset();
                    return INTCONST;
                }
                break;
            case 24:
                c = nextchar();
                if (c == 0) return EOF_TOK;
                if (isdigit(c)) {
                    state = 25;  //! token for float constant
                } else {
                    fail();
                }
                break;
            case 25:
                c = nextchar();
                if (c == 0) return EOF_TOK;
                if (isdigit(c)) {
                    state = 25;  //! token for float constant
                } else {
                    set_lookahead(c);
                    logger("FLOATCONST");
                    state_reset();
                    return FLOATCONST;
                }
                break;
            case 26:  //! token for "("
                logger("LPAREN_TOK");
                state_reset();
                return LPAREN_TOK;
            case 27:  //! token for ")"
                logger("RPAREN_TOK");
                state_reset();
                return RPAREN_TOK;
            case 28:  //! token or "["
                logger("LBRACKET_TOK");
                state_reset();
                return LBRACKET_TOK;
            case 29:  //! token for "{"
                logger("LBRACE_TOK");
                state_reset();
                return LBRACE_TOK;
            case 30:  //! token for "}"
                logger("RBRACE_TOK");
                state_reset();
                return RBRACE_TOK;
            case 31:  //! token for "!"
                logger("SEMICOLON_TOK");
                state_reset();
                return SEMICOLON_TOK;
            case 32:  //! token for "]"
                logger("RBRACKET_TOK");
                state_reset();
                return RBRACKET_TOK;
            case 33:
                c = nextchar();
                if (c == 0) return EOF_TOK;
                if (isalpha(c) || c == '_') {
                    state = 33;  //! token for identifier
                } else {
                    set_lookahead(c);
                    logger("ID_TOK");
                    state_reset();
                    return ID_TOK;
                }
                break;
            case 34:
                c = nextchar();
                if (c == 0) return EOF_TOK;
                if (c == 'n') {
                    state = 35;  //! reached "in"
                } else if (isalpha(c) || c == '_') {
                    state = 33;  //! token for identifier
                } else {
                    set_lookahead(c);
                    logger("ID_TOK");
                    state_reset();
                    return ID_TOK;
                }
                break;
            case 35:  //! state "in"
                c = nextchar();
                if (c == 0) return EOF_TOK;
                if (c == 't') {
                    state = 36;  //! reached "int"
                } else if (isalpha(c) || c == '_') {
                    state = 33;  //! token for identifier
                } else {
                    set_lookahead(c);
                    logger("ID_TOK");
                    state_reset();
                    return ID_TOK;
                }
                break;
            case 36:  //! token for "int"
                c = nextchar();
                logger("INT_TOK");
                state_reset();
                return INT_TOK;
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