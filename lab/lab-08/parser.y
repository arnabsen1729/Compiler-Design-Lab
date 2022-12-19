%{
#include "lex.yy.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//defining the max size of symbol table
#define TABLE_SIZE 500

void yyerror(char *s);

//keep trackk of scope during parsing
int scope = 0;

//variable to keep track of datatype
int dtype;
int flag = 0;

/* Defining the Symbol Table data structure */

//structure defining the individual units of the symbol table
typedef struct val {
	char name[20];
	int dtype;
	int scope;
	//int isPointer;
	struct val *next;
} Symbol;

//defining the structure of the symbol table
typedef struct table {
	Symbol *entry[TABLE_SIZE];
	int size;
} SymTable;

//the global variable for the symbol table
SymTable table;

/*	defining the hash function for the symbol table:
	http://www.cse.yorku.ca/~oz/hash.html => using the djb2 algorithm
*/
int hash (char *str) {
	int h = 5381;
	int c;
	
	while((c = *str++)) {
		h = ((h << 5) + h) + c;	//hash * 33 + c
	}
	
	return h % TABLE_SIZE;
}

//initializing the symbol table
void initTable() {
	for(int i=0;i<TABLE_SIZE;i++) {
		table.entry[i] = NULL;
	}
	table.size = 0;
}

//function to print symmbol table
void printTable() {
	printf("Entry no.\tSymbol name\tDatatype\tScope\n");
	for(int i=0;i<TABLE_SIZE;i++) {
		if(table.entry[i] != NULL) {
			Symbol *head = table.entry[i];
			while(head != NULL) {
				printf("%d\t\t%s\t\t%d\t\t%d\n", i, head->name, head->dtype, head->scope);
				head = head->next;
			}
		}
	}
}

//function to check is a symbol is present in the symbol table
int isPresent(char *sym) {
	int hval = hash(sym);
	Symbol *head = table.entry[hval];

	if(head == NULL) {
		return 0;
	}

	while(head != NULL) {
		if(strcmp(head->name, sym) == 0)
			return 1;
		
		head = head->next;
	}

	return 0;
}

//function to check for a redeclaration
int alreadyDeclared(char *sym) {
	int hval = hash(sym);
	Symbol *head = table.entry[hval];
	
	if(head == NULL) {
		return 0;
	}

	while(head != NULL) {
		//checking if the same symbol name exists in the same scope
		if(strcmp(head->name, sym) == 0 && head->scope == scope) {
			
			//checking if the datatype is also same
			if(head->dtype == dtype)
				return 1;

			else
				return 2;
		}

		head = head->next;
	}

	return 0;
}

//function to add a new entry in the table
int addSymbol(char *sym) {

	if(table.size == TABLE_SIZE) {
		return -1;
	}
	
	int hval = hash(sym);
	Symbol *head = table.entry[hval];
	
	Symbol *tmp = (Symbol *)malloc(sizeof(Symbol));
	strcpy(tmp->name, sym);
	tmp->dtype = dtype;
	tmp->scope = scope;
	tmp->next = NULL;

	//in case there is no collision
	if(head == NULL) {
		head = tmp;
		table.size++;
		table.entry[hval] = head;
		//printTable();
		return 0;
	}

	//in case of a collision, add to the end of list
	while(head->next != NULL) {
		head = head->next;
	}

	head->next = tmp;
	//printTable();
	return 0;
}

// function to add a user defined function identifier to symbol table
int addFunction(char *sym) {
	if(table.size == TABLE_SIZE) {
		return -1;
	}
	
	int hval = hash(sym);
	Symbol *head = table.entry[hval];
	Symbol *tmp = (Symbol *)malloc(sizeof(Symbol));
	strcpy(tmp->name, sym);
	tmp->dtype = dtype;
	tmp->scope = 0;
	tmp->next = NULL;
	
	//in case there is no collision
	if(head == NULL) {
		head = tmp;
		table.size++;
		table.entry[hval] = head;
		//printTable();
		return 0;
	}

	//in case of a collision, add to the end of list
	while(head->next != NULL) {
		head = head->next;
	}

	head->next = tmp;
	//printTable();
	return 0;
}

//function to get the datatype of a symbol from symbol table
int getDatatype(char *sym) {
	int hval = hash(sym);
	Symbol *head = table.entry[hval];
	while(head != NULL && strcmp(head->name, sym) != 0) {
		head = head->next;
	}
	if(head == NULL) return 0;
	return head->dtype;
}

//function to delete all nodes from a list with matching scope
void deleteNodes(int i, int key) {
	Symbol *tmp, *p, *q;
	Symbol *head = table.entry[i];

	while(head != NULL && head->scope == key) {
		tmp = head;
		head = head->next;
		free(tmp);
	}

	if(head == NULL) {
		table.entry[i] = head;
		return;
	}

	table.entry[i] = head;
	p = head;
	q = head->next;
	while(q != NULL) {
		if(q->scope == key) {
			p->next = q->next;
			free(q);
			q = p->next;
		}
		else {
			p = p->next;
			q = q->next;
		}
	}
}

//function to delete the symbols of a scope when scope ends
void deleteScopeSyms(int s) {
	printf("Table before deleting scope %d:\n", s);
	printTable();
	printf("Table size = %d\n", table.size);
	for(int i=0;i<TABLE_SIZE;i++) {
		if(table.entry[i] != NULL) {
			deleteNodes(i, s);
			if(table.entry[i] == NULL) {
				table.size--;
			}
		}
	}
	printf("Table after deleting scope %d:\n", s);
	printTable();
	printf("Table size = %d\n", table.size);
}

//function to free memory by deleting entire symbol table
void freeTable() {
	for(int i=0;i<TABLE_SIZE;i++) {
		Symbol *head = table.entry[i];
		Symbol *tmp;
		while(head != NULL) {
			tmp = head;
			head = head->next;
			free(tmp);
		}
	}
}

/* Symbol Table DS definition ends */

/* code to handle Intermediate Code Generation */

//file to store the intermediate code generated
FILE *out_file;

//variables to keep track of labels for intermediate code
int interm_label = 0, temp_label = 0, backpatch_label = 0;

//variable to help create new unique temporary variables
int new_tmp_index = 1;

int temp = 0;

//stores intermediate code corresponding to a label
char *interm_table[100];

//expr_var keeps track of last assigned var in expressions/assignment
//temp_var used in backpatching
char expr_var[20], tmp_var[20];

//function to return name of new temporary variable
char *new_temp_var() {
	static char t[5];
	sprintf(t, "t%d", new_tmp_index);
	return t;
}

//function to write quadruple to output array
void generate(int label, char *str) {
	interm_table[label] = (char *)malloc((strlen(str) + 1) * sizeof(char));
	strcpy(interm_table[label], str); 
}

//function to print intermediate code to output file
void write_to_file() {
	for(int i=0;i<100;i++) {
		if(interm_table[i] != NULL) {
			fprintf(out_file, "%d: %s", i, interm_table[i]);
			free(interm_table[i]);
			interm_table[i] = NULL;
		}
	}
}

/* Intermediate Code Generation functions end */

/* Code to handle conversion of intermediate code to assembly language */

FILE *assemblyFile;

// struct to store register information
typedef struct Reg
{
    int isOccupied;
    // list of identifiers whose value is in that register
    char name[5][5];
} RegInfo;

// Registor Descriptor table (considering 4 registers: B, C, D, E)
RegInfo regDesc[4];

// counter to keep track of count of labels
int label_no = 0;

// function to return a new label name
char* getNewLabel ( )
{
    static char label[5];
    sprintf(label, "L%d", label_no);
    label_no++;
    return label;
}

//function to check if a variable is in register descriptor table
int inRegDesc ( char* var )
{
    int found = 0;
    int reg_no = -1;
    for (int i = 0; i < 4; i++)
    {
        if (found)
            break;

        if (regDesc[i].isOccupied)
        {
            for (int j = 0; j < 5; j++)
            {
                if (strlen(regDesc[i].name[j]) == 0)
                    break;

                if (strcmp(regDesc[i].name[j], var) == 0)
                {
                    found = 1;
                    reg_no = i;
                    break;
                }
            }
        }
    }
    return reg_no;
}

//function to generate the assembly language code from intermediate code
void convert () {
    const int BUFFER_SIZE = 50;
    char line_read[BUFFER_SIZE];
    size_t len = 0;
    srand(time(0));

    // Error in reading the file
    if (out_file == NULL) {
        printf("Error in opening file");
        exit(1);
    }

    // initializing the register descriptor table
    for (int i = 0; i < 4; i++)
    {
        regDesc[i].isOccupied = 0;
        for (int j = 0; j < 5; j++)
            memset(regDesc[i].name[j], 0, 5);
    }

    // initializing variable to store the tokens of a read line
    char *tokens[6];
    for (int i = 0; i < 6; i++) {
        tokens[i] = NULL;
    }

    //reading the intermediate code file
    while (fgets(line_read, BUFFER_SIZE, out_file)){
        // removing newline from the end
        line_read[strlen(line_read)-1] = '\0';

        //printf("starting read\n");
        //printf("%s: line read now\n", line_read);
        // tokenizing the string based on ' '
        char *token = strtok(line_read," ");
        int i = 0;
        while (token != NULL){
            //printf("token = %s\n", token);
            tokens[i] = (char*) malloc( 5 * sizeof(char));
            strcpy(tokens[i], token);
            
            //printf("token written = %s\n", token);
            token = strtok(NULL," ");
            i++;
        }

        //printf("i = %d\n", i);
        //skipping labels for functions or end statements or return statements
        if(tokens[1][strlen(tokens[1])-1] == ':' || strcmp(tokens[1], "end") == 0 || strcmp(tokens[1], "return") == 0) {
            continue;
        }

        /* for(int j=0;j<i;j++) {
            printf("tokens[%d] = %s\n", j, tokens[j]);
        }*/ 
        // action associated with an assignment expression
        if (strcmp(tokens[2], "=") == 0){
            //printf("= found\n");
            // handling "not"
            if (strcmp(tokens[3], "not") == 0){
                char *l1 = getNewLabel();
                char *l2 = getNewLabel();
                fprintf(assemblyFile, "LHLD %s\n", tokens[4]);
                fprintf(assemblyFile, "MOV A,M\n");
                fprintf(assemblyFile, "ADI 0\n");
                fprintf(assemblyFile, "JZ %s\n", l1);
                fprintf(assemblyFile, "MVI A,0\n");
                fprintf(assemblyFile, "JMP %s\n", l2);
                fprintf(assemblyFile, "%s: MVI A,1\n", l1);
                fprintf(assemblyFile, "%s: NOP\n", l2);

                int done = 0;
                int reg_no = 0;
                for (int i = 0; i < 4; i++){
                    if (!regDesc[i].isOccupied){
                        reg_no = i;
                        done = 1;
                        break;
                    }
                }
                if (!done)
                    reg_no = rand() % 4;

                regDesc[reg_no].isOccupied = 1;
                strcpy(regDesc[reg_no].name[0], tokens[1]);

                fprintf(assemblyFile, "MOV R%d,A\n", reg_no);
            }

            // simple assignment
            else if (tokens[4]==NULL) {
                fprintf (assemblyFile, "LHLD %s\n", tokens[3]);

                int reg_no = inRegDesc(tokens[3]);
                if (reg_no != -1)
                {
                    for(int j = 0; j < 5; j++)
                        if (strlen(regDesc[reg_no].name[j]) == 0)
                            strcpy(regDesc[reg_no].name[j], tokens[1]);
                }

                else
                {
                    int done = 0;
                    int reg_no1 = 0;
                    for (int i = 0; i < 4; i++)
                    {
                        if (!regDesc[i].isOccupied)
                        {
                            reg_no1 = i;
                            done = 1;
                            break;
                        }
                    }
                    if (!done)
                        reg_no1 = rand() % 4;

                    regDesc[reg_no1].isOccupied = 1;
                    strcpy(regDesc[reg_no1].name[0], tokens[1]);

                    fprintf(assemblyFile, "MOV R%d,M\n", reg_no1);
                }
            }

            // handling statements of type (number+something) or (number-something)
            else if (tokens[3][0]>='0' && tokens[3][0]<='9') {
                // type (number+number) or (number-number)
                if (tokens[5][0]>='0' && tokens[5][0]<='9') {
                    fprintf(assemblyFile, "MVI A,%s\n", tokens[3]);
                    if (strcmp(tokens[4], "+") == 0)
                        fprintf(assemblyFile, "ADI %s\n", tokens[5]);
                    else
                        fprintf(assemblyFile, "SUI %s\n", tokens[5]);

                    int done = 0;
                    int reg_no = 0;
                    for (int i = 0; i < 4; i++)
                    {
                        if (!regDesc[i].isOccupied)
                        {
                            reg_no = i;
                            done = 1;
                            break;
                        }
                    }
                    if (!done)
                        reg_no = rand() % 4;

                    regDesc[reg_no].isOccupied = 1;
                    strcpy(regDesc[reg_no].name[0], tokens[1]);

                    fprintf(assemblyFile, "MOV R%d,A\n", reg_no);
                }

                // type (number+id) or (number-id)
                else {
                    int reg_no = inRegDesc(tokens[5]);
                    if (reg_no == -1) {
                        fprintf(assemblyFile, "LHLD %s\n", tokens[5]);
                        fprintf(assemblyFile, "MOV A,M\n");
                    }
                    else
                        fprintf(assemblyFile, "MOV A,R%d\n", reg_no);

                    if (strcmp(tokens[4], "+") == 0)
                        fprintf(assemblyFile, "ADI %s\n", tokens[3]);
                    else
                        fprintf(assemblyFile, "SUI %s\n", tokens[3]);

                    int done = 0;
                    reg_no = 0;
                    for (int i = 0; i < 4; i++) {
                        if (!regDesc[i].isOccupied) {
                            reg_no = i;
                            done = 1;
                            break;
                        }
                    }
                    if (!done)
                        reg_no = rand() % 4;

                    regDesc[reg_no].isOccupied = 1;
                    strcpy(regDesc[reg_no].name[0], tokens[1]);

                    fprintf(assemblyFile, "MOV R%d,A\n", reg_no);
                }
            }

            // type (id+number) or (id-number)
            else if (tokens[5][0]>='0' && tokens[5][0]<='9') {
                int reg_no = inRegDesc(tokens[3]);
                if (reg_no == -1) {
                    fprintf(assemblyFile, "LHLD %s\n", tokens[3]);
                    fprintf(assemblyFile, "MOV A,M\n");
                }
                else
                    fprintf(assemblyFile, "MOV A,R%d\n", reg_no);

                if (strcmp(tokens[4], "+")==0)
                    fprintf(assemblyFile, "ADI %s\n", tokens[5]);
                else
                    fprintf(assemblyFile, "SUI %s\n", tokens[5]);


                int done = 0;
                reg_no = 0;
                for (int i = 0; i < 4; i++)
                {
                    if (!regDesc[i].isOccupied)
                    {
                        reg_no = i;
                        done = 1;
                        break;
                    }
                }
                if (!done)
                    reg_no = rand() % 4;

                regDesc[reg_no].isOccupied = 1;
                strcpy(regDesc[reg_no].name[0], tokens[1]);

                fprintf(assemblyFile, "MOV R%d,A\n", reg_no);
            }

            // type (id+id) or (id-id)
            else {
                int reg_no = inRegDesc(tokens[3]);
                if (reg_no == -1) {
                    fprintf(assemblyFile, "LHLD %s\n", tokens[3]);
                    fprintf(assemblyFile, "MOV A,M\n");
                }
                else
                    fprintf(assemblyFile, "MOV A,R%d\n", reg_no);

                reg_no = inRegDesc(tokens[5]);
                if (reg_no == -1)
                {
                    fprintf(assemblyFile, "LHLD %s\n", tokens[5]);
                    if (strcmp(tokens[4], "+") == 0)
                        fprintf(assemblyFile,"ADD M\n");
                    else
                        fprintf(assemblyFile,"SUB M\n");
                }
                else
                {
                    if (strcmp(tokens[4], "+") == 0)
                        fprintf(assemblyFile, "ADD R%d\n", reg_no);
                    else
                        fprintf(assemblyFile, "SUB R%d\n", reg_no);

                }

                int done = 0;
                reg_no = 0;
                for (int i = 0; i < 4; i++)
                {
                    if (!regDesc[i].isOccupied)
                    {
                        reg_no = i;
                        done = 1;
                        break;
                    }
                }
                if (!done)
                    reg_no = rand() % 4;

                regDesc[reg_no].isOccupied = 1;
                strcpy(regDesc[reg_no].name[0], tokens[1]);

                fprintf(assemblyFile,"MOV R%d,A\n",reg_no);
            }
        }

        // handling jump statements
        else {
            // unconditional jump
            if (strcmp(tokens[1], "goto") == 0)
                fprintf(assemblyFile, "JMP %s\n", tokens[2]);

            // conditional jump
            else {
                fprintf(assemblyFile, "LHLD %s\n", tokens[2]);
                fprintf(assemblyFile, "MOV A,M\n");
                fprintf(assemblyFile, "ADI 0\n");
                fprintf(assemblyFile, "JNZ %s\n", tokens[4]);
            }
        }

        // Free allocated space
        for (int i = 0; i < 6; i++)
        {
            free(tokens[i]);
            tokens[i] = NULL;
        }
    }
}

/* code to handle conversion ends */

%}

