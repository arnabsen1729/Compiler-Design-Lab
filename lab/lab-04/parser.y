%{

#include "lex.yy.c"

void yyerror(char *);

void parsed(const char * msg) {
    printf("[line: %d] => %s syntax is OK\n",yylineno, msg);
}

%}

// [ Relational & Assingment Operators ]
%token LT_TOK
%token GT_TOK
%token EQ_TOK

// [ Arithmetic Operators ]
%token MINUS_TOK
%token PLUS_TOK
%token MULT_TOK
%token DIV_TOK
%token MOD_TOK

// [ Bitwise Operators ]
%token BNOT_TOK
%token NOT_TOK
%token AND_TOK
%token OR_TOK
%token XOR_TOK

// [ Delimiters ]
%token LBRACE_TOK
%token RBRACE_TOK
%token LBRACKET_TOK
%token RBRACKET_TOK
%token LPAREN_TOK
%token RPAREN_TOK
%token SEMICOLON_TOK
%token COMMA_TOK
%token SINGLE_QUOTE_TOK
%token DOUBLE_QUOTE_TOK

// [ Reserved words ]
%token MAIN_TOK
%token WHILE_TOK
%token DO_TOK
%token FOR_TOK
%token BREAK_TOK
%token CONTINUE_TOK
%token IF_TOK
%token ELSE_TOK
%token SWITCH_TOK
%token CASE_TOK

// [ Datatype tokens ]
%token VOID_TOK
%token INT_TOK
%token FLOAT_TOK
%token CHAR_TOK
%token RETURN_TOK
%token ID_TOK

// [ Relational Operators ]

%token LT_EQ_TOK
%token GT_EQ_TOK
%token EQ_EQ_TOK

// [ Arithmetic Assignment Operators ]

%token PLUS_EQ_TOK
%token MINUS_EQ_TOK
%token MULT_EQ_TOK
%token DIV_EQ_TOK
%token MOD_EQ_TOK

// [ Logical Operators ]

%token LOG_AND_TOK
%token LOG_OR_TOK

// [ Identifier, constants ]
%token ID_TOK
%token INTCONST
%token FLOATCONST
%token CHARCONST
%token STRCONST

//start symbol
%start S

%%
S               : S statement
                | S main
                | statement
                | main
                ;

main            : datatype  MAIN_TOK LPAREN_TOK RPAREN_TOK block       {parsed("main function");}
                ;

block           : LBRACE_TOK  statements  blocks  RBRACE_TOK
                ;

blocks          : block statements blocks
                | // required for empty block
                ;

statements      : statements  statement
                | // required for empty statement
                ;

statement       : declaration SEMICOLON_TOK
                | assignment SEMICOLON_TOK
                ;


declaration     : datatype id_token      {parsed("declaration statement");}
                ;

assignment      : datatype id_token EQ_TOK data    {parsed("assignment statement");}
                ;              

data            : id_token
                | INTCONST
                | FLOATCONST
                | CHARCONST
                | STRCONST
                ;  

datatype        : INT_TOK
                | VOID_TOK
                | CHAR_TOK
                | FLOAT_TOK
                ;

id_token        : id_token COMMA_TOK ID_TOK
                | ID_TOK
                ;

%%

void yyerror(char *s) {
	printf("yyerror: %s\n", s);
}

int main()
{
   if (yyparse()==0) printf("\nPARSING COMPLETED SUCCESSFULLY ✅\n");
   else printf("\nPARSING ERROR (at line no:  %d) ❌\n", yylineno);

   return(0);	

}