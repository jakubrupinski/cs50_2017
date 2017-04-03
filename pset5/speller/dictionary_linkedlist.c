/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

#define LONGEST_WORD (sizeof("pneumonoultramicroscopicsilicovolcanoconiosis"))

// defining linkedlist
typedef struct node
{
	char word[LONGEST_WORD];
	struct node *next;
} linkedlist;

// prototyping
linkedlist *create_list();
linkedlist *insert_word(linkedlist *list, char *word);
void destroy_list(linkedlist *list);
int count_words(linkedlist *list);
void print_words(linkedlist *list);

// create a global list for keeping words
linkedlist *head = NULL;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    linkedlist *trav = head;
    // copy const char to new variable (to lowercase it)
    char *low_case_word = malloc((strlen(word) + 1) * sizeof(char));
    strcpy(low_case_word, word);

    // convert word to lowercase
    for(int i = 0; word[i]; i++)
    {
    	low_case_word[i] = tolower(word[i]);
    }
    
    // if first word in dictionary is word - return true
    if(strcmp(trav->word, low_case_word) == 0)
    {
		free(low_case_word);
    	return true;
    }
    // if word is not first in dictionary - go further
    while(trav->next != NULL)
    {
    	if(strcmp(trav->word, low_case_word) == 0)
    	{
			free(low_case_word);
    		return true;
    	}
    	trav = trav->next;
    }
	
	free(low_case_word);    
	return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
	// create linkedlist variable
	linkedlist *word_list = create_list();
    // update head
    head = word_list;

	// open dictionary file
	FILE *filein = fopen(dictionary, "r");
	if (filein == NULL)
	{
		fprintf(stderr, "Could not open %s\n", dictionary);
		return false;
	}

	// read words into memory
	char *read_buffer = malloc(LONGEST_WORD * sizeof(char)); 
	if (read_buffer == NULL)
	{
		free(read_buffer);
		unload();
		return false;
	}
	while (fscanf(filein, "%s", read_buffer) != EOF)
	{
		// strcpy(head->word, read_buffer);
		insert_word(head, read_buffer);
	}
	
    // free memory allocs
    free(read_buffer);
    fclose(filein);

	// return true if loaded
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    int word_count = 0;
	linkedlist *trav = head;
	while(trav->next != NULL)
	{
		word_count++;
		trav = trav->next;
	}

	return word_count;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
	linkedlist *trav = head;
	// if there's nothing to unload return false
	if(trav == NULL)
		return false;

	destroy_list(head);
    return true;
}

/**
 * Creates a new linkedlist
 */
linkedlist *create_list()
{
	linkedlist *new_list = malloc(sizeof(linkedlist));
	if (new_list == NULL)
	{
		fprintf(stderr, "could not allocate memory for list\n");
		free(new_list);
		return NULL;
	}

	new_list->next = NULL;
	// update head of global list
	head = new_list;
	return new_list;
}

/**
 * Inserts new word from dictionary into linkedlist
 */
linkedlist *insert_word(linkedlist *list, char *word)
{
	linkedlist *new_word = malloc(sizeof(linkedlist));
	if (new_word == NULL)
	{
		fprintf(stderr, "could not allocate memory for %s\n", word);
		free(new_word);
		return NULL;
	}
	strcpy(new_word->word, word);
	new_word->next = list;

	// update global head
	head = new_word;

	return new_word;
}

void destroy_list(linkedlist *list)
{
	linkedlist *trav = list;
	if(trav->next != NULL)
	{
		destroy_list(trav->next);
	}
	free(trav);
}

void print_words(linkedlist *list)
{
	linkedlist *trav = list;
	while(trav->next != NULL)
	{
		printf("%s\n", trav->word);
		trav = trav->next;
	}
}