// Implements a dictionary's functionality 
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27
// macro to get the character to {0-26}
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

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
        struct node *getNewNode = NULL;
        getNewNode = (struct node *)malloc(sizeof(struct node));
        if (getNewNode)
        {
            getNewNode->is_word = false;

            for (int i = 0; i < 26; i++)
            {
                getNewNode->children[i] = NULL;
            }
        return getNewNode;
        } 
        else
        {
            return 0;
        }
}

void insert (struct node *top, const char *key)
    {
        // get the length of the word in order to
        // assign it to the n-nodes
        int length = strlen(key);
        // index is the trie depth
        int index;
        // crawl is a node used to traverse the trie
        struct node *crawl = root;
        for (int level = 0; level < length; level++)
        {
            // getting the index of the ith char
            // also get the lowercase
            index = CHAR_TO_INDEX(tolower(key[level]));      
            if(index == -58)
            {
                index = 26;
            }
            // if children[index] is NULL the create new new node
            // at that index
            if (!crawl->children[index])
            {
                crawl->children[index] = getNewNode();
            }
            // after creating the node move to the next one
            // by getting the pointer to crawl
            crawl = crawl->children[index];
        }
        // after all characters are done
        // set the deepest node to a leaf
        crawl->is_word = true;
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
    // set all children to NULL
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
    // word counter
    unsigned int amntWords = 0;
    bool check;
    // Insert words into trie
    // This get a string!
    check = false;
    while (fscanf(file, "%s", word) != EOF)
    {
        // Insert this string into the trie
        // Starting from root
        struct node *curr = root; 
        // loop through word characters
        // and insert word
        insert(curr, word);
        amntWords ++;
    }
    check = true;
    // Close dictionary
    fclose(file);
    // Indicate success
    return true;
}

unsigned int wordCount(struct node *crawl)
{
    int count = 0;
    if (crawl->is_word)
    {
        count ++;
    }
    
    for (int i = 0; i < N; i++)
    {
        if (crawl->children[i])
        {
            count += wordCount(crawl->children[i]);
        }
    }

    return count;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int words = 0;
    words += wordCount(root);
    return words;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    struct node *crawl = root;
    int index;
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        index = CHAR_TO_INDEX(tolower(word[i])); 
        if (index == -58)
        {
            index = 26;
        }
        if (crawl->children[index] == NULL)
        {
            return false;
            return 0;
        }
        else
        {
            crawl = crawl->children[index];
        }
    }

    return (crawl != NULL && crawl->is_word == true);
}

// Unloads dictionary from memory, returning true if successful else false
void free_node(struct node *crawl)
{
    if (!crawl)
    {
        return;
    }

    for (int i = 0; i < N; i++)
    {
        free_node(crawl->children[i]);
    }

    free(crawl);
}
bool unload(void)
{
    free_node(root);    
    return 1;
}
