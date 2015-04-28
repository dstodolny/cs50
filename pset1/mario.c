/**
 * mario.c
 *
 * Dominik Stodolny
 * d.stodolny@gmail.com
 *
 * Prints mario-like pyramid
 */

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    do
    {
        printf("Height: ");
        height = GetInt();
    }
    while (height < 0 || height > 23);

    for (int i = 1; i <= height; i++)
    {
        int j;

        for (j = height; j > i; j--)
        {
            printf(" ");
        }
        for (; j >= 0; j--)
        {
            printf("#");
        }
        printf("\n");
    }
}
   
