/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality. Future implementation to free malloc'ed memory
 * 
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// declare hashtable with all pointers initialized to NULL
node* hashtable[SIZE] = {NULL};

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // convert to all lower cases
    char temp[LENGTH + 1];
    int len = strlen(word);
    for(int i = 0; i < len; i++)
        temp[i] = tolower(word[i]);
    temp[len] = '\0';
    
    // find the index of the word
    unsigned long index = hash(temp);
    
    // check if this index entry even exists
    if (hashtable[index] == NULL) 
        {
        printf("Entry # %lu does not exist in hashtable.\n",index);
        return false;
        }
    
    node* cursor = hashtable[index];
    while (cursor)
    {
    if (!strcmp (cursor->word,temp))
        return true;
    cursor=cursor->next;
    }
    return false;
    
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // when loading dictionary create a hash table
    int index, counter=0;
    char word[LENGTH + 1];
    
    // open dictionary file
    FILE* dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }
    
/* let's initialize the array by adding a new_node at each entry in the index. the elements to the array should all point 
* to unique addresses!  */

    // file to keep track of hash values for the words in the dictionary
    FILE* log= fopen("log.txt","w");
    if (log == NULL)
    {
        printf("Could not create log file\n");
        return false;
    }
    
    // iterate through all the words in the dictionary
    while(fscanf(dic,"%s\n",word)!=EOF)
    {
        // malloc a node* save new words in the "word" field
        node* new_node = malloc(sizeof(node));
        if (new_node==NULL) return false;
        new_node->next= NULL;
        strcpy(new_node->word,word); 
        
        // hash the word to get the index of the "bucket" in the hash table, then insert the node into the linked list
        index = hash(new_node->word);
        
        // write word and corresponding index into log
        fprintf(log,"Word %s with hash %d\n",new_node->word,index);
        
        // insert new node into list, nodes will be arranged according to alphabetical order;traverse the list until cursor points to last node
        node* cursor = hashtable[index];
        // found an empty bucket
        if (cursor == NULL)
            {
                hashtable[index] = new_node;
                counter++;
            }
    
        // in case of collisions append a node to the list
        else
        {
            while (cursor->next != NULL)
                {
                        cursor = cursor->next;
                }
            cursor->next = new_node;
            counter++;
        }
        
    } 
    
fclose(log);
printf("loaded %d words into dictionary\n",counter);
return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return false;
}

// djb2 algorithm used by dan bernstein
unsigned long hash(char *str)
    {
        unsigned long hash = 5381;
        int c;

        while ((c = *str++))
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

        return hash % SIZE;
    }