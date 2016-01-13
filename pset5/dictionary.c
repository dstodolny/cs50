/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

unsigned int dictSize = 0;
node *root;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    node *cursor = root;
    
    for (int i = 0, l = strlen(word); i < l; i++)
    {
        int c = tolower(word[i]);
        int index = (c == '\'') ? CHARACTERS - 1 : c - 'a';
        
        if (cursor->children[index] == NULL)
        {
            return false;
        }
        
        cursor = cursor->children[index];
    }
    
    return (cursor->is_word) ? true : false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    
    FILE *fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }
    
    // initialize root of the trie
    root = (node *) malloc(sizeof(node));
    for (int i = 0; i < CHARACTERS; i++)
    {
        root->children[i] = NULL;
    }
    root->is_word = false;
    
    node *cursor = root;
    
    for (int c = fgetc(fp); c != EOF; c = fgetc(fp))
    {
        if (c == '\n')
        {
            cursor->is_word = true;        
            cursor = root;
            dictSize++;
        }
        else
        {
            
            int index = (c == '\'') ? CHARACTERS - 1 : c - 'a';
            if (cursor->children[index] == NULL)
            {
                cursor->children[index] = (node *) malloc(sizeof(node));
                for (int i = 0; i < CHARACTERS; i++)
                {
                    cursor->children[index]->children[i] = NULL;
                }
                cursor->children[index]->is_word = false;
            }
            cursor = cursor->children[index];
        }
    }
    
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return dictSize;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    return freeNode(root);
}

/**
 * Recursivly free every node
 */
bool freeNode(node *node)
{
    for (int i = 0; i < CHARACTERS; i++)
    {
        if (node->children[i] != NULL)
        {
            freeNode(node->children[i]);
        }
    }
    
    free(node);
    return true;
}
