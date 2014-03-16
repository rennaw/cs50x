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

#include "dictionary.h"
#include "trie.h"

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // traverse the trie, checking each letter

    // if the word is in the dictionary, return true

    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // first, create trie container
    trie* dict = malloc(sizeof(trie));
    trie_node* root = malloc(sizeof(trie_node));
    dict->root_ptr = root;

    trie_node* cursor = root;

    // now open the dictionary file and word buffer and word count
    FILE* dict_fp = fopen(dictionary, "r");
    if (dict_fp != NULL) 
    {
        printf("Dictionary file opened.");
    }
    else
    {
        return 1;
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
            cursor = root;
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
   return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // free the nodes from the bottom to the top, using recursion
    return false;
}

