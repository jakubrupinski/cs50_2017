#include <stdio.h>
#include <stdlib.h>

#define HASH_MAX 10

// prototyping
unsigned int hash(char *str);

// global array
char *hash_array[HASH_MAX];

int main(void)
{
    hash_array[hash("John")] = "John";
    hash_array[hash("Paul")] = "Paul";
    hash_array[hash("Ringo")] = "Ringo";
    hash_array[hash("John")] = "John";


    for (int i = 0; i < HASH_MAX; i++)
        printf("%s\n", hash_array[i]);

    return 0;
}

unsigned int hash(char *str)
{
    int sum = 0;
    for (int j = 0; str[j] != '\0'; j++)
    {
        sum += str[j];
    }
    return sum % HASH_MAX;
}
