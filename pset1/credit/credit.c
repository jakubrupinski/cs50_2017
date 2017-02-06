#include <stdio.h>
#include <cs50.h>

long long user_input(void);
int card_length(long long credit_card);
void is_card_valid(long long credit_card);


int main(void)
{
    long long card_number = user_input();
    // int length = card_length(card_number);
    // printf("Card number: %lld\nCard number length: %d\n", card_number, length);
    is_card_valid(card_number);
    return 0;
}


long long user_input(void)
{
    long long card_number;
    /*
    do
    {
        printf("Number: ");
        card_number = get_long_long();
        printf("%d\n", card_length(card_number));
    }
    while(card_length(card_number) < 13 && card_length(card_number) > 16 );
    */
    printf("Number: ");
    card_number = get_long_long();
    return card_number;
}


int card_length(long long credit_card)
{
    int card_length = 0;
    
    for(long long i = credit_card; i > 0; i /= 10)
    {
        card_length++;
    }
    
    return card_length;
}

void is_card_valid(long long credit_card)
{
    int length = card_length(credit_card),
    last_index = length-1,
    sum_non_multiplied = 0,
    sum_multiplied = 0,
    total_sum = 0;
    
    long long card_number_array[length]; 
    
    for (int i = last_index; i >= 0; i--)    // get card number into an array
    {
        card_number_array[i] = credit_card % 10;
        credit_card /= 10;
    }
    
    for (int i = last_index-1; i >= 0; i -= 2)   // sum digits multiplied by 2
    {
        if (((int)card_number_array[i] * 2) >= 10)  // break up two-digit numbers into two digits
        {

            sum_multiplied += ((int)card_number_array[i] * 2) % 10; // ones
            sum_multiplied += ((int)card_number_array[i] * 2) / 10; // tenths
            // printf("number index : %d, number = %d\n", i+1, (int)card_number_array[i]);
            // printf("sum multiplied = %d + %d\n", sum_multiplied, (int)card_number_array[i] * 2);
        }
        else
        {
            sum_multiplied += (int)card_number_array[i] * 2;    // if single digit - sum 
            // printf("number index : %d, number = %d\n", i+1, (int)card_number_array[i]);
            // printf("sum multiplied = %d + %d\n", sum_multiplied, (int)card_number_array[i] * 2);
        }
    }
    
    if (length % 2 == 1)    // if uneven - start at second number
    {
        for (int i = 0; i <= last_index; i += 2) // sum non-multiplied digits
        {
            sum_non_multiplied += (int)card_number_array[i];
            // printf("uneven number index : %d, number = %d\n", i+1, (int)card_number_array[i]);
            // printf("sum nonmultiplied = %d + %d\n", sum_non_multiplied, (int)card_number_array[i] * 2);
        }
    }
    else
    {
        for (int i = 1; i <= last_index; i += 2) // sum non-multiplied digits
        {
            sum_non_multiplied += (int)card_number_array[i];
            // printf("uneven number index : %d, number = %d\n", i+1, (int)card_number_array[i]);
            // printf("sum nonmultiplied = %d + %d\n", sum_non_multiplied, (int)card_number_array[i] * 2);
        }
    }
    
    total_sum = sum_multiplied + sum_non_multiplied; // total sum of multiplied and unmultiplied
    // printf("sum nonmultiplied is %d\n", sum_non_multiplied);
    // printf("sum multiplied is %d\n", sum_multiplied);
    // printf("Total sum: %d\n", total_sum);
    
    if (total_sum % 10 == 0)
    {
        switch (card_number_array[0])   // check what kind of card and if it's valid
        {
            case 3:
            if (card_number_array[1] == 4 || card_number_array[1] == 7)
            {
                printf("AMEX\n");
                break;
            }
            case 4:
            printf("VISA\n");
            break;
            
            case 5:
            if (card_number_array[1] == 1 || card_number_array[1] == 2 
                    || card_number_array[1] == 3 || card_number_array[1] == 4
                        || card_number_array[1] == 5)
                {
                    printf("MASTERCARD\n");
                    break;
                }
                
            default:
            printf("INVALID\n");
            break;
        }
    }
    else
    {
        printf("INVALID\n");
    }
}