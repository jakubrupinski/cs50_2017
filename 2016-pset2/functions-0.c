#include <stdio.h>
#include <cs50.h>

void Print_Name(char* name);

int main(int argc, char** argv)
{
    Print_Name("Rupcio");
    Print_Name(argv[1]);
    return 0;
}

void Print_Name(char* name)
{
    printf("Hello, %s!\n", name);
}