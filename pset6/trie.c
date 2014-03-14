// This will include the inplementation of the dictionary retrieval structure
// Be sure to add the prototypes to the header file, and change the Makefile
// to include this file. 

// This will also include the functions to initialize the tree, add nodes, 
// traverse the tree, and other things specific the tries.

// Each node in the trie will have two parts: the boolean "is_word"
// and the array of child nodes. The array will be of size 27, including
// all of the letters in the english alphabet and the apostrophe.

// The apostrophe at the root node will point to a special element, 
// called "trie_size" that will be linked from the root by way of
// two apostrophies (since they don't occur together in english words)
// This is what the size() function will refer to in dictionary.c
