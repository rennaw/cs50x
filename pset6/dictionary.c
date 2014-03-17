/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"
#include "trie.h"

trie* dict;
trie_node* cursor;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // traverse the trie, checking each letter
    cursor = dict->root;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if (cursor->children[i] != NULL)
        {
            cursor = next_node(cursor, i);
        }
        else
        {
            return false;
        }
    }
    
    // if word is dictionary, return true
    if (cursor->is_word == true)
    {
        return true;
    } 
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // first, create trie container
    dict = malloc(sizeof(trie));
    dict->root = malloc(sizeof(trie_node));

    cursor = dict->root;
    
    // now open the dictionary file and word buffer and word count
    FILE* dict_fp = fopen(dictionary, "r");
    if (dict_fp == NULL) 
    {
        return false;
    }
    
    // for each dictionary char, iterate through the trie
    for (int c = fgetc(dict_fp); c != EOF; c = fgetc(dict_fp))
    {
        if (isalpha(c) || (c == '\''))
        {
            int index = tolower(c) - 'a';
            if (cursor->children[index] == NULL)
            {
                trie_node* child = create_node(cursor, index);
                cursor = child;
            }
            else
            {
                cursor = next_node(cursor, index);
            }
        }
        else if (c == '\n')
        {
            dict->size++;
            cursor->is_word = true;
            cursor = dict->root;
        }
    }
    fclose(dict_fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
   return dict->size;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // free the nodes from the bottom to the top, using recursion
    remove_branch(dict->root);
    free(dict);
    return true;
}

