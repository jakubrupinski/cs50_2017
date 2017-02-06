#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    string s = GetString();
    
    for (int i = 0, length = strlen(s); i < length; i++)
    {
        if (s[i] >= 'a' && s[i] <= 'z')
        {
            printf("%c", s[i] + ('A' - 'a'));
        }
        else
        {
            printf("%c", s[i]);
        }
    }
    printf("\n");
}