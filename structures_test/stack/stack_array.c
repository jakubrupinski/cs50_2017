#include <stdio.h>
#include <stdlib.h>

// define array stack
typedef struct _stack
{
    int array[99];
    int top;
} stack;

// prototyping
void push(stack *s, int n);
int pop(stack *s);


int main(void)
{
    stack s;
    s.top = 0;

    for(int i = 0; i < 200; i++)
    {
        push(&s, i);
        if (i % 2 == 0)
            pop(&s);
    }
    push(&s, 500);
    push(&s, 666);
    printf("stack, n1 = %d, n99 = %d\n", s.array[0], pop(&s));
    return 0;
}

void push(stack *s, int n)
{
    if (s->top < 99)
    {
        s->array[s->top] = n;
        (s->top)++;
    }
    else
        fprintf(stderr, "array is full!\n");
}

int pop(stack *s)
{
    if (s->top >= 0)
    {
        int placeholder = s->array[s->top];
        (s->top)--;
        return placeholder;
    }
    else
        return fprintf(stderr, "No more values to pop!\n");
}
