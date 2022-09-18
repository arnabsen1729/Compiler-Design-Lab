letter      [a-zA-Z]
digit       [0-9]
identifier  [a-zA-Z_][a-zA-Z0-9_]*
intconst    [+\-]?{digit}+
floatconst  [+\-]?{digit}*\.{digit}+(e[+\-]?{digit}+)?
charconst   \'{letter}\'
stringconst \".*\"
delimiter   [ \t]

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include "y.tab.h"

    int yylineno;
    char var_name[20];
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
"\'"            return (SINGLE_QUOTE_TOK);
"\""            return (DOUBLE_QUOTE_TOK);    
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
","             return (COMMA_TOK);
"++"            return (PLUS_PLUS_TOK);
"--"            return (MINUS_MINUS_TOK);
main            return (MAIN_TOK);
while           return (WHILE_TOK);
for             return (FOR_TOK);
if              return (IF_TOK);
else            return (ELSE_TOK);
int             return (INT_TOK);
float           return (FLOAT_TOK);
char            return (CHAR_TOK);
return          return (RETURN_TOK);
{identifier}    {strcpy(var_name, yytext); return (ID_TOK);}
{intconst}      return (INTCONST);
{floatconst}    return (FLOATCONST);
{charconst}     return (CHARCONST);
{stringconst}   return (STRCONST);
\n              {yylineno++;}
{delimiter}+ ;
%%