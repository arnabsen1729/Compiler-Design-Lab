#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexemes.h"
#include "utils.h"

FILE *yyin;
char *yytext;

int checkReservedKeyword(char *word) {
    if (strcmp(word, "while") == 0) return WHILE_TOK;
    if (strcmp(word, "for") == 0) return FOR_TOK;
    if (strcmp(word, "if") == 0) return IF_TOK;
    if (strcmp(word, "else") == 0) return ELSE_TOK;
    if (strcmp(word, "int") == 0) return INT_TOK;
    if (strcmp(word, "float") == 0) return FLOAT_TOK;

    return 0;
}

int checkSingleCharacterLexemes(char *word) {
    if (strcmp(word, "(") == 0) return LPAREN_TOK;
    if (strcmp(word, ")") == 0) return RPAREN_TOK;
    if (strcmp(word, ">") == 0) return GT_TOK;
    if (strcmp(word, "<") == 0) return LT_TOK;
    if (strcmp(word, "=") == 0) return EQ_TOK;
    if (strcmp(word, "-") == 0) return MINUS_TOK;
    if (strcmp(word, "+") == 0) return PLUS_TOK;
    if (strcmp(word, "*") == 0) return MULTIPLY_TOK;
    if (strcmp(word, "/") == 0) return DIVISION_TOK;
    if (strcmp(word, ";") == 0) return SEMICOLON_TOK;

    return 0;
}

int checkValidIdentifier(char *word) {
    // first letter of identifier should be letter or underscore
    if (word[0] != '_' && !isLetter(word[0])) return 0;

    // can only contain letters (uppercase and lowercase), digits and underscore
    for (int i = 0; i < (int)strlen(word); i++) {
        if (word[0] != '_' && !isAlphanumeric(word[0])) return 0;
    }

    return ID_TOK;
}

int checkConstant(char *word) {
    int base = INTCONST;
    int mask = (1 << CONSTANTS_COUNT) - 1;
    int period = 0;
    for (int i = 0; i < (int)strlen(word); i++) {
        if (word[i] == '.' && period < 1) {
            // INT check
            if (mask & (1 << (INTCONST - base)))
                mask ^= (1 << (INTCONST - base));  // if the word has a period (.) then it can't be int
            period++;
        } else if (!isDigit(word[i])) {
            return 0;
        }
    }

    if (period == 0) mask ^= (1 << (FLOATCONST - base));

    for (int i = 0; i < CONSTANTS_COUNT; i++) {
        if (mask & (1 << i)) return base + i;
    }

    return 0;
}

int yylex() {
    char *word = malloc(256);
    int flag;
    fscanf(yyin, "%s", word);
    yytext = word;

    if ((flag = checkReservedKeyword(word))) return flag;
    if ((flag = checkSingleCharacterLexemes(word))) return flag;
    if ((flag = checkValidIdentifier(word))) return flag;
    if ((flag = checkConstant(word))) return flag;

    return 0;
}

int main(int argc, char *argv[]) {
    int token;
    if (argc != 2) {
        printf("USAGE: %s <source-file>\n", argv[0]);
    } else {
        yyin = fopen(argv[1], "r");

        if (yyin == NULL) {
            printf("%s: no such file\n", argv[1]);
            return 1;
        }

        while (!feof(yyin)) {
            token = yylex();
            if (token)
                printf("[TOKEN] [%s] -> [%d]\n", yytext, token);
            else
                printf("[TOKEN NOT FOUND YET]\n");
        }
        fclose(yyin);
    }
}