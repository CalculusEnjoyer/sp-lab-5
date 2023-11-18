#include "syntax_tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

syntax_node* create_node(const char* name) {
    syntax_node* new_node = malloc(sizeof(syntax_node));
    for(int i = 0; i < NODES_SIZE; i++) {
        new_node->next_elements[i] = NULL;
    }

    new_node->name = name;

    return new_node;
}

syntax_node* create_node_value(const char* name, double value) {
    syntax_node* new_node = create_node(name);
    new_node->value = value;
    return new_node;
}

void add_sub_node(syntax_node* main_node, syntax_node* sub_node)
{
    int i = 0;
    while (main_node->next_elements[i] != NULL)
    {
        i++;
    }

    main_node->next_elements[i] = sub_node;
}

syntax_node* create_node_list_3(const char* name, syntax_node* one, syntax_node* two, syntax_node* three) 
{
    syntax_node* new_node = create_node(name);
    add_sub_node(new_node, one);
    add_sub_node(new_node, two);
    add_sub_node(new_node, three);

    return new_node;
}

syntax_node* create_node_list_2(const char* name, syntax_node* one, syntax_node* two) 
{
    syntax_node* new_node = create_node(name);
    add_sub_node(new_node, one);
    add_sub_node(new_node, two);

    return new_node;
}


void print_tree(syntax_node* node, char* ind, int is_last) 
{
    char *indent = strdup(ind);
    int c = 0;
    printf("\033[0;33m");
    printf("%s", indent);

    if(is_last) {
        printf("└");
        strcat(indent, "   ");
    } else {
        printf("|-");
        strcat(indent, "|  ");
    }

    printf(" %s\n", node->name);

    c = 0;
    while (node->next_elements[c] != NULL)
    {
        print_tree(node->next_elements[c], indent, node->next_elements[c+1] == NULL);
        c++;
    }
}


void print_spaces(int count) {
    for (int i = 0; i < count; ++i) {
        printf("  "); // Adjust the number of spaces for indentation
    }
}


void print_syntax_tree_rec(syntax_node* node, int depth, int isLast) {
    printf("\033[0;36m");
    if (node != NULL) {
        print_spaces(depth - 1);

        if (depth > 0) {
            if (isLast) {
                printf(" \\-> ");
            } else {
                printf(" |-> ");
            }
        }

        printf("%s", node->name);

        if (node->value != 0.0) {
            printf(": %.2f", node->value);
        }

        printf("\n");

        for (int i = 0; i < NODES_SIZE; ++i) {
            int newDepth = depth + 1;
            int newIsLast = (node->next_elements[i] == NULL);

            print_syntax_tree_rec(node->next_elements[i], newDepth, newIsLast);
        }
    }
}

void print_syntax_tree(syntax_node* node) {
    printf("\033[0;33m");
    printf("Syntax Tree:\n");
    print_syntax_tree_rec(node, 0, 1);
}

