#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h>
#include <stdlib.h>

// struct and function prototypes

typedef struct trie_node
{
    bool is_word;
    struct trie_node* children[27];
}
trie_node;

typedef struct trie
{
    trie_node* root_ptr;
    int size;
} 
trie;

trie_node* create_node(trie_node* parent, int index);

trie_node* next_node(trie_node* parent, int index);

void remove_branch(trie_node* node);

#endif // TRIE_H
