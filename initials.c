#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string name = get_string("");
    //check if first leter is alpha, if yes print f, move to next
    int i = 0;

    if (isalpha(name[i]))
    {
        printf ("%c", toupper(name[i]));
        i++;
    }
    else
    {
        i ++;
    }

    //check if alfa and previous was space if yes printf
    while (i < strlen(name))
    {
        if ( isalpha(name[i]) && (isspace(name[i - 1])))
        {
            printf ("%c", toupper(name[i]));
        }
        i++;
    }
        printf ("\n");

}