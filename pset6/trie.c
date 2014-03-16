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
    for (int i = 0; i < 27; i++)
    {
        if (node->children[i] != NULL)
        {
            remove_branch(node->children[i]);
        }
        free(node);
    }
    return;
}

