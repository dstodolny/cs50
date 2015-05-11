/**
 * vigenere.c
 *
 * Dominik Stodolny
 * d.stodolny@gmail.com
 *
 * Encrypts messages using Vigenere's cipher.
 *
 * Usage: ./vigenere keyword 
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>
#include <stdbool.h>

int encipher(int letter, int k);
int base(int letter);
int calc_k(int letter);
bool isword(string word);

int main(int argc, string argv[])
{
    if (argc != 2 || !isword(argv[1]))
    {
        printf("Usage: ./vigenere keyword\n");
        printf("keyword must be a word\n");
        return 1;
    }

    string kword = argv[1];
    int kword_length = strlen(kword);


    string p;
    p = GetString();

    for (int i = 0, j = 0, n = strlen(p); i < n; i++)
    {
        if (isalpha(p[i]))
        {
            // wrap around the keyword
            int letter = kword[j % kword_length];

            printf("%c", encipher(p[i], calc_k(letter)));
            j++;
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

int calc_k(int letter)
{
    if (isupper(letter))
    {
        return letter - 'A';
    }
    else
    {
        return letter - 'a';
    }
}

bool isword(string word)
{
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if (!isalpha(word[i]))
        {
            return false;
        }
    }
    return true;
}

