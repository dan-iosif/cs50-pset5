/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 * 
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
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
    
    node* hashtable[SIZE];
    for(int i=0; i<SIZE;i++)
    {
        node* new_node=malloc(sizeof(node));
        if (new_node == NULL) return false;
        
        new_node -> next = NULL;
        strcpy(new_node->word,"zzzz");
        hashtable[i]=new_node;
        if (i == SIZE - 1) 
            free(new_node);
    }

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
        
        // write word into log
        fprintf(log,"Word %s with hash %d\n",new_node->word,index);
        
        // insert new node into list, nodes will be arranged according to alphabetical order;traverse the list until cursor points to last node
        node* cursor = hashtable[index];
        // how do you handle an empty bucket. that is an index in the hash table where no words have been saved yet? you know that next is set to NULL
        if (strcmp(cursor->word,"zzzz") == 0)
            {cursor=new_node;
            counter++;}
    
        // in case of collisions eat shit
        else
        {
            while (cursor->next != NULL)
                {
                        cursor = cursor->next;
                }
            cursor->next = new_node;
            counter++;
            if (counter == 20)
                free(new_node);
            
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