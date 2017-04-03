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
#define HASH_SIZE 26

// defining hash_table
typedef struct hash_tab_elem
{
	char word[LONGEST_WORD];
	struct hash_tab_elem *next;
} hash_table;

// prototyping
void init_hashtable();
void insert_word(hash_table *table, char *word);
bool destroy_hash_table(hash_table *table);
bool check_single_index(hash_table *table, char *word);
int count_words_single_index(hash_table *table);
unsigned long hash(const char *str);

// create a global hash table for keeping words
hash_table *hashtabe_array[HASH_SIZE];

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // copy const char to new variable (to lowercase it)
    char *low_case_word = malloc((strlen(word) + 1) * sizeof(char));
    strcpy(low_case_word, word);

    // convert word to lowercase
	for(int i = 0; i < strlen(word); i++)
    {
    	low_case_word[i] = tolower(word[i]);
    }
	//check hash index of current word
	int hash_index = hash(low_case_word);

	return check_single_index(hashtabe_array[hash_index], low_case_word);
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
	// create hash_table variable
	init_hashtable();

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
		// get hash index
		int index = hash(read_buffer);
		insert_word(hashtabe_array[index], read_buffer);
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
    int size = 0;
	
	for (int i = 0; i < HASH_SIZE; i++)
	{
		size += count_words_single_index(hashtabe_array[i]);
	}

	return size;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload()
{
	for (int i = 0; i < HASH_SIZE; i++)
	{
		if (!destroy_hash_table(hashtabe_array[i]))
	    	return false;
	}

	return true;
}

/**
 * Creates a new hash_table
 */
void init_hashtable()
{
	// iterate over every index of hash table
	for(int i = 0; i < HASH_SIZE; i++)
	{
		hashtabe_array[i] = malloc(sizeof(hash_table));
		// check for memory allocation problems
		if (hashtabe_array[i] == NULL)
		{
			fprintf(stderr, "could not allocate memory for hash table\n");
			free(hashtabe_array);
			return;
		}
		// change next pointer to NULL, just in case compiler doesn't do it itself
		hashtabe_array[i]->next = NULL;
	}
}

/**
 * Inserts new word from dictionary into hash_table
 */
void insert_word(hash_table *table, char *word)
{
	// temp pointer to travel, points to beginning of table
	hash_table *trav = table;

	hash_table *word_node = malloc(sizeof(hash_table));
	if (word_node == NULL)
	{
		fprintf(stderr, "could not allocate memory for %s\n", word);
		unload();
		return;
	}
	strcpy(word_node->word, word);

	// if hashtable index points to a node already - keep it in new word_node->next pointer
	if (table->next != NULL)
		word_node->next = trav->next;
	// point hashtable index to new word_node
	table->next = word_node;
}

bool destroy_hash_table(hash_table *table)
{
	bool success = false;
	hash_table *trav = table;
	if(trav->next != NULL)
	{
		destroy_hash_table(trav->next);
	}
	free(trav);
	// if everything worked fine
	success = true;
	return success;
}

unsigned long hash(const char *str)
{
    unsigned long hash = 5381;
    int c = 0;

    while (c == *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

int count_words_single_index(hash_table *table)
{
    int word_count = 0;
	hash_table *trav = table;
	while(trav->next != NULL)
	{
		word_count++;
		trav = trav->next;
	}

	return word_count;
}

bool check_single_index(hash_table *table, char *low_case_word)
{
	// create a temporary pointer for traveling across nodes
    hash_table *trav = table;

    // if word is not first in dictionary - go further
    while(trav != NULL)
    {
    	// if current node includes word - return true
    	if(strcmp(trav->word, low_case_word) == 0)
    	{
			free(low_case_word);
    		return true;
    	}

    	// go to next node
    	trav = trav->next;    	
    }
	
	free(low_case_word);    
	return false;
}