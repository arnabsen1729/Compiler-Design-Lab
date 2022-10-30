%{

#include "lex.yy.c"
#include "hash.c"
#include <stdbool.h>

void yyerror(char *);

void parsed(const char * msg) {
    printf("[line: %d] => %s syntax is OK\n", yylineno, msg);
}

int scope = 0;
int dtype = 0;
int type = -1;
symbol_table *table;

void add_variable(symbol_table *t, char *name, int dtype) {
    symbol *var = create_symbol(name, dtype, scope, yylineno);
    insert_table(t, var);
}

bool is_declared(symbol_table *t, char *name) {
    symbol *var = lookup_table(t, name, scope);
    if (var == NULL) {
        return false;
    }
    return true;
}

void delete_variables(symbol_table *t) {
    remove_table(t, scope);
}

int get_type(symbol_table *t, char *name, int scope) {
    symbol *var = lookup_table(t, name, scope);
    if (var == NULL) {
        return -1;
    }
    return var->dtype;
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

// [ Increment & Decrement Operators ]

%token PLUS_PLUS_TOK
%token MINUS_MINUS_TOK

// [ Logical Operators ]

%token LOG_AND_TOK
%token LOG_OR_TOK

// [ Identifier, constants ]
%token INTCONST
%token FLOATCONST
%token CHARCONST
%token STRCONST

//start symbol
%start S

%%
S               : S statement
                | S main
                | S function
                | statement
                | main
                | function
                ;

open_paren      : LBRACE_TOK    { scope++; }
                ;

close_paren     : RBRACE_TOK    { delete_variables(table); scope--; }
                ;


main            : datatype  MAIN_TOK LPAREN_TOK RPAREN_TOK block       {parsed("main function");}
                ;


block           : open_paren  statements  blocks  close_paren 
                ;

blocks          : block statements blocks
                | // required for empty block
                ;

statements      : statements statement
                | statements if_statement
                | statements for_statement
                | statements while_statement
                | // required for empty statement
                ;

statement       : operation SEMICOLON_TOK {type = -1;}
                | return_statement
                ;

operation       : declaration 
                | assignment
                | expression
                | condition
                ;

declaration     : datatype id_token                      {
    parsed("declaration statement");
    add_variable(table, var_name, dtype);
    iterate_table(table);
}
                ;

assignment      : datatype id_token EQ_TOK expression    {
    if (type == -1) {
        type = dtype;
    } else if (type != dtype) {
        yyerror("type mismatch");
        return 1;
    }

    add_variable(table, var_name, dtype);
    iterate_table(table);
    parsed("assignment statement");
}
                | id_token EQ_TOK expression              {
    int current_type = get_type(table, var_name, scope);
    if (type == -1) {
        type = current_type;
    } else if (type != current_type) {
        yyerror("type mismatch");
        return 1;
    }

    if(!is_declared(table, var_name)) {
        yyerror("variable not declared");
        return 1;
    } 
    parsed("assignment statement");
}
                ;     

return_statement: RETURN_TOK expression SEMICOLON_TOK    {parsed("return statement");}
                ;

function        : datatype id_token LPAREN_TOK params RPAREN_TOK block {parsed("function");}
                ;

params          : datatype id_token COMMA_TOK params
                | datatype id_token     
                | // required for empty params
                ;                

function_call   : id_token LPAREN_TOK args RPAREN_TOK {parsed("function call");}
                ;

args            : expression COMMA_TOK args
                | expression
                | // required for empty args
                ;           

expression      : function_call
                | id_token                                                     {
                    if(!is_declared(table, var_name)) {
                        yyerror("variable not declared");
                        return 1;
                    }

                    if(type == -1) {
                        type = get_type(table, var_name, scope);
                    } else {
                        int current_type = get_type(table, var_name, scope);
                        if (current_type != type) {
                            yyerror("type mismatch");
                            return 1;
                        }
                    }
                }
                | INTCONST  {
                    if(type == -1) {
                        type = INT_TOK;
                    } else if (type != INT_TOK) {
                        yyerror("type mismatch");
                        return 1;
                    }
                }
                | FLOATCONST {
                    if(type == -1) {
                        type = FLOAT_TOK;
                    } else if (type != FLOAT_TOK) {
                        yyerror("type mismatch");
                        return 1;
                    }
                }
                | CHARCONST {
                    if(type == -1) {
                        type = CHAR_TOK;
                    } else if (type != CHAR_TOK) {
                        yyerror("type mismatch");
                        return 1;
                    }
                }
                | STRCONST {
                    if(type == -1) {
                        type = CHAR_TOK;
                    } else if (type != CHAR_TOK) {
                        yyerror("type mismatch");
                        return 1;
                    }
                }
                | SEMICOLON_TOK
                | LPAREN_TOK expression RPAREN_TOK
                | expression arithmetic_op expression
                | expression relational_op expression
                | expression PLUS_PLUS_TOK
                | expression MINUS_MINUS_TOK
                ;  

if_statement    : IF_TOK LPAREN_TOK condition RPAREN_TOK block                  {parsed("if statement");}
                | IF_TOK LPAREN_TOK condition RPAREN_TOK block ELSE_TOK block   {parsed("if-else statement");}
                | IF_TOK LPAREN_TOK condition RPAREN_TOK block ELSE_TOK if_statement {parsed("else-if statement");}
                ;

for_statement   : FOR_TOK LPAREN_TOK operation SEMICOLON_TOK operation SEMICOLON_TOK operation RPAREN_TOK block {parsed("for statement");}
                ;

while_statement : WHILE_TOK LPAREN_TOK condition RPAREN_TOK block {parsed("while statement");}
                ;

condition       : expression relational_op expression
                | expression
                ;

arithmetic_op   : PLUS_TOK
                | MINUS_TOK
                | MULT_TOK
                | DIV_TOK
                | MOD_TOK
                | PLUS_EQ_TOK
                | MINUS_EQ_TOK
                | MULT_EQ_TOK
                | DIV_EQ_TOK
                | MOD_EQ_TOK
                ;

relational_op   : LT_TOK
                | GT_TOK
                | EQ_TOK
                | LT_EQ_TOK
                | GT_EQ_TOK
                | EQ_EQ_TOK
                ;

datatype        : INT_TOK       { dtype = INT_TOK;}
                | VOID_TOK      { dtype = VOID_TOK;}
                | CHAR_TOK      { dtype = CHAR_TOK;}
                | FLOAT_TOK     { dtype = FLOAT_TOK;}
                ;

id_token        : id_token COMMA_TOK ID_TOK
                | ID_TOK      { 
                    int current_type = get_type(table, var_name, scope);
                    if (type == -1) {
                        type = current_type;
                    } else if (type != current_type) {
                        yyerror("type mismatch");
                        return 1;
                    }
}
                ;

%%

void yyerror(char *s) {
	printf("SYNTAX ERROR: %s LINE NUMBER: %d\n", s, yylineno);
}

int main()
{
    table = create_table();

    if (yyparse()==0) printf("\nPARSING COMPLETED SUCCESSFULLY ✅\n");
    else printf("\nPARSING ERROR (at line no:  %d) ❌\n", yylineno);

    return(0);	

}