#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    printf("Enter a string: ");
    string s = GetString();
    
    if (s != NULL)
    {
        for (int i = 0, len = strlen(s); i < len; i++)
        {
            printf("%c = %d\n", s[i], (int) s[i]);
        }
    }
}