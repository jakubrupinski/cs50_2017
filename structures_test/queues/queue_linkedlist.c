#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int n;
    struct node *prev;
    struct node *next;
} queue;

// global variables
queue *head = NULL;
queue *tail = NULL;

// prototyping
void enqueue(queue *q, int n);
int dequeue(queue *q);

int main(void)
{
    queue *q = malloc(sizeof(queue));
    q->n = 10;
    q->prev = NULL;
    q->next = NULL;
    head = q;
    tail = q;

    enqueue(tail, 20);
    enqueue(tail, 30);
    enqueue(q, 40);
    enqueue(q, 50);

    printf("current first client: %d\n", head->n);
    printf("current last client: %d\n", tail->n);

    dequeue(head);

    printf("current first client: %d\n", head->n);
    printf("current last client: %d\n", tail->n);

    dequeue(head);

    printf("current first client: %d\n", head->n);
    printf("current last client: %d\n", tail->n);



}

void enqueue(queue *q, int value)
{
    queue *new_node = malloc(sizeof(queue));
    new_node->n = value;
    new_node->prev = tail;
    new_node->next = NULL;

    tail->next = new_node;
    tail = new_node;
}

int dequeue(queue *q)
{
    queue *trav = head;
    int n = head->n;
    head = head->next;
    head->prev = NULL;
    free(trav);

    return n;
}