//defining the yyval union
%union {
	int number;		//for integer constants
	float decimal;	//for real constants
	char *string;	//for identifier names
	struct Dtype {	//for datatype of expression
		int dtype;
		char *place;	//for place value of expression
	} Dtype;
}

// Single caharacter lexemes
%token LPAREN_TOK
%token GT_TOK
%token LT_TOK
%token RPAREN_TOK
%token ASSIGN_TOK
%token MINUS_TOK
%token PLUS_TOK
%token MULT_TOK
%token DIV_TOK
%token MOD_TOK
%token NOT_TOK
%token SEMICOLON_TOK
%token HASH_TOK
%token DOT_TOK
%token COMMA_TOK
%token LCURL_TOK
%token RCURL_TOK
%token LSQUARE_TOK
%token RSQUARE_TOK
%token BIT_AND_TOK
%token BIT_OR_TOK
%token BACKSLASH_TOK
%token SPEECH_TOK
%token INVCOMMA_TOK
%token XOR_TOK
%token NEG_TOK

%left PLUS_TOK MINUS_TOK
%left MULT_TOK DIV_TOK MOD_TOK

//Double character lexemes
%token EQ_TOK
%token GTE_TOK
%token LTE_TOK
%token LSHIFT_TOK
%token RSHIFT_TOK
%token AND_TOK
%token OR_TOK
%token NEQ_TOK
%token INC_TOK
%token DEC_TOK

