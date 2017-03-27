#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define ALPHABET_LENGTH 26


char  *encrypt(char  *text, int key);


int main(int argc, char  *argv[])
{
    // if not enough or more than 1 arguments - exit and return an error
    if (argc != 2)  
    {
        printf("\nIncorrect number of arguments!\n");
        return 1;
    }
    
    char  *plaintext = malloc(100 * sizeof(char)), *ciphertext;
    int key = atoi(argv[1]);    // convert console key argument to int
    
    printf("plaintext: ");
    plaintext = fgets(plaintext, 100, stdin);
    ciphertext = encrypt(plaintext, key);
    
    printf("ciphertext: %s\n", ciphertext);
    
    return 0;
}

char *encrypt(char *plaintext, int key)
{
    int text_length = strlen(plaintext),
        alphabet_array[ALPHABET_LENGTH];    //this array will hold indexes of each acii letter in alphabet indexing
    char *ciphertext = plaintext; // first copy the plaintext, then encrypt every letter
    bool has_shifted = false;   //  check if letter has shifted
    
    // assign alphabet to an array for alphabet indexing
    for (int i = 'a', j = 0; i <= 'z'; i++, j++)
    {
        alphabet_array[j] = i;
    }
  
    /*  Check each letter of the whole plaintext and shift it */
    for (int i = 0, n = text_length; i < n; i++)
    {
        has_shifted = false;    //  each next letter is unshifted in the beginning
        
        if (isalpha(ciphertext[i])) // if plaintext character is a letter - go inside loop to shift it
        {
            for (int j = 0; j < ALPHABET_LENGTH; j++)
            {
                /* If letter already shifted - stop nested loop and go to next letter of plaintext (i++) */
                if (has_shifted)
                {
                    break;
                }
                
                /* when current plaintext letter found in alphabet array - check what letter 
                        it should be after shifting it in alphabet indexing and assign it to cipher */
                if (tolower(ciphertext[i]) == alphabet_array[j])    
                {
                    if (islower(ciphertext[i]))
                    {
                        ciphertext[i] = tolower(alphabet_array[(j + key) % ALPHABET_LENGTH]);   // modulo returns index back to 0
                    }
                    else
                    {
                        ciphertext[i] = toupper(alphabet_array[(j + key) % ALPHABET_LENGTH]);   // modulo returns index back to 0
                    }
                    
                    has_shifted = true; // letter has shifted so it's true now
                }
            }
        }
    }
    
    return ciphertext;
}
