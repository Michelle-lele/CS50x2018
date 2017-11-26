#include <stdio.h>
#include <cs50.h>
int main(void)
{
    int bottles;
    int m= get_int("Type how many minutes you spend in the shower:");
    bottles=m*12;
    printf("Minutes: %i\nBottles: %i\n", m, bottles);
}