//Arithmetic assignment operators
%token PLUS_ASSIGN_TOK
%token MINUS_ASSIGN_TOK
%token MULT_ASSIGN_TOK
%token DIV_ASSIGN_TOK
%token MOD_ASSIGN_TOK

// Reserved words
%token DO_TOK
%token WHILE_TOK
%token FOR_TOK
%token IF_TOK
%token ELSE_TOK
%token RET_TOK
%token PRINT_TOK
%token SCAN_TOK
%token DEF_TOK
%token TYPEDEF_TOK
%token BREAK_TOK
%token CONTINUE_TOK
%token SIZEOF_TOK
%token CASE_TOK
%token SWITCH_TOK
%token MAIN_TOK
%token INCLUDE_TOK
%token PRINTF_TOK
%token SCANF_TOK

// Identifiers, constants
%token ID_TOK
%token INT_CONST_TOK
%token CHAR_CONST_TOK
%token REAL_CONST_TOK
%token STRING_CONST_TOK

// Type specifiers
%token INT_TOK
%token CHAR_TOK
%token FLOAT_TOK
%token DOUBLE_TOK
%token LONG_TOK
%token SHORT_TOK
%token VOID_TOK

//%type tells bison which member of the yyval union is used by which expression
%type<number> INT_CONST_TOK
%type<string> ID_TOK
%type<string> comparison
%type<string> arith_op
%type<decimal> REAL_CONST_TOK
%type<string> CHAR_CONST_TOK
%type<string> STRING_CONST_TOK
%type<Dtype> expression
%type<Dtype> FUNCTION_CALL
%type<Dtype> cond_exp
%type<string> PLUS_TOK
%type<string> MINUS_TOK
%type<string> MULT_TOK
%type<string> DIV_TOK
%type<string> MOD_TOK
%type<string> GT_TOK
%type<string> LT_TOK
%type<string> GTE_TOK
%type<string> LTE_TOK
%type<string> EQ_TOK
%type<string> NEQ_TOK
%type<string> AND_TOK
%type<string> OR_TOK

