/**
 * greedy.c
 *
 * Dominik Stodolny
 * d.stodolny@gmail.com
 *
 * Returns the fewest number  of coins for a change
 */

#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float change;
    int coins = 0;

    printf("O hai! ");
    do
    {
        printf("How much change is owed?\n");
        change = GetFloat();
    }
    while (change < 0);

    // change dollars to cents
    int cents = (int) round(change * 100);

    while (cents > 0)
    {
        if (cents >= 25)
        {
            cents -= 25;
        }
        else if (cents >= 10)
        {
            cents -= 10;
        }
        else if (cents >= 5)
        {
            cents -= 5;
        }
        else
        {
            cents -= 1;
        }
        coins++;
    }

    printf("%i\n", coins);
}

