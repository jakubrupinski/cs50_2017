/*
* A not-so-simple (for me at least) program that draws
* a half-pyramid with 2 blocks on top.
* Takes int for input, ranging from 0 to 23.
*/
#include <stdio.h>
#include <cs50.h>

int main (void)
{
    //initializing variables, topmost block width is always 2!
    int height, space_width, block_width = 2;
    string block = "#", space = " ";
    
    // Getting input from user
    do
    {
        printf("Input height (no more than 23)\n");
        height = GetInt();
        
        if (height < 0 || height > 23)
            printf("Invalid input, try again!\n");
    }
    while (height < 0 || height > 23);
    
    
    // loops for displaying the pyramid, takes the height and goes down
    for (int i = height; i > 0; i--)
    {
        // space width is one block less than height
        space_width = i - 1;
        
        // loop for generating spaces
        while (space_width > 0)
        {
            printf("%s", space);
            space_width--;
        }
        
        // loop for generating blocks
        for (int j = block_width; j > 0; j--)
        {
            printf("%s", block);
        }
        
        // adding one more block on each iteration and making a new line
        block_width++;
        printf("\n");
    }
}