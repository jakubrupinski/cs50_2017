#include <stdio.h>
#include <cs50.h>

void pyramid(int n);
int user_input(void);

int main(void)
{
    int height = user_input();
    pyramid(height);
}

// get user input
int user_input(void)
{
    int height;
    do
    {
        printf("Height(positive integer less than 24): ");
        height = get_int();
    }
    while(height < 0 || height >= 24);
    
    return height;
}

/*
* start from top, i decreases 1 level vertically, j draws blocks
* horizontally - top has 1 block for each side,
* increment number of blocks on each side with every step down
*/
void pyramid(int n)
{
    for(int i = n; i > 0; i--)
    {
        for(int j = i-1; j > 0; j--)
        {
            printf(" ");
        }
        
        for(int j = i; j <= n; j++)
        {
            printf("#");
        }
        
        printf("  ");
        
        for(int j = i; j <= n; j++)
        {
            printf("#");
        }
        
        printf("\n");
    }
}