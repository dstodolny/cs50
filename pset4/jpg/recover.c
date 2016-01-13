/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
 
#define BLOCKSIZE 512

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

bool isJPEG(BYTE* p);
char* fileName(int n);

int main(void)
{
    FILE* file = fopen("./card.raw", "r");
    FILE* temp;
    
    if (file == NULL)
    {
        printf("Could not open card.raw\n");
        return 1;
    }
    
    BYTE* buffer = malloc(BLOCKSIZE);
    
    if (buffer == NULL)
    {
        printf("Error allocating memory\n");
        return 2;
    }
    
    char* filename = malloc(sizeof(char) * 8);
    int counter = 0;
    
    bool fileOpened = false;
    
    while(fread(buffer, sizeof(buffer), 1, file) == 1)
    {   
        if(isJPEG(buffer))
        {
            sprintf(filename, "%03d.jpg", counter);
            counter++;
            
            if(fileOpened)
            {
                fclose(temp);
                temp = fopen(filename, "w");
                fwrite(buffer, sizeof(buffer), 1, temp);
            }
            else
            {
                temp = fopen(filename, "w");
                fwrite(buffer, sizeof(buffer), 1, temp);
                fileOpened = true;
            }             
        }     
        else if (fileOpened)
        {
            fwrite(buffer, sizeof(buffer), 1, temp);
        }
    }
    
    if(temp)
    {
        fclose(temp);
    }
    fclose(file);
    free(filename);
    free(buffer);
    
    return 0;
}

bool isJPEG(BYTE* p)
{
    return (p[0] == 0xff && p[1] == 0xd8 && p[2] == 0xff && (p[3] == 0xe0 || p[3] == 0xe1));
}

