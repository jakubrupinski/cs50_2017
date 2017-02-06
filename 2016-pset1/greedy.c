/*
* A program that calculates minimal amount of coins required to give change
*/
#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // initializing variables
    int change, coins = 0, quarter = 25, dime = 10, nickel = 5, penny = 1,
    quarter_count = 0, dime_count = 0, nickel_count = 0, penny_count = 0;
    float input;
    
    // taking user input for change
    do
    {
        printf("Enter cash amount: ");
        input = GetFloat();
        
        if (input < 0)
            printf("Wrong input, try again!\n");
    }
    while (input < 0);
    
    // converting the change to an int, fixing the imprecision by rounding it
    change = round(input*100);
    
    // dividing change into smaller coins using while loops
    while (change >= quarter)
    {
        change -= quarter;
        coins++;
        quarter_count++;
    }
    
    while (change >= dime)
    {
        change -= dime;
        coins++;
        dime_count++;
    }
    
    while (change >= nickel)
    {
        change -= nickel;
        coins++;
        nickel_count++;
    }
    
    while (change >= penny)
    {
        change -= penny;
        coins++;
        penny_count++;
    }
    
    
    
    /*
    * printf("Your cash input was %.2f dollar(s).\n", input);
    * printf("Your change in coins is %d quarters, "
    * "%d dimes, %d nickels and %d pennies.\n",
    *     quarter_count, dime_count, nickel_count, penny_count);
    * printf("You will get this many coins: ");
    */
    
    printf("%d\n", coins);
    return 0;
}