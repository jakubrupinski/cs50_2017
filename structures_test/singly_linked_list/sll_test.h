/**
  * Header file for singly-linked list test containing functions of it
**/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// initialize list struct
typedef struct sllist
{
    int n;
    struct sllist *next;
}
sllnode;

/*
 * define global variables for head node and prev_node
**/
sllnode *head_node = NULL;
sllnode *prev_node = NULL;

/*
 * functions for operations on list
 */

// create new list
sllnode *create(int value)
{
    sllnode *node = (sllnode*) malloc(sizeof(sllnode));

    // if not enough memory - return error
    if (node == NULL)
    {
        free(node);
        fprintf(stderr, "could not allocate memory for value\n");
    }

    node->n = value;
    node->next = NULL;
    // update head to point to new list node
    head_node = node;

    return node;
}

// insert new node in front
sllnode *insert (sllnode *list, int value)
{
    sllnode *new_node = (sllnode*) malloc(sizeof(sllnode));

    if (new_node == NULL)
    {
        free(new_node);
        fprintf(stderr, "could not allocate memory\n");
    }

    new_node->n = value;
    new_node->next = list;
    // make new_node head of list
    head_node = new_node;

    return new_node;
}

bool find(sllnode *head, int value)
{
    sllnode *traversal = head;
    // if found - return true
    if (traversal->n == value)
    {
        printf("%d found!\n", value);
        return true;
    }
    // if not found - go to next element if present
    else if (traversal->next != NULL)
        find(traversal->next, value);

    // if not found and/or end of list - return false
    return false;
}

// destroy whole list
void destroy(sllnode *head)
{
    sllnode *traversal = head;

    if(traversal->next != NULL)
        destroy(traversal->next);

    free(traversal);
    head_node = NULL;
}
