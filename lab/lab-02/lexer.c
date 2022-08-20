#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

FILE *yyin;        // input source file ptr
int yylineno = 0;  // line number
char *yytext;      // lexeme
char c = '\0';

char lookahead = -1;  // lookahead character
int state = 0;        // current transition state id
char *token_name;

/**
 * @brief Returns the next non-whitespace character from the yyin.
 *
 * If there already exists a character in the lookahead buffer, it then
 * returns the character, else reads a new character from the yyin.
 *
 * @return char
 */
char nextchar() {
    if (lookahead != -1) {
        char c = lookahead;
        lookahead = -1;
        return c;
    }

    char c = fgetc(yyin);

    if (feof(yyin)) {
        return '\0';
    }

    return c;
}

void append_to_yytext() {
    char temp[] = "0";
    temp[0] = c;
    strcat(yytext, temp);
}

/**
 * @brief Set the lookahead value
 *
 * @param c Character to be set as lookahead
 */
void set_lookahead(char c) {
    lookahead = c;
}

void fail() {
    printf("Lexical error at line %d\n", yylineno);
}

void set_token_name(char *msg) {
    token_name = msg;
}

void state_reset() {
    state = 0;
}

int yylex() {
    yytext = malloc(256);
    c = '\0';
    while (1) {
        if (c != '\0') append_to_yytext();
        switch (state) {
            case 0:  // initial state
                c = nextchar();
                if (c == 0) return EOF_TOK;

                if (c == BLANK || c == TAB) {
                    c = '\0';
                    state_reset();
                } else if (c == NEWLINE) {
                    c = '\0';
                    yylineno++;
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
                } else if (c == 'f') {
                    state = 37;  //! token for "float"
                } else if (c == 'c') {
                    state = 42;  //! token for "char"
                } else if (c == 'e') {
                    state = 48;  //! token for "else"
                } else if (c == 'w') {
                    state = 53;  //! token for "while"
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
                    set_token_name("LT_TOK");
                    state_reset();
                    return LT_TOK;
                }
                break;
            case 2:  //! token for "<="
                set_token_name("LT_EQ_TOK");
                state_reset();
                return LT_EQ_TOK;
            case 3:  //! token for "="
                c = nextchar();
                if (c == 0) return EOF_TOK;

                if (c == '=') {
                    state = 16;  //! token for "=="
                } else {
                    set_lookahead(c);
                    set_token_name("EQ_TOK");
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
                    set_token_name("GT_TOK");
                    state_reset();
                    return GT_TOK;
                }
                break;
            case 5:  //! token for ">="
                set_token_name("GT_EQ_TOK");
                state_reset();
                return GT_EQ_TOK;
            case 6:  //! token for "+"
                c = nextchar();
                if (c == 0) return EOF_TOK;

                if (c == '=') {
                    state = 11;  //! token for "+="
                } else {
                    set_token_name("PLUS_TOK");
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
                    set_token_name("MINUS_TOK");
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
                    set_token_name("DIV_TOK");
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
                    set_token_name("MULT_TOK");
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
                    set_token_name("MOD_TOK");
                    state_reset();
                    return MOD_TOK;
                }
                break;
            case 11:  //! token for "+="
                set_token_name("PLUS_EQ_TOK");
                state_reset();
                return PLUS_EQ_TOK;
            case 12:  //! token for "-="
                set_token_name("MINUS_EQ_TOK");
                state_reset();
                return MINUS_EQ_TOK;
            case 13:  //! token for "/="
                set_token_name("DIV_EQ_TOK");
                state_reset();
                return DIV_EQ_TOK;
            case 14:  //! token for "*="
                set_token_name("MULT_EQ_TOK");
                state_reset();
                return MULT_EQ_TOK;
            case 15:  //! token for "%="
                set_token_name("MOD_EQ_TOK");
                state_reset();
                return MOD_EQ_TOK;
            case 16:  //! token for "=="
                set_token_name("EQ_EQ_TOK");
                state_reset();
                return EQ_EQ_TOK;
            case 17:  //! token for "&"
                c = nextchar();
                if (c == 0) return EOF_TOK;
                if (c == '&') {
                    state = 18;  //! token for "&&"
                } else {
                    set_lookahead(c);
                    set_token_name("AND_TOK");
                    state_reset();
                    return AND_TOK;
                }
                break;
            case 18:  //! token for "&&"
                set_token_name("LOG_AND_TOK");
                state_reset();
                return LOG_AND_TOK;
            case 19:  //! token for "|"
                c = nextchar();
                if (c == 0) return EOF_TOK;
                if (c == '|') {
                    state = 20;  //! token for "||"
                } else {
                    set_lookahead(c);
                    set_token_name("OR_TOK");
                    state_reset();
                    return OR_TOK;
                }
                break;
            case 20:  //! token for "||"
                set_token_name("LOG_OR_TOK");
                state_reset();
                return LOG_OR_TOK;
            case 21:  //! token for "!"
                set_token_name("NOT_TOK");
                state_reset();
                return NOT_TOK;
            case 22:  //! token for "^"
                set_token_name("XOR_TOK");
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
                    set_token_name("INTCONST");
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
                    set_token_name("FLOATCONST");
                    state_reset();
                    return FLOATCONST;
                }
                break;
            case 26:  //! token for "("
                set_token_name("LPAREN_TOK");
                state_reset();
                return LPAREN_TOK;
            case 27:  //! token for ")"
                set_token_name("RPAREN_TOK");
                state_reset();
                return RPAREN_TOK;
            case 28:  //! token or "["
                set_token_name("LBRACKET_TOK");
                state_reset();
                return LBRACKET_TOK;
            case 29:  //! token for "{"
                set_token_name("LBRACE_TOK");
                state_reset();
                return LBRACE_TOK;
            case 30:  //! token for "}"
                set_token_name("RBRACE_TOK");
                state_reset();
                return RBRACE_TOK;
            case 31:  //! token for "!"
                set_token_name("SEMICOLON_TOK");
                state_reset();
                return SEMICOLON_TOK;
            case 32:  //! token for "]"
                set_token_name("RBRACKET_TOK");
                state_reset();
                return RBRACKET_TOK;
            case 33:  //! token for identifier
                c = nextchar();
                if (c == 0) return EOF_TOK;
                if (isalpha(c) || c == '_') {
                    state = 33;  //! token for identifier
                } else {
                    set_lookahead(c);
                    set_token_name("ID_TOK");
                    state_reset();
                    return ID_TOK;
                }
                break;
            case 34:  //! state "i"
                c = nextchar();
                if (c == 0) return EOF_TOK;
                if (c == 'n') {
                    state = 35;  //! reached "in"
                } else if (c == 'f') {
                    state = 52;  //! token for "if"
                } else if (isalpha(c) || c == '_') {
                    state = 33;  //! token for identifier
                } else {
                    set_lookahead(c);
                    set_token_name("ID_TOK");
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
                    set_token_name("ID_TOK");
                    state_reset();
                    return ID_TOK;
                }
                break;
            case 36:  //! token for "int"
                set_token_name("INT_TOK");
                state_reset();
                return INT_TOK;
            case 37:  //! state "f"
                c = nextchar();
                if (c == 0) return EOF_TOK;
                if (c == 'l') {
                    state = 38;  //! reached "fl"
                } else if (c == 'o') {
                    state = 46;  //! reached "fo"
                } else if (isalpha(c) || c == '_') {
                    state = 33;  //! token for identifier
                } else {
                    set_lookahead(c);
                    set_token_name("ID_TOK");
                    state_reset();
                    return ID_TOK;
                }
                break;
            case 38:  //! state "fl"
                c = nextchar();
                if (c == 0) return EOF_TOK;
                if (c == 'o') {
                    state = 39;  //! reached "flo"
                } else if (isalpha(c) || c == '_') {
                    state = 33;  //! token for identifier
                } else {
                    set_lookahead(c);
                    set_token_name("ID_TOK");
                    state_reset();
                    return ID_TOK;
                }
                break;
            case 39:  //! state "flo"
                c = nextchar();
                if (c == 0) return EOF_TOK;
                if (c == 'a') {
                    state = 40;  //! reached "floa"
                } else if (isalpha(c) || c == '_') {
                    state = 33;  //! token for identifier
                } else {
                    set_lookahead(c);
                    set_token_name("ID_TOK");
                    state_reset();
                    return ID_TOK;
                }
                break;
            case 40:  //! state "floa"
                c = nextchar();
                if (c == 0) return EOF_TOK;
                if (c == 't') {
                    state = 41;  //! reached "float"
                } else if (isalpha(c) || c == '_') {
                    state = 33;  //! token for identifier
                } else {
                    set_lookahead(c);
                    set_token_name("ID_TOK");
                    state_reset();
                    return ID_TOK;
                }
                break;
            case 41:  //! token for "float"
                set_token_name("FLOAT_TOK");
                state_reset();
                return FLOAT_TOK;
            case 42:  //! state "c"
                c = nextchar();
                if (c == 0) return EOF_TOK;
                if (c == 'h') {
                    state = 43;  //! reached "ch"
                } else if (isalpha(c) || c == '_') {
                    state = 33;  //! token for identifier
                } else {
                    set_lookahead(c);
                    set_token_name("ID_TOK");
                    state_reset();
                    return ID_TOK;
                }
                break;
            case 43:  //! state "ch"
                c = nextchar();
                if (c == 0) return EOF_TOK;
                if (c == 'a') {
                    state = 44;  //! reached "cha"
                } else if (isalpha(c) || c == '_') {
                    state = 33;  //! token for identifier
                } else {
                    set_lookahead(c);
                    set_token_name("ID_TOK");
                    state_reset();
                    return ID_TOK;
                }
                break;
            case 44:  //! state "cha"
                c = nextchar();
                if (c == 0) return EOF_TOK;
                if (c == 'r') {
                    state = 45;  //! reached "char"
                } else if (isalpha(c) || c == '_') {
                    state = 33;  //! token for identifier
                } else {
                    set_lookahead(c);
                    set_token_name("ID_TOK");
                    state_reset();
                    return ID_TOK;
                }
                break;
            case 45:  //! token for "char"
                set_token_name("CHAR_TOK");
                state_reset();
                return CHAR_TOK;
            case 46:  //! state "fo"
                c = nextchar();
                if (c == 0) return EOF_TOK;
                if (c == 'r') {
                    state = 47;  //! reached "for"
                } else if (isalpha(c) || c == '_') {
                    state = 33;  //! token for identifier
                } else {
                    set_lookahead(c);
                    set_token_name("ID_TOK");
                    state_reset();
                    return ID_TOK;
                }
                break;
            case 47:  //! token for "for"
                set_token_name("FOR_TOK");
                state_reset();
                return FOR_TOK;
            case 48:  //! state "e"
                c = nextchar();
                if (c == 0) return EOF_TOK;
                if (c == 'l') {
                    state = 49;  //! reached "el"
                } else if (isalpha(c) || c == '_') {
                    state = 33;  //! token for identifier
                } else {
                    set_lookahead(c);
                    set_token_name("ID_TOK");
                    state_reset();
                    return ID_TOK;
                }
                break;
            case 49:  //! state "el"
                c = nextchar();
                if (c == 0) return EOF_TOK;
                if (c == 's') {
                    state = 50;  //! reached "els"
                } else if (isalpha(c) || c == '_') {
                    state = 33;  //! token for identifier
                } else {
                    set_lookahead(c);
                    set_token_name("ID_TOK");
                    state_reset();
                    return ID_TOK;
                }
                break;
            case 50:  //! state "els"
                c = nextchar();
                if (c == 0) return EOF_TOK;
                if (c == 'e') {
                    state = 51;  //! reached "else"
                } else if (isalpha(c) || c == '_') {
                    state = 33;  //! token for identifier
                } else {
                    set_lookahead(c);
                    set_token_name("ID_TOK");
                    state_reset();
                    return ID_TOK;
                }
                break;
            case 51:  //! token for "else"
                set_token_name("ELSE_TOK");
                state_reset();
                return ELSE_TOK;
            case 52:  //! token for "if"
                set_token_name("IF_TOK");
                state_reset();
                return IF_TOK;
            case 53:  //! state "w"
                c = nextchar();
                if (c == 0) return EOF_TOK;
                if (c == 'h') {
                    state = 54;  //! reached "wh"
                } else if (isalpha(c) || c == '_') {
                    state = 33;  //! token for identifier
                } else {
                    set_lookahead(c);
                    set_token_name("ID_TOK");
                    state_reset();
                    return ID_TOK;
                }
                break;
            case 54:  //! state "wh"
                c = nextchar();
                if (c == 0) return EOF_TOK;
                if (c == 'i') {
                    state = 55;  //! reached "whi"
                } else if (isalpha(c) || c == '_') {
                    state = 33;  //! token for identifier
                } else {
                    set_lookahead(c);
                    set_token_name("ID_TOK");
                    state_reset();
                    return ID_TOK;
                }
                break;
            case 55:  //! state "whi"
                c = nextchar();
                if (c == 0) return EOF_TOK;
                if (c == 'l') {
                    state = 56;  //! reached "whil"
                } else if (isalpha(c) || c == '_') {
                    state = 33;  //! token for identifier
                } else {
                    set_lookahead(c);
                    set_token_name("ID_TOK");
                    state_reset();
                    return ID_TOK;
                }
                break;
            case 56:  //! state "whil"
                c = nextchar();
                if (c == 0) return EOF_TOK;
                if (c == 'e') {
                    state = 57;  //! reached "while"
                } else if (isalpha(c) || c == '_') {
                    state = 33;  //! token for identifier
                } else {
                    set_lookahead(c);
                    set_token_name("ID_TOK");
                    state_reset();
                    return ID_TOK;
                }
                break;
            case 57:  //! token for "while"
                set_token_name("WHILE_TOK");
                state_reset();
                return WHILE_TOK;
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

    yyin = fopen(argv[1], "r");
    if (yyin == NULL) {
        printf("Error: could not open file %s\n", argv[1]);
        return 1;
    }
    printf("%-10s %-20s %-10s %-10s\n",
           "Line #",
           "Token Name",
           "Token ID", "Value");
    printf("=================================================\n");
    int token;
    while (!feof(yyin)) {
        token = yylex();
        if (token == 0) break;
        printf("%-10d %-20s %-10d %s \n", yylineno, token_name, token, yytext);
    }

    return 0;
}