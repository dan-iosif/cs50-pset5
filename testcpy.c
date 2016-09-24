/**
 * Cannot figure out why I get segfault when I strcpy 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>

typedef struct node
{
    char word[51];
    struct node* next;
}
node;

int main(void)
{
    node* hashtable[5];
    for(int i=0; i<5;i++)
    {
        hashtable[i] = malloc(sizeof(node));
        strcpy(hashtable[i]->word,"cos");
    } 
}