%start S

%%

S: 				header S
  				| header
				| MAIN_FN
				| USER_FN S1
				| DECLARE_ASSIGN SEMICOLON_TOK S1
				;

S1: 			USER_FN S1
				| DECLARE_ASSIGN SEMICOLON_TOK S1
				| header
				| USER_FN
				| MAIN_FN
				| DECLARE_ASSIGN SEMICOLON_TOK
				;

open_paren:		LPAREN_TOK											{scope++;}
				;

close_paren:	RPAREN_TOK											{scope--;}
				;

header:			HASH_TOK INCLUDE_TOK LT_TOK ID_TOK DOT_TOK ID_TOK GT_TOK 		{printf("Header syntax correct;\tline no:\t%d\n", yylineno);}
    			| HASH_TOK INCLUDE_TOK STRING_CONST_TOK 						{printf("Header syntax correct;\tline no:\t%d\n", yylineno);}
				;

MAIN_FN:		INT_TOK MAIN_TOK 					{	char msg[50];
														sprintf(msg, "main:\n");
														generate(interm_label, msg);
														interm_label++;
													}
				param block  						{	char msg[50];
														sprintf(msg, "end main\n");
														generate(interm_label, msg);
														interm_label++;
														printf("Main function syntax OK;\tline no:\t%d\n", yylineno);
													}
				;

