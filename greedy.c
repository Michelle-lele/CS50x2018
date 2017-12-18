#include <stdio.h>
#include <cs50.h>
#include <math.h>

int quarters, dimes, nickels, pennies, coins, rem_change;
float change;

int main(void)
{
    quarters = 25;
    dimes = 10;
    nickels = 5;
    pennies = 1;
    //prompt user to type change until positive number is entered
    do
    {
        change = get_float("O hai! How much change is owed?\n");
    }
    while (change < 0);

    if (change >= 0)
    {
        coins = 0;
        rem_change = round (change * 100);
        while (rem_change >= quarters)
        {
            coins++;
            rem_change = rem_change - quarters;
        }
        while (rem_change >= dimes)
        {
            coins++;
            rem_change = rem_change - dimes;
        }
        while (rem_change >= nickels)
        {
            coins++;
            rem_change = rem_change - nickels;
        }
        while (rem_change >= pennies)
        {
            coins++;
            rem_change = rem_change - pennies;
        }
        printf("%i\n", coins);
    }

    }