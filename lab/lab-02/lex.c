#include "lex.h"

#include <stdio.h>

char *yytext = ""; /* lexeme */
int yyleng = 0;    /* lexeme length */
int yylineno = 0;  /* line number */