USER_FN:		datatype ID_TOK 					{	int c = addFunction($2); 
														if(c == -1) { 
															char msg[100]; 
															sprintf(msg, ": Symbol table full"); 
															yyerror(msg);
														}
														char msg[50];
														sprintf(msg, "%s:\n", $2);
														generate(interm_label, msg);
														interm_label++;
													}
				param block 						{	char msg[50];
														sprintf(msg, "end %s\n", $2);
														generate(interm_label, msg);
														interm_label++;
														printf("User defined function OK;\tline no:\t%d\n", yylineno);
													}
				;

param:			open_paren params close_paren						
    			| LPAREN_TOK RPAREN_TOK
				;

params: 		datatype ID_TOK COMMA_TOK params					{	int c = alreadyDeclared($2);
																		char msg[100];
																		if(c == 1) {
																			sprintf(msg, ": Multiple declarations of the identifier in same scope");
																			yyerror(msg);
																		}
																		else if(c == 2) {
																			sprintf(msg, ": Conflicting types for identifier");
																			yyerror(msg);
																		}
																		else {
																			int x = addSymbol($2);
																			if(x == -1) {
																				sprintf(msg, ": Symbol table full");
																				yyerror(msg);
																			}
																		}
																	}
				| datatype ID_TOK									{	int c = alreadyDeclared($2);
																		char msg[100];
																		if(c == 1) {
																			sprintf(msg, ": Multiple declarations of the identifier in same scope");
																			yyerror(msg);
																		}
																		else if(c == 2) {
																			sprintf(msg, ": Conflicting types for identifier");
																			yyerror(msg);
																		}
																		else {
																			int x = addSymbol($2);
																			if(x == -1) {
																				sprintf(msg, ": Symbol table full");
																				yyerror(msg);
																			}
																		}
																	}
				;

