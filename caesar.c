#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//allows accepting command prompt argument
int main(int argc, string argv[])
{
   //accepts only 2 command prompt arguments, first is the program itself
   if (argc == 2)
   {
      //converts string to an integer
      int key = atoi(argv[1]);
      //prompt user for plaintext
      string plaintext = get_string("plaintext: ");
      printf ("ciphertext: ");
      // loops for each character in the plaintexts provided
      for (int i = 0; i < strlen(plaintext); i++)
      {
         //check if the symbol is a character
         if (isalpha(plaintext[i]))
         {
          //check if character is uppercase and less than 90 ascii when key added
          if (isupper(plaintext[i]))
          {
              plaintext[i] = (plaintext [i] + key - 'A') % 26 + 'A';
          }

         //check if character is lowercase and less than 122 ascii when key added
         if (islower(plaintext[i]))
         {
              plaintext[i] = (plaintext [i] + key - 'a') % 26 + 'a';
         }

         printf ("%c", plaintext[i]);
      }

        //if not a character print without change
        else
        {
            printf ("%c", plaintext[i]);
        }
     }
       printf ("\n");
   }
   else
   {
        printf ("Error! Please provide non negative integer\n");
        return 1;
   }
}
