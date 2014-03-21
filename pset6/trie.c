// This will include the inplementation of the dictionary retrieval structure
// Be sure to add the prototypes to the header file, and change the Makefile
// to include this file. 

// This will also include the functions to initialize the tree, add nodes, 
// traverse the tree, and other things specific the tries.

// Each node in the trie will have two parts: the boolean "is_word"
// and the array of child nodes. The array will be of size 27, including
// all of the letters in the english alphabet and the apostrophe.

// The apostrophe at the root node, followed by another apostrophe,
// will point to a special element, called "trie_size" (We will use
// two apostrophies, since they don't occur together in english words)
// This is what the size() function will refer to in dictionary.c

// In this implementation, the apostrophe will be mapped to trie_node[27]

#include <stdbool.h>
#include <stdlib.h>

#include "trie.h"

trie_node* create_node(trie_node* parent, int index)
{
    // take the index of the parent and create
    // a new child node with a pointer to it
    parent->children[index] = malloc(sizeof(trie_node));

    // initialize all of new node's pointers to NULL
    for (int i = 0; i < 27; i++)
    {
        parent->children[index]->children[i] = NULL;
    }
    parent->children[index]->is_word = false;
    return parent->children[index];
}

trie_node* next_node(trie_node* parent, int index)
{
    // take the index of the parent and jump
    // to the child node
    if (parent->children[index] != NULL)
    {
        trie_node* next = parent->children[index];
        return next;
    }
    else
    {
        return NULL;
    }
}

void remove_branch(trie_node* node)
{
    // this will take the current node and remove
    // it and all of it's children from the trie.
    // if this method is called on the root,
    // the entire thing will be removed from memory.
    return;
}

