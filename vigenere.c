#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int j;
//allows accepting command prompt argument
int main(int argc, string argv[])
{

    //accepts only 2 command prompt arguments, first is the program itself, second should be alphabetical key
    if (argc == 2)
    {
        //check if string contains only alphabetical symbols
        string keys = argv[1];
        for (j = 0; j < strlen(argv[1]); j++)
        {
            if (isalpha(keys[j]) == false)
            {
                printf ("Error! Please provide string of only alphabetical symbols\n");
                return 1;
            }
        }

        //get the index of the key character
        int key[strlen(keys)];
        for (j = 0; j < strlen(keys); j++)
        {
            if (isupper(keys[j]))
            {
                key[j] = (keys[j] - 'A');
            }

            else
            {
                key[j] = keys[j] - 'a';
            }

            printf ("%i", key[j]);
        }
        printf("\n");

        //prompt user for plaintext
        string plaintext = get_string("plaintext: ");
        printf ("ciphertext: ");

        // loops for each character in the plaintexts provided
        j = 0;
        for (int i = 0; i < strlen(plaintext); i++)
        {
            //check if the symbol is a character
            if (isalpha(plaintext[i]))
            {
                //check if character is uppercase
                if (isupper(plaintext[i]))
                {
                    //add key to the character by converting from ascii to index and ascii again
                    plaintext[i] = (plaintext [i] + key[j] - 'A') % 26 + 'A';
                }

                //check if character is lowercase
                if (islower(plaintext[i]))
                {

                    //add key to the character by converting from ascii to index and ascii again
                    plaintext[i] = (plaintext [i] + key[j] - 'a') % 26 + 'a';
                }

                printf ("%c", plaintext[i]);
                //increments key character only if it plaintext symbol is a character
                j++;

                //cycles the characters in the keys string
                if (j >= strlen(keys))
                {
                    j = 0;
                }
            }

            //if not a character print without change
            else
            {
                printf ("%c", plaintext[i]);
            }
        }
        printf ("\n");
        return 0;
    }

    else
    {
        printf ("Error! Please provide single argument\n");
        return 1;
    }
}
