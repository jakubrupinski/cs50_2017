#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 100

typedef struct _queue
{
    int array[CAPACITY];
    int front;
    int size;
} queue;

// prototyping
void enqueue(int n);
int dequeue();

// global variable
queue q;


int main(void)
{
    q.front = 0;
    q.size = 0;
    enqueue(10);
    enqueue(20);
    enqueue(30);
    dequeue();
    printf("current first in queue: %d\n",q.array[q.front]);
    return 0;
}

void enqueue(int n)
{
    q.array[(q.size + q.front) % CAPACITY] = n;
    (q.size)++;
}

int dequeue()
{
    int value = q.array[q.front];
    (q.size)--;
    (q.front)++;
    return value;
}
