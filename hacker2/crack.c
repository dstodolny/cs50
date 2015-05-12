/**
 * cipher.c
 *
 * Dominik Stodolny
 * d.stodolny@gmail.com
 *
 * Cracks DES-based hashed password
 */
#define DICT "./passwords.txt"
#define MAXLENGTH 8

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <crypt.h>
#include <ctype.h>

void iterate(char* str, int idx, int len);
void crack(char *line);

char* ghash;
char salt[3];

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }

    ghash = argv[1];
    salt[0] = ghash[0];
    salt[1] = ghash[1];

    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int dwlen;
    char str[9];
    memset(str, 0, 9);

    fp = fopen(DICT, "r");
    if (fp == NULL)
    {
        exit(EXIT_FAILURE);
    }

    // dictionary attack
    while ((read = getline(&line, &len, fp)) != -1)
    {
        dwlen = strlen(line);
        line[dwlen - 1] = '\0';
        if (dwlen <= MAXLENGTH + 1)
        {
            crack(line);
        }
    }

    // brute force digits attack
    for (int i = 1; i <= MAXLENGTH; i++)
    {
        iterate(str, 0, i - 1);
    }

    fclose(fp);
    if(line)
    {
        free(line);
    }
    exit(EXIT_SUCCESS);
}

void iterate(char* str, int idx, int len)
{
    char c;

    if (idx < (len - 1))
    {
        for (c = '0'; c <= '9'; c++)
        {
            str[idx] = c;
            iterate(str, idx + 1, len);
        }
    }
    else
    {
        for (c = '0'; c <= '9'; c++)
        {
            str[idx] = c;
            crack(str);
        }
    }
}

void crack(char* line)
{
    if(strcmp(ghash, crypt(line, salt)) == 0)
    {
        printf("*** CRACKED! ***\n");
        printf("Password: ");
        puts(line);
        exit(0);
    }
}