datatype:		INT_TOK												{dtype = 1;}
	 			| FLOAT_TOK											{dtype = 2;}
				| DOUBLE_TOK										{dtype = 2;}
				| CHAR_TOK											{dtype = 4;}
				| VOID_TOK											{dtype = 5;}
				;

start_block:	LCURL_TOK											{scope++;}
				;

end_block:		RCURL_TOK											{deleteScopeSyms(scope); scope--;}
				;

block:			start_block blocks end_block
      			| start_block end_block
      			;

blocks: 		block STATEMENTS blocks
       			| STATEMENTS blocks
				| STATEMENTS
				;

STATEMENTS:		stmt STATEMENTS
	   			| stmt
				;

stmt:			DECLARE_ASSIGN SEMICOLON_TOK						{printf("Declaration over;\tline no:\t%d\n", yylineno);}
				| EXP_ASSIGN SEMICOLON_TOK							{printf("Assignment over;\tline no:\t%d\n", yylineno);}
				| CONDITIONAL										{printf("Conditional block ends;\tline no:\t%d\n", yylineno);}
				| ITERATIVE											{printf("Iterative block ends;\tline no:\t%d\n", yylineno);}
				| FUNCTION_CALL SEMICOLON_TOK									
				| RET_TOK expression SEMICOLON_TOK					{	char msg[50];
																		sprintf(msg, "return %s\n", $2.place);
																		generate(interm_label, msg);
																		interm_label++;
																		printf("Return statement found;\tline no:\t%d\n", yylineno);
																	}
				| PRINTF_ST
    			;

PRINTF_ST:		PRINTF_TOK args SEMICOLON_TOK						{printf("printf statement found;\tline no:\t%d\n", yylineno);}
	  			;

expression:		ID_TOK												{	if(!isPresent($1)) {
																			char msg[100];
																			sprintf(msg, ": Undefined identifier found");
																			yyerror(msg);
																		}
																		else {
																			$$.dtype = getDatatype($1);
																			$$.place = strdup($1);
																		}
																	}
				| ID_TOK array_ele									{	if(!isPresent($1)) {
																			char msg[100];
																			sprintf(msg, ": Undefined identifier found");
																			yyerror(msg);
																		}
																		else {
																			$$.dtype = getDatatype($1);
																			$$.place = strdup($1);
																		}
																	}
	   			| INT_CONST_TOK										{	$$.dtype = 1;
				   														char tmp[20];
																		sprintf(tmp, "%d", $1);
																		$$.place = strdup(tmp);
																	}
				| REAL_CONST_TOK									{	$$.dtype = 2;
																		char tmp[20];
																		sprintf(tmp, "%.2f", $1);
																		$$.place = strdup(tmp);
																	}
				| CHAR_CONST_TOK									{	$$.dtype = 4;
																		char tmp[5];
																		sprintf(tmp, "%s", $1);
																		$$.place = strdup(tmp);
																	}
				| STRING_CONST_TOK									{	$$.dtype = 5;
																		char tmp[100];
																		sprintf(tmp, "%s", $1);
																		$$.place = strdup(tmp);
																	}
				| FUNCTION_CALL										{	$$.dtype = $1.dtype;
																		$$.place = strdup($1.place);
																	}
				| LPAREN_TOK expression RPAREN_TOK					{	$$.dtype = $2.dtype;
																		$$.place = strdup($2.place);
																	}
				| expression arith_op expression					{	if($1.dtype != $3.dtype) {
																			char msg[100];
																			sprintf(msg, ": Type matching error in expression");
																			yyerror(msg);
																		}
																		else {
																			char *tmp = new_temp_var();
																			new_tmp_index++;
																			$$.place = strdup(tmp);

																			char msg[50];
																			sprintf(msg, "%s = %s %s %s\n", $$.place, $1.place, $2, $3.place);
																			generate(interm_label, msg);
																			strcpy(expr_var, $$.place);
																			interm_label++;
																		}
																		$$.dtype = $1.dtype;
																	}
				;

arith_op:		PLUS_TOK	{$$ = strdup($1);}										
	 			| MINUS_TOK	{$$ = strdup($1);}
				| MULT_TOK	{$$ = strdup($1);}
				| DIV_TOK	{$$ = strdup($1);}
				| MOD_TOK	{$$ = strdup($1);}
				;

DECLARE_ASSIGN:	datatype varlist
				;

array_ele:		LSQUARE_TOK ID_TOK RSQUARE_TOK						{	if(!isPresent($2)) {
																			char msg[100];
																			sprintf(msg, ": Undeclared identifier found");
																			yyerror(msg);
																		}
																	}
				| LSQUARE_TOK INT_CONST_TOK RSQUARE_TOK
				| LSQUARE_TOK RSQUARE_TOK							{	char msg[100];
																		sprintf(msg, ": Unspecified array element access");
																		yyerror(msg);
																	}
				;

