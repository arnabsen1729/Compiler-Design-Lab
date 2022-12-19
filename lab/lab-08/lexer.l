
letter	[a-zA-Z]
digit	[0-9]
intconst [+\-]?{digit}+
realconst [+\-]?{digit}*\.{digit}+(e[+\-]?{digit}+)?
str_const \"(\\.|[^"\\])*\"
char_const \'(\\.|.)\'
delim	[ \t]
eoc */
single_line_comment "//"[^\n]*
multiline_comment "/*"[^{eoc}]*"*/"

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "y.tab.h"

%}

%%

single_line_comment		{;}
multiline_comment		{;}

#					{return(HASH_TOK);}
\.					{return(DOT_TOK);}
;					{return(SEMICOLON_TOK);}

int					{return(INT_TOK);}
float				{return(FLOAT_TOK);}
char				{return(CHAR_TOK);}
double				{return(DOUBLE_TOK);}
for					{return(FOR_TOK);}
do					{return(DO_TOK);}
while				{return(WHILE_TOK);}
if					{return(IF_TOK);}
else				{return(ELSE_TOK);}
return				{return(RET_TOK);}
printf				{return(PRINTF_TOK);}
scanf				{return(SCANF_TOK);}
define				{return(DEF_TOK);}
include				{return(INCLUDE_TOK);}
main				{return(MAIN_TOK);}

"++"				{return(INC_TOK);}
"--"				{return(DEC_TOK);}
== 					{yylval.string = strdup(yytext); return(EQ_TOK);}
\<=					{yylval.string = strdup(yytext); return(LTE_TOK);}
>=					{yylval.string = strdup(yytext); return(GTE_TOK);}
!=					{yylval.string = strdup(yytext); return(NEQ_TOK);}
\<<					{return(LSHIFT_TOK);}
>>					{return(RSHIFT_TOK);}
>					{yylval.string = strdup(yytext); return(GT_TOK);}
\<					{yylval.string = strdup(yytext); return(LT_TOK);}
&&					{yylval.string = strdup(yytext); return(AND_TOK);}
\|\|				{yylval.string = strdup(yytext); return(OR_TOK);}
!					{return(NOT_TOK);}
&					{return(BIT_AND_TOK);}
\|					{return(BIT_OR_TOK);}
\^					{return(XOR_TOK);}
~					{return(NEG_TOK);}
=					{return(ASSIGN_TOK);}
\+=					{return(PLUS_ASSIGN_TOK);}
-=					{return(MINUS_ASSIGN_TOK);}
\*=					{return(MULT_ASSIGN_TOK);}
\/=					{return(DIV_ASSIGN_TOK);}
%=					{return(MOD_ASSIGN_TOK);}
\+					{yylval.string = strdup(yytext); return(PLUS_TOK);}
-					{yylval.string = strdup(yytext); return(MINUS_TOK);}
\*					{yylval.string = strdup(yytext); return(MULT_TOK);}
\/					{yylval.string = strdup(yytext); return(DIV_TOK);}
%					{yylval.string = strdup(yytext); return(MOD_TOK);}
,					{return(COMMA_TOK);}

\{					{return(LCURL_TOK);}
\}					{return(RCURL_TOK);}
\(					{return(LPAREN_TOK);}
\)					{return(RPAREN_TOK);}
\[					{return(LSQUARE_TOK);}
\]					{return(RSQUARE_TOK);}

{intconst}				{yylval.number = atoi(yytext); return(INT_CONST_TOK);}
{realconst}				{yylval.decimal = atof(yytext); return(REAL_CONST_TOK);}
{str_const}				{yylval.string = strdup(yytext); return(STRING_CONST_TOK);}
{char_const}				{yylval.string = strdup(yytext); return(CHAR_CONST_TOK);}
({letter}|_)({letter}|{digit}|_)*	{yylval.string = strdup(yytext); return(ID_TOK);}

"\n"					{yylineno++;}
{delim}+				{;}

%%

/*int main() {
	int val;
	while((val = yylex()) > 0) {
		printf("Token: %s\tToken ID: %d\n", yytext, val);
	}
	
	return 0;
}*/
