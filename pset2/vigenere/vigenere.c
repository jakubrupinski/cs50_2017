#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_LENGTH 26


string encrypt(string text, string keyword);


int main(int argc, string argv[])
{
    //  create keyword string that keeps the terminal argument from user
    
    /* ### SANITY CHECKS FOR TERMINAL INPUT ### */
    // if not enough or more than 1 arguments - exit and return an error
    if (argc != 2)  
    {
        printf("\nIncorrect number of arguments!\n");
        return 1;
    }
    else
    {
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            if(isalpha(argv[1][i]) == 0)
            {
                printf("Input parameter is not a string/character!\n");
                return 1;       
            }
        }
    }
    /* ### ### ### ### ### ### ### ### ### ### */
    
    //  declare variables
    string
        plaintext,
        ciphertext,
        keyword = argv[1];   

    printf("plaintext: ");
    plaintext = get_string();
    ciphertext = encrypt(plaintext, keyword);
    printf("ciphertext: %s\n", ciphertext);
    
    return 0;
}

string encrypt(string plaintext, string keyword)
{
    int 
        text_length = strlen(plaintext),
        alphabet_array[ALPHABET_LENGTH],    // this array will hold indexes of each acii letter in alphabet indexing
        letter_key = 0;     //  keeps shifting key value for every letter
        
    string 
        ciphertext = plaintext; // first copy the plaintext, then encrypt every letter
        
    bool 
        has_shifted = false,   //  check if letter has shifted
        letter_key_found = false; // check if key for keyword letter found (so it doesn't have to loop unnecessarily)

    
    // assign alphabet to an array for alphabet indexing
    for (int i = 'a', j = 0; i <= 'z'; i++, j++)
    {
        alphabet_array[j] = i;
    }
  
    /*  Check each letter of the whole plaintext and shift it 
        int l is for not changing the letter_key when on non-letter character   */
    for (int i = 0, l = 0, n = text_length; i < n; i++, l++)
    {
        has_shifted = false;    //  each next letter is unshifted in the beginning
        letter_key_found = false;

        
        if (isalpha(ciphertext[i])) // if plaintext character is a letter - go inside loop to shift it
        {
            for (int j = 0; j < ALPHABET_LENGTH; j++)   //  iterate over every letter in alphabet 
            {
                /* If letter already shifted - stop nested loop and go to next letter of plaintext (i++) */
                if (has_shifted)
                {
                    break;
                }
                
                if (letter_key_found == false)  //  if letter key not found yet - find it
                {
                    /*  iterate over every letter value in alphabet index until 
                        we  find one that matches current character in keyword */ 
                    for (int k = 0; k < ALPHABET_LENGTH; k++) 
                    {
                        /* we use modulo strlen(keyword) so indexes don't exceed keyword length */
                        if (tolower(keyword[l % strlen(keyword)]) == alphabet_array[k])  // if key value found - assign and exit loop
                        {
                            letter_key = k;   // modulo by keyword length so index reverts back to beginning
                            letter_key_found = true;
                            break;
                        }
                    }
                }
                //  find and assign new key for each letter (find value in alphabet index array)
                
                
                
                /* when current plaintext letter found in alphabet array - check what letter 
                    it should be after shifting it in alphabet indexing and assign it to cipher */
                if (tolower(ciphertext[i]) == alphabet_array[j])    
                {
                    
                    if (islower(ciphertext[i]))
                    {
                        ciphertext[i] = tolower(alphabet_array[(j + letter_key) % ALPHABET_LENGTH]);   // returns index back to 0
                    }
                    else
                    {
                        ciphertext[i] = toupper(alphabet_array[(j + letter_key) % ALPHABET_LENGTH]);   // returns index back to 0
                    }
                    
                    has_shifted = true; // letter has shifted so it's true now
                }
            }
        }
        else
        {
            l--;
        }
    }
    
    return ciphertext;
}
