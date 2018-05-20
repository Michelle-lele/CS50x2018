// Implements a dictionary's functionality

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "dictionary.h"

#define HT_MAX_SIZE 300000

node *hashtable[HT_MAX_SIZE];

int count = 0;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //open dictionary
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        fprintf(stderr, "%s cannot be open.", dictionary);
        count = 0;
        return false;
    }

    //read word from file
    char word[(LENGTH + 1)];

    //int collisions = 0;
    //create new linked list and add node to hashtable index
    while (fscanf(dict, "%s", word) != EOF)
    {
        unsigned long index = hash((unsigned char *)word) % HT_MAX_SIZE; //hash the word to get index
        //add node to existing linked list in that hashtable index
        if (hashtable[index] == NULL)
        {
            node *llnode = malloc(sizeof(node));
            if (llnode == NULL)
            {
                fprintf(stderr, "Out of memory!2");
                count = 0;
                unload();
                return false;
            }
            llnode->word = malloc(sizeof(char) * (strlen(word) + 1));
            if (llnode->word == NULL)
            {
                fprintf(stderr, "Out of memory!3");
                count = 0;
                unload();
                return false;
            }
            strcpy(llnode->word, word);
            llnode->next = NULL;
            hashtable[index] = (void *)(llnode);
        }
        //add node to existing linked list
        else
        {
            node *llnode = malloc(sizeof(node));
            if (llnode == NULL)
            {
                fprintf(stderr, "Out of memory!4");
                count = 0;
                unload();
                return false;
            }
            llnode->word = malloc(sizeof(char) * (strlen(word) + 1));
            if (llnode->word == NULL)
            {
                fprintf(stderr, "Out of memory!5");
                count = 0;
                unload();
                return false;
            }
            strcpy(llnode->word, word);
            llnode->next = hashtable[index];
            hashtable[index] = (void *)(llnode);
            //collisions++;
        }
        count++;
    }
    //printf("collisions %i\n", collisions);

    //close dictionary
    fclose(dict);
    //free(word); // 2/0 bytes inside a block of size 46 free'd
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (count > 0)
    {
        return count;
    }
    else
    {
        return 0;
    }
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //hash the word
    char *word_buffer = malloc((sizeof(char) * (LENGTH + 1)));
    strcpy(word_buffer, word);
    //printf("Word buffer: %s\n", word_buffer);
    unsigned char *u_word = (unsigned char *)word_buffer;
    //by J.F. Sebastian, https://stackoverflow.com/questions/2661766/c-convert-a-mixed-case-string-to-all-lower-case
    for (unsigned char *ptr = u_word; *ptr; ++ptr)
    {
        *ptr = tolower(*ptr);
    }

    unsigned long i = (hash(u_word) % HT_MAX_SIZE);
    //checking if there is such index in hastable, if not word is not in dictionary
    if (hashtable[i] != NULL)
    {
        //check if word matches any existing word in the linked list at that index
        node *head = hashtable[i];
        do
        {
            if (strcmp(head->word, word_buffer) == 0)
            {
                free(word_buffer);
                return true;
            }
            else
            {
                head = head->next;
            }
        }
        while (head != NULL);
    }

    //if word not found in linked list for that index, it is mispelled
    free(word_buffer);
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < HT_MAX_SIZE; i++)
    {
        if (hashtable[i] != NULL)
        {
            node *head = hashtable[i];
            //printf("HT: %p\n", hashtable[i]);
            node *cursor = NULL;
            do
            {
                cursor = head->next;
                free(head->word);
                free(head);
                head = cursor;
            }
            while (head != NULL);
        }
    }
    return true;
}

//djb2, dan bernstein's hash
unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c = 0;

    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c;     /* hash * 33 + c */
    }
    return hash;
}
