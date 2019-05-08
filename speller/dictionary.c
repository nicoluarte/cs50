// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;

// Represents a trie
node *root;

// Return a new node
// This function returns a node structure pointer
struct node* getNewNode() // gets no input
{
    // Allocate memory for newly created node
    struct node* node = (struct node*)malloc(sizeof(struct node));
    // It not the end for the word 
    node->is_word = false;

    // returns the newly created node struct
    return node;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        // Insert this string into the trie
        // Starting from root
        struct node curr = *root; 
        // loop through word characters
        for (int i  = 0; i < strlen(word); i++)
        {
            // get the ith char 
            char ch = word[i];

        }
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
}
