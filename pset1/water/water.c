#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int minutes, bottles, gallon = 128;
    double water_spent;
    
    do
    {
        printf("How many minutes did you shower: ");
        minutes = get_int();
        
        if (minutes < 0)
            printf("You must enter a positive number!\n");
    } 
    while (minutes<0);
        
    water_spent = (1.5 * gallon) * minutes;
    // 1.5 gallon per minute
    bottles = water_spent / 16;
    
    printf("Minutes: %i\nBottles: %i\n", minutes, bottles);
}