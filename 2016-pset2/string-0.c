#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(int argc, char** argv)
{
    for (int i = 1; i < argc; i++)
    {
        for (int j = 0; j < strlen(argv[i]); j++)
        {
            printf("%c\n", argv[i][j]);
        }
    }
}