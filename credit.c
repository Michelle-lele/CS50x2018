#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    //prompt the user to enter credit card number
    string ccnum = get_string("Number: ");
    // implement additonal checks to allow only digits

    long long card_num = atoll(ccnum);
    int lenght = log10(card_num) + 1;
    int total = 0;
    //check if number is 13,15 or 16 digits long, else return invalid
    if (lenght == 13 || lenght == 15 || lenght == 16 )
    {

        //increment each digit in the card number started from the end
        int i = lenght - 1;
        int num;
        while (i >= 0)
        {
            //counted from last digit, even positions add to sum
            if (i >= 0)
            {
                num = (ccnum[i] - '0');
                total = total + num;
                i--;
            }
            //odd position multiply by 2, then add to sum
            if (i >= 0)
            {
                num = (ccnum[i] - '0');
                //if num*2 > 9, take the single digits and sum them, then assign to num
                if (num * 2 > 9)
                {
                    num = (num * 2) % 10;
                    total = total + (1 + num);
                    i--;
                }
                else
                {
                    total = total + (num * 2);
                    i--;
                }
            }
        }
    }
    else
    {
        printf ("INVALID\n");
        return 0;
    }

    // check if last digit is 0 ((%10) is 0)
    if (total % 10 == 0)
    {
        //VISA starts with 4, 13 or 16 digit number
        //if 13 check if first digit is 4, else return invalid
        if (lenght == 13 && ccnum[0] == '4')
        {
            printf ("VISA\n");
            return 0;
        }
        if (lenght == 16 && ccnum[0] == '4')
        {
            printf ("VISA\n");
            return 0;
        }

        //MASTERCARD starts with 51, 52, 53, 54, or 55, 16 digit number
        if (lenght == 16 && ccnum[0] == '5')
        {
            //if 5 check if second digit is 1,2,3,4,5, else return invalid
            if (ccnum[1] == '1' || ccnum[1] == '2' || ccnum[1] == '3' || ccnum[1] == '4' || ccnum[1] == '5')
            {
                printf ("MASTERCARD\n");
                return 0;
            }
        }
        //AMEX starts with 34 or 37, 15 digit number
        //if 15 check if first two digits are 34 or 37, else return invalid
        if (lenght == 15 && ccnum[0] == '3')
        {
            if (ccnum[1] == '4' || ccnum[1] == '7')
            {
                printf ("AMEX\n");
                return 0;
            }
            else
            {
                printf("INVALID\n");
                return 0;
            }
        }
        else
        {
            printf("INVALID\n");
            return 0;
        }
    }

    else
    {
        printf("INVALID\n");
        return 0;
    }
}