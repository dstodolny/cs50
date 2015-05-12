/**
 * initials.c
 *
 * Dominik Stodolny
 * d.stodolny@gmail.com
 *
 * Obtains initials from a name.
 */

#include <stdio.h>
#include <cs50.h>
#include <stdbool.h>
#include <ctype.h>

int main(void)
{
    string fullname;
    bool got_letter = false;

    fullname = GetString();
    
    while (*fullname != '\0')
    {
        if (got_letter == false && *fullname != ' ')
        {
            printf("%c", toupper(*fullname));
            got_letter = true;
        }
        else if(*fullname == ' ')
        {
            got_letter = false; 
        }

        fullname++;
    }
    printf("\n");

    return 0;
}
        
