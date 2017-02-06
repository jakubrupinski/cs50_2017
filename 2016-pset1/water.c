/*
* A small program that calculates the equivalent 
* of how many bottles of water you use up when you shower.
*/
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // initializing variables
    int minutes, bottle = 16;
    float gallons_minute = 1.5, ounces_minute = 128 * gallons_minute;
    float water_spent, result;
    
    // user-input time in minutes
    do
    {
        printf("How many minutes do you spend in the shower?\n");
        minutes = GetInt();
        
        if (minutes < 0)
            printf("You must enter a positive number!\n");
    }
    while (minutes < 0);

    
    // program calculates water spent, and converts it into a number of bottles
    water_spent = ounces_minute * minutes;
    result = (float)water_spent/bottle;
    
    printf("You pour down %.3f gallons, the equivalent of %.1f bottles of water while showering!\n", water_spent, result);
    
    return 0;
}