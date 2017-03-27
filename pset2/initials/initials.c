#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void initials (char *name);

int main(void)
{
    char *name = malloc (100 * sizeof(char));
    fgets(name, 100, stdin);

    initials(name);
    return 0;
}

void initials (char *name)
{
    for (int i = 0, n = strlen(name); i < n; i++)  // skip first argument (program name)
    {
        if ((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z'))   // if current character is a letter - make it uppercase
        {
            printf("%c", toupper(name[i]));
            
            //  after making single inital - move index to skip current string (go to a space separator)
            do
            {
                i++;
            }
            while ((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z'));
        }
    }
    printf("\n");
}