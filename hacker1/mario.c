/**
 * mario.c
 *
 * Dominik Stodolny
 * d.stodolny@gmail.com
 *
 * Prints two towers
 */

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height, j;
    do
    {
        printf("Height: ");
        height = GetInt();
    }
    while (height < 0 || height > 23);

    for (int i = 1; i <= height; i++)
    {
        for (j = height; j > i; j--)
        {
            printf(" ");
        }
        int k = j;
        for (; j > 0; j--)
        {
            printf("#");
        }
        printf("  ");
        for (; k > 0; k--)
        {
            printf("#");
        }
        printf("\n");
    }
    return 0;
}

