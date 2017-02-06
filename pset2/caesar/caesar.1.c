#include <stdio.h>
#include <cs50.h>
#include <string.h>

string encrypt(string text, int key);

int main(int argc, string argv[])
{
    // if not enough or more than 1 arguments - return an error
    if (argc != 2)  
    {
        printf("Incorrect number of arguments!");
        return 1;
    }
    
    string plaintext, ciphertext;
    int key = atoi(argv[1]);    // convert console key argument to int
    
    printf("plaintext: ");
    plaintext = get_string();
    ciphertext = encrypt(plaintext, key);
    printf("ciphertext: %s\n", ciphertext);
    
    return 0;
}

string encrypt(string plaintext, int key)
{
    int text_length = strlen(plaintext);
    string ciphertext = plaintext; // first copy the plaintext, then encrypt it
    
    for (int i = 0, n = text_length; i < n; i++)
    {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') // for lower-case characters
        {
            for (int j = 0; j < key; j++)   // crypt every character of ciphertext
            {
                if (ciphertext[i] >= 'z')
                {
                    ciphertext[i] = 'a';
                }
                else
                {
                    ciphertext[i]++;
                }
            }
        }
        else if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z')    // for upper-case characters
        {
            for (int j = 0; j < key; j++)   // crypt every character of ciphertext
            {
                if (ciphertext[i] >= 'Z')
                {
                    ciphertext[i] = 'A';
                }
                else
                {
                    ciphertext[i]++;
                }
            }
        }
    }
    
    return ciphertext;
}