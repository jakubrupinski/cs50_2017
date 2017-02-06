#include <stdio.h>
#include <cs50.h>

int main(void)
{
    for (char i = 'A'; i <= 'Z'; i++)
        printf("%c is %i\n", i, (int) i);
}