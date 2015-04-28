/**
 * credit.c
 *
 * Dominik Stodolny
 * d.stodolny@gmail.com
 *
 * Validates credit card number.
 */

#include <cs50.h>
#include <stdio.h>
#include <stdbool.h>

int main(void)
{
    printf("Number: ");    
    long long number = GetLongLong();

    bool left = true;
    int left_sum, right_sum, company;
    left_sum = right_sum = 0;

    while (number > 0)
    {
        int digit = number % 10;

        // save the very first digit
        company = number;

        number /= 10;

        if (left == true)
        {
            left_sum += digit;
            left = false;
        }
        else
        {
            digit *= 2;
            
            while (digit > 0)
            {
                right_sum += digit % 10;
                digit /= 10;
            }
            left = true;
        }
    }

    if ((left_sum + right_sum) % 10 == 0)
    {
        switch (company)
        {
            case 3:
                printf("AMEX\n");
                break;
            case 4:
                printf("VISA\n");
                break;
            case 5:
                printf("MASTERCARD\n");
                break;
        }
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}

