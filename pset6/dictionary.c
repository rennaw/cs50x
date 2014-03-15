/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>

#include "dictionary.h"

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
    // first,create root node in dictionary, then create a cursor
    trie_root* root = create_root();
    
    // now open the dictionary file and word buffer and word count
    FILE* dict_fp = fopen(dictionary, "r");
    char word[LENGTH+1];
    int wcount = 0, windex = 0;

    // for each dictionary char, iterate through the trie
    for (int c = fgetc(dict_fp); c != EOF; c = fgetc(dict_fp))
    {
        
        if (isalpha(c) || (c == '\'' && windex > 0))
        {
            if
            int index = islower(c) - 'a'
            trie_node* child = create_node(parent, index); 
        }
        else if (c == '\n')
        {
            wcount++;
        }
    }

    // each element in children corresponds to a different letter

    // check the value at children[i]

    // if NULL, malloc new node, have children[i] point to it

    // if not NULL, move to new node and continue

    // if at end of word, is_word = true, and call addword(dict_size)

    return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // access trie_size node and reports it
    if (root[0]->child[0]->trie_size != NULL)
    {
        unsigned int size = root[0]->child[0]->trie_size;
        return size;
    }
    else
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