array_size:		LSQUARE_TOK INT_CONST_TOK RSQUARE_TOK
				| LSQUARE_TOK REAL_CONST_TOK RSQUARE_TOK			{	char msg[100];
																		sprintf(msg, ": Incorrect type for array size");
																		yyerror(msg);
																	}
				;

varlist:		ID_TOK												{	int c = alreadyDeclared($1);
																		char msg[100];
																		if(c == 1) {
																			sprintf(msg, ": Multiple declarations of the identifier in same scope");
																			yyerror(msg);
																		}
																		else if(c == 2) {
																			sprintf(msg, ": Conflicting types for identifier");
																			yyerror(msg);
																		}
																		else {
																			int x = addSymbol($1);
																			if(x == -1) {
																				sprintf(msg, ": Symbol table full");
																				yyerror(msg);
																			}
																		}
																	}
	    		| ID_TOK COMMA_TOK varlist							{	int c = alreadyDeclared($1);
																		char msg[100];
																		if(c == 1) {
																			sprintf(msg, ": Multiple declarations of the identifier in same scope");
																			yyerror(msg);
																		}
																		else if(c == 2) {
																			sprintf(msg, ": Conflicting types for identifier");
																			yyerror(msg);
																		}
																		else {
																			int x = addSymbol($1);
																			if(x == -1) {
																				sprintf(msg, ": Symbol table full");
																				yyerror(msg);
																			}
																		}
																	}
				| ID_TOK ASSIGN_TOK expression COMMA_TOK varlist	{	int c = alreadyDeclared($1);
																		char msg[100];
																		if(c == 1) {
																			sprintf(msg, ": Multiple declarations of identifier in same scope");
																			yyerror(msg);
																		}
																		else if(c == 2) {
																			sprintf(msg, ": Conflicting types for identifier");
																			yyerror(msg);
																		}
																		else {
																			int x = addSymbol($1);
																			if(x == -1) {
																				sprintf(msg, ": Symbol table full");
																				yyerror(msg);
																			}
																		}
																		if(dtype != $3.dtype) {
																			sprintf(msg, ": Type mismatch between identifier and expression");
																			yyerror(msg);
																		}
																		else {
																			char msg[100];
																			sprintf(msg, "%s = %s\n", $1, $3.place);
																			generate(interm_label, msg);
																			strcpy(expr_var, $1);
																			interm_label++;
																		}
																	}
				| ID_TOK ASSIGN_TOK expression						{	int c = alreadyDeclared($1);
																		char msg[100];
																		if(c == 1) {
																			sprintf(msg, ": Multiple declarations of identifier in same scope");
																			yyerror(msg);
																		}
																		else if(c == 2) {
																			sprintf(msg, ": Conflicting types for identifier");
																			yyerror(msg);
																		}
																		else {
																			int x = addSymbol($1);
																			if(x == -1) {
																				sprintf(msg, ": Symbol table full");
																				yyerror(msg);
																			}
																		}
																		if(getDatatype($1) != $3.dtype) {
																			sprintf(msg, ": Type mismatch between identifier and expression");
																			yyerror(msg);
																		}
																		else {
																			char msg[100];
																			sprintf(msg, "%s = %s\n", $1, $3.place);
																			generate(interm_label, msg);
																			strcpy(expr_var, $1);
																			interm_label++;
																		}
																	}
				| ID_TOK array_size COMMA_TOK varlist				{	int c = alreadyDeclared($1);
																		char msg[100];
																		if(c == 1) {
																			sprintf(msg, ": Multiple declarations of identifier in same scope");
																			yyerror(msg);
																		}
																		else if(c == 2) {
																			sprintf(msg, ": Conflicting types for identifier");
																			yyerror(msg);
																		}
																		else {
																			int x = addSymbol($1);
																			if(x == -1) {
																				sprintf(msg, ": Symbol table full");
																				yyerror(msg);
																			}
																		}
																	}
				| ID_TOK array_size									{	int c = alreadyDeclared($1);
																		char msg[100];
																		if(c == 1) {
																			sprintf(msg, ": Multiple declarations of identifier in same scope");
																			yyerror(msg);
																		}
																		else if(c == 2) {
																			sprintf(msg, ": Conflicting types for identifier");
																			yyerror(msg);
																		}
																		else {
																			int x = addSymbol($1);
																			if(x == -1) {
																				sprintf(msg, ": Symbol table full");
																				yyerror(msg);
																			}
																		}
																	}
				;

EXP_ASSIGN:		ID_TOK ASSIGN_TOK expression						{	if(!isPresent($1)) {
																			char msg[100];
																			sprintf(msg, ": Undefined identifier found");
																			yyerror(msg);
																		}
																		else {
																			if(getDatatype($1) != $3.dtype) {
																				char msg[100];
																				sprintf(msg, ": Type mismatch between identifier and expression");
																				yyerror(msg);
																			}
																			else {
																				char msg[100];
																				sprintf(msg, "%s = %s\n", $1, $3.place);
																				generate(interm_label, msg);
																				strcpy(expr_var, $1);
																				interm_label++;
																			}
																		}
																	}
				;

