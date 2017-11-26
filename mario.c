#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int row, space, hash, height;
    //get user input for pyramid height
    height = get_int("Height:");
    //if height's not positive number or less than 24, promp user
    while (height < 0 || height > 23)
    {
        height = get_int("Height:");
    }
    if (height >= 0 && height <= 23)
    {
        //print as much spaces as needed depending on specified height
        for (row = 1; row <= height; row++)
        {
            for (space = 0; space < (height - row); space++)
            {
                printf(" ");
            }
            //print as many hashes as needed depending on the row number, first raw has 2 hashes
            for (hash = 1; hash <= (row + 1); hash++)
            {
                printf("#");
            }
            printf("\n");
        }
    }
}