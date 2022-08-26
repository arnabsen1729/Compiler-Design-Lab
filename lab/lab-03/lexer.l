letter      [a-zA-Z]
digit       [0-9]
identifier  [a-zA-Z_][a-zA-Z0-9_]*
intconst    [+\-]?{digit}+
floatconst   [+\-]?{digit}*\.{digit}+(e[+\-]?{digit}+)?
delimiter   [ \t\n]

%{
    #include <stdio.h>
    #include <stdlib.h>

    #include "tokens.h"

    int yylineno;
%}

%%
;               return (SEMICOLON_TOK);
"<"             return (LT_TOK);
">"             return (GT_TOK);
"="             return (EQ_TOK);
"-"             return (MINUS_TOK);
"+"             return (PLUS_TOK);
"*"             return (MULT_TOK);
"/"             return (DIV_TOK);
"%"             return (MOD_TOK);
"~"             return (BNOT_TOK);
"!"             return (NOT_TOK);
"&"             return (AND_TOK);
"|"             return (OR_TOK);
"^"             return (XOR_TOK);
"{"             return (LBRACE_TOK);
"}"             return (RBRACE_TOK);
"["             return (LBRACKET_TOK);
"]"             return (RBRACKET_TOK);
"("             return (LPAREN_TOK);
")"             return (RPAREN_TOK);
"<="            return (LT_EQ_TOK);
">="            return (GT_EQ_TOK);
"=="            return (EQ_EQ_TOK);
"+="            return (PLUS_EQ_TOK);
"-="            return (MINUS_EQ_TOK);
"*="            return (MULT_EQ_TOK);
"/="            return (DIV_EQ_TOK);
"%="            return (MOD_EQ_TOK);
"&&"            return (LOG_AND_TOK);
"||"            return (LOG_OR_TOK);
while           return (WHILE_TOK);
for             return (FOR_TOK);
if              return (IF_TOK);
else            return (ELSE_TOK);
int             return (INT_TOK);
float           return (FLOAT_TOK);
char            return (CHAR_TOK);
return          return (RETURN_TOK);
{identifier}    return (ID_TOK);
{intconst}      return (INTCONST);
{floatconst}    return (FLOATCONST);
{delimiter}+ ;
%%

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s <source-file>\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (yyin == NULL) {
        printf("Error: could not open file %s\n", argv[1]);
        return 1;
    }

    printf("%-10s %-10s %-10s\n",
           "Line #",
           "Token ID", 
           "Value");
    printf("====================================\n");


    int token;
    while ((token = yylex())) {
        printf("%-10d %-10d %s \n", yylineno, token, yytext);
    }

    return 0;
}