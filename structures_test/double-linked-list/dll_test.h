/**
  * Header file containing functions of doubly linked lists
**/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// declaring doubly-linked list structure
typedef struct dll_list
{
    int n;
    struct dll_list *prev;
    struct dll_list *next;
} dll_node;

// global variable for prev_node
dll_node *prev_node = NULL;

/**
*** functions for doubly-linked list functionality
**/

dll_node *create_dll(int value)
{
    dll_node *new_list = (dll_node*) malloc(sizeof(dll_node));
    new_list->n = value;
    new_list->prev = NULL;
    new_list->next = NULL;

    return new_list;
}

dll_node *insert(dll_node *list, int value)
{
    dll_node *new_node = (dll_node*) malloc(sizeof(dll_node));
    new_node->n = value;
    new_node->prev = NULL;
    new_node->next = list;

    // update pointer of previous head
    list->prev = new_node;

    return new_node;
}

bool search(dll_node *list, int value)
{
    dll_node *traversal = list;
    // if current node's n equals value - return true
    if (traversal->n == value)
    {
        printf("%d found!\n", value);
        return true;
    }
    // else keep going to the next node until the last one
    else if (traversal->next != NULL)
        search(traversal->next, value);
    // else value not in list
    return false;
}

// remove single node with given value
void remove_node(dll_node **list, int value)
{
    dll_node *traversal = *list;

    // go to next node until value is found
    while (traversal->n != value && traversal->next != NULL)
    {
        prev_node = traversal;
        traversal = traversal->next;
    }

    // if value is in head node
    if (traversal->n == value && traversal->prev == NULL)
    {
        *list = (*list)->next;
        (*list)->prev = NULL;
        free(traversal);
    }
    // if value is somewhere between head and last node
    else if (traversal->n == value && traversal->next != NULL)
    {
        prev_node->next = traversal->next;
        (traversal->next)->prev = prev_node;
        free(traversal);
    }
    // if value is in the last node
    else if (traversal->n == value && traversal->next == NULL)
    {
        prev_node->next = NULL;
        free(traversal);
    }
    else
        fprintf(stderr, "value not found in list\n");
}

void destroy(dll_node *list)
{
    dll_node *traversal = list;

    if(traversal != NULL)
        destroy(traversal->next);

    free(traversal);
}
