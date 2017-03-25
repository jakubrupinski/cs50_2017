#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 10

// define linkedlist
typedef struct node
{
    char *string;
    struct node *prev;
    struct node *next;
} linkedlist;

// prototyping
linkedlist *create(char *string);
linkedlist *insert(linkedlist *list, char *string);
int hash(char *string);

// global variable with pointer to head of list
struct node *head = NULL;

int main(void)
{
    int *list[HASH_SIZE];

    list[hash("Joey")] = insert(list[hash("Joey")], "Joey");

    printf("string in hash %d = %s\n", hash("Joey"), list[hash("Joey")]->string);
    return 0;
}

int hash(char *string)
{
    int sum = 0;

    for(int i = 0; string[i] != '\0'; i++)
    {
        sum += string[i];
    }

    return sum % HASH_SIZE;
}

linkedlist *create(char *string)
{
    linkedlist *new_list = malloc (sizeof(linkedlist));
    new_list->string = string;
    new_list->prev = NULL;
    new_list->next = NULL;

    if (head == NULL)
        head = new_list;
    return new_list;
}

linkedlist *insert(linkedlist *list, char *string)
{
    linkedlist *new_node = create(string);

    new_node->next = list;
    list->prev = new_node;

    head = new_node;
    return new_node;
}
