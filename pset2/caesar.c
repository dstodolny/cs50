/**
 * caesar.c
 *
 * Dominik Stodolny
 * d.stodolny@gmail.com
 *
 * Encrypts messages using Caesar's cipher.
 *
 * Usage: ./caesar key
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

int encipher(int letter, int k);
int base(int letter);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int k = atoi(argv[1]);

    string p;
    p = GetString();

    for (int i = 0, n = strlen(p); i < n; i++)
    {
        if (isalpha(p[i]))
        {
            printf("%c", encipher(p[i], k));
        }
        else
        {
            printf("%c", p[i]);
        }
    }
    printf("\n");

    return 0;
}

int encipher(int letter, int k)
{
    
    return (letter - base(letter) + k) % 26 + base(letter);
}

int base(int letter)
{
    if (isupper(letter))
    {
        return 'A';
    }

    return 'a';
}

