#define _XOPEN_SOURCE
#include <stdio.h>
#include <cs50.h>
#include <unistd.h>
#include <string.h>

char pass[5];
int n = 1;
int i;

int main(int argc, string argv[1])
{
    //check if 2 cl arguments are provided by user
    if (argc == 2)
    {
        //generate combinations of 1, 2, 3 and 4 letter passwords including a-z, A-Z
        char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

        for (i = 0; i < 52; i++)
        {
            pass[0] = charset [i];
            pass[1] = '\0';
            n++;
            //printf("%s, ", pass);
            if (strcmp (crypt (pass, "50"), argv[1]) == 0)
            {
               //print the pass
               printf ("%s\n", pass);
               return 0;
            }
        }

        for (i = 0; i < 52; i++)
        {
            pass[0] = charset [i];

            for (int ii = 0; ii < 52; ii++)
            {
                pass[1] = charset[ii];
                pass[2] = '\0';
                n++;
                //printf("%s, ", pass);
                if (strcmp (crypt (pass, "50"), argv[1]) == 0)
                {
                     //print the pass
                     printf ("%s\n", pass);
                     return 0;
                }
           }
        }

         for (i = 0; i < 52; i++)
        {
           pass[0] = charset [i];

           for (int ii = 0; ii < 52; ii++)
           {
               pass[1] = charset[ii];

               for (int iii = 0; iii < 52; iii++)
               {
               pass[2] = charset[iii];
               pass[3] = '\0';
               n++;
               //printf("%s, ", pass);
                     if (strcmp (crypt (pass, "50"), argv[1]) == 0)
                    {
                          //print the pass
                          printf ("%s\n", pass);
                          return 0;
                    }
               }
            }
        }

        for (i = 0; i < 52; i++)
        {
            pass[0] = charset [i];

            for (int ii = 0; ii < 52; ii++)
            {
                pass[1] = charset[ii];

                for (int iii = 0; iii < 52; iii++)
                {
                    pass[2] = charset[iii];
                    for(int iiii = 0; iiii < 52; iiii++)
                    {
                        pass[3] = charset[iiii];
                        pass[4] = '\0';
                        n++;
                        //printf("%s, ", pass);
                        if (strcmp (crypt (pass, "50"), argv[1]) == 0)
                        {
                            //print the pass
                            printf ("%s\n", pass);
                            return 0;
                        }
                    }

                }
            }
        }
    }

    //print error message if more or less than 2 arguments are provided by user
    else
    {
        printf ("Error! Provide single argument!\n");
        return 1;
    }
}