#include <stdio.h>
#include <stdbool.h>

typedef struct
{
    int n;
    char *elo;
}
str1;

typedef struct node
{
    int liczba;
    struct node *next;
}
node;

// prototyping
bool search(int n, node *list, int *iteration);

int main(void)
{
    str1 test;

    // test struktur
    test.n = 5;
    test.elo = "test";
    printf("n = %d\n", test.n);
    printf("elo = %s\n", test.elo);

    return 0;
}