IF_ST:			IF_TOK {temp_label = interm_label;}
				open_paren cond_exp close_paren						{	char *tmp = new_temp_var();
																		new_tmp_index++;
																		char msg[50];
																		sprintf(msg, "%s = not %s\n", tmp, expr_var);
																		generate(interm_label, msg);
																		interm_label++;
																		backpatch_label = interm_label;
																		strcpy(tmp_var, tmp);
																		interm_label++;
																	}
    			;

ELSE_PART:		ELSE_TOK 	{	//backpatching
								char msg[50];
								sprintf(msg, "if %s goto %d\n", tmp_var, interm_label+1);
								generate(backpatch_label, msg);
								backpatch_label = interm_label;
								interm_label++;
							}
				block		{	//backpatching
								char msg[50];
								sprintf(msg, "goto %d\n", interm_label);
								generate(backpatch_label, msg);
							}
				;

IF_PART:		IF_ST block
				;

CONDITIONAL:	IF_PART ELSE_PART
	    		| IF_PART	{	//backpatching
								char msg[50];
								sprintf(msg, "if %s goto %d\n", tmp_var, interm_label);
								generate(backpatch_label, msg);
							}
				;

cond_exp:		expression											{	$$.dtype = $1.dtype;
																		$$.place = strdup($1.place);
																	}
				| expression comparison expression					{	if($1.dtype != $3.dtype) {
																			char msg[100];
																			sprintf(msg, ": Type matching error in expression");
																			yyerror(msg);
																		}
																		else {
																			char *tmp = new_temp_var();
																			new_tmp_index++;
																			$$.place = strdup(tmp);

																			char msg[50];
																			sprintf(msg, "%s = %s %s %s\n", $$.place, $1.place, $2, $3.place);
																			generate(interm_label, msg);
																			strcpy(expr_var, $$.place);
																			interm_label++;
																		}
																		$$.dtype = $1.dtype;
																	}
				;

comparison:		GT_TOK		{$$ = strdup($1);}
	   			| LT_TOK	{$$ = strdup($1);}
				| GTE_TOK	{$$ = strdup($1);}
				| LTE_TOK	{$$ = strdup($1);}
				| NEQ_TOK	{$$ = strdup($1);}
				| EQ_TOK	{$$ = strdup($1);}
				| AND_TOK	{$$ = strdup($1);}
	   			| OR_TOK	{$$ = strdup($1);}
				;

WHILE_ST:		WHILE_TOK {temp_label = interm_label;} 
				open_paren cond_exp close_paren			{	
															char *tmp = new_temp_var();
															new_tmp_index++;
															char msg[50];
															sprintf(msg, "%s = not %s\n", tmp, expr_var);
															generate(interm_label, msg);
															interm_label++;
															backpatch_label = interm_label;
															strcpy(tmp_var, tmp);
															interm_label++;
														}
	 			;

ITERATIVE:		WHILE_ST block							{
															char msg[50];
															sprintf(msg, "goto %d\n", temp_label);
															generate(interm_label, msg);
															interm_label++;

															//backpatching
															sprintf(msg, "if %s goto %d\n", tmp_var, interm_label);
															generate(backpatch_label, msg);
														}
				;

FUNCTION_CALL:	ID_TOK args											{	printf("Function call statement found;\tline no:\t%d\n", yylineno);
																		if(!isPresent($1)) {
																			char msg[100];
																			sprintf(msg, ": Undeclared identifier found");
																			yyerror(msg);
																		}
																		else {
																			$$.dtype = getDatatype($1);
																			$$.place = strdup($1);
																		}
																	}
				;

args:			LPAREN_TOK arg RPAREN_TOK
				| LPAREN_TOK RPAREN_TOK
				;

arg:			expression
    			| expression COMMA_TOK arg
				;

%%

void yyerror(char *s) {
	flag = 1;
	printf("\nParsing error at line: %d; Error%s\n\n", yylineno, s);
}

int main() {
	yyin = fopen("test.c", "r");
	out_file = fopen("interm_code.txt", "w");
	initTable();
	if(yyparse() == 0){
		if(flag == 0)
			printf("Parsed Successfully\n");
		else
			printf("Parsing Finished\n");
	}
	else {
		printf("\nSyntax error at line no.: %d\n", yylineno);
		printf("Last read token: %s\n", yytext);
	}
	write_to_file();
	fclose(yyin);
	fclose(out_file);
	out_file = fopen("interm_code.txt", "r");
	assemblyFile = fopen("assembly_code.txt", "w");
	convert();
	fclose(out_file);
	fclose(assemblyFile);
	freeTable();
	printf("All operations completed successfully.\nThe intermediate code can be found in file 'interm_code.txt'.\nThe assembly code can be found in file 'assembly_code.txt'.\n");
	return 0;
}

