#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct t_symbol {
    char name[20];
    int dtype;
    int scope;
    int line_number;
} symbol;

symbol *create_symbol(char *name, int dtype, int scope, int line_number) {
    symbol *s = (symbol *)malloc(sizeof(symbol));
    strcpy(s->name, name);
    s->dtype = dtype;
    s->scope = scope;
    s->line_number = line_number;
    return s;
}

void display_symbol(symbol *s) {
    if (s == NULL) {
        printf("Cannot display NULL symbol\n");
        return;
    }

    printf("%-10s %-10d %-10d %-10d\n", s->name, s->dtype, s->scope, s->line_number);
}

typedef struct t_node {
    symbol *data;
    struct t_node *next;
} node;

typedef struct t_symbol_table {
    node *head;
    int size;
} symbol_table;

symbol_table *create_table() {
    symbol_table *table = (symbol_table *)malloc(sizeof(symbol_table));
    table->head = NULL;
    table->size = 0;
    return table;
}

void insert_table(symbol_table *table, symbol *data) {
    node *new_node = (node *)malloc(sizeof(node));
    new_node->data = data;
    new_node->next = table->head;
    table->head = new_node;
    table->size++;
}

void iterate_table(symbol_table *table) {
    printf("\n[SYMBOL TABLE]\n%-10s %-10s %-10s %-10s\n", "Name", "Data Type", "Scope", "Line Number");
    printf("------------------------------------------------\n");
    node *current = table->head;
    while (current != NULL) {
        display_symbol(current->data);
        current = current->next;
    }
}

symbol *lookup_table(symbol_table *table, char *name, int scope) {
    node *current = table->head;
    while (current != NULL) {
        if ((strcmp(current->data->name, name) == 0) && (current->data->scope <= scope)) {
            return current->data;
        }
        current = current->next;
    }
    printf("Symbol not found\n");
    return NULL;
}

void remove_table(symbol_table *table, int scope) {
    node *current = table->head;
    node *previous = NULL;
    while (current != NULL) {
        if (current->data->scope == scope) {
            if (previous == NULL) {
                table->head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            table->size--;
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("Symbol not found\n");
}