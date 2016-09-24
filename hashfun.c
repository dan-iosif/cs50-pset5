#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <cs50.h>

unsigned long hash(unsigned char *str);

void *data[] = { "alpha", "bravo", "charlie", "delta",
            "echo", "foxtrot", "golf", "hotel", "india", "juliet",
            "kilo", "lima", "mike", "november", "oscar", "papa",
            "quebec", "romeo", "sierra", "tango", "uniform",
            "victor", "whisky", "x-ray", "yankee", "zulu"
       };


int main(void)
{
    int i;
    for(i=0; i < 25; i++)
    printf("The string: %s  and the hash %lu \n", data[i], hash(data[i]));
}

unsigned long hash(unsigned char *str)
    {
        unsigned long hash = 5381;
        int c;

        while ((c = *str++))
        {
           
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
            
        }
        return hash;
    }