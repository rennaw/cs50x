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



typedef struct trie_node
{
    bool is_word = false;
    struct trie_node* children[ALPHABET];
}
trie_node;

typedef struct trie_root
{
    int trie_size;
    trie_node* children[ALPHABET];
}
trie_root;

trie_node* create_node(trie_node* parent, int index)
{
    // take the index of the parent and create
    // a new child node with a pointer to it
    parent->children[index] = malloc(sizeof(trie_node));

    // initialize all of new node's pointers to NULL
    for (i = 0; i < ALPHABET; i++)
    {
        parent->children[index]->children[i] = NULL;
    }
}

trie_root* create_root(void)
{
    trie_root* root = malloc(sizeof(trie_root));
    for (i = 0; i < ALPHABET; i++)
    {
        root->children[i] = NULL;
    }
    root->trie_size = 0;
    return root;
}

trie_node* next_node(trie_node* parent, int index)
{
    // take the index of the parent and jump
    // to the child node
    trie_node* next = parent[index]
}

void remove_branch(trie_node* node)
{
    // this will take the current node and remove
    // it and all of it's children from the trie.
    // if this method is called on the root,
    // the entire thing will be removed from memory.
}

void set_trie_size(trie_node* root)
{
    // this will create a special 'trie_size' node
    // that is linked in this fashion:
    // root[0]->child[0]->trie_size
    trie_node* child = create_node(root, 0);
    int* trie_size = malloc(sizeof(int));
    root->child[0] = trie_size;
}

