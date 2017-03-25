#include <stdio.h>
#include <stdlib.h>

typedef struct _stack
{
    int val;
    struct _stack *next;
} stack;

// prototyping
void push(int n);
int pop();
void destroy();

// global variable to keep head location
stack *head = NULL;

int main(void)
{
    stack *s = malloc(sizeof(stack));
    s->val = 0;
    s->next = NULL;
    head = s;

    push(10);
    push(20);
    push(30);

    printf("head: %d\n", head->val);
    printf("pop: %d\n", pop());
    printf("head: %d\n", head->val);
    printf("siemanko\n");

    destroy();
    free(s);
    return 0;
}

void push(int n)
{
    stack *new_node = malloc(sizeof(stack));
    new_node->val = n;
    new_node->next = head;
    head = new_node;
}

int pop()
{
    stack *trav = head->next;
    int value = head->val;
    free(head);
    head = trav;
    return value;
}

void destroy()
{
    stack *trav = head;
    if (trav->next!=NULL)
        destroy(trav->next);
    free(trav);
}
