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
#define ALPHABET_LENGTH 27

// defining trie
typedef struct node
{
	bool is_word;
	struct node *children[ALPHABET_LENGTH];
} trie;

// prototyping
void init_trie(void);
trie *create_node(void);
void insert_word(char *word);
bool destroy_trie(trie *curr_trie);
int count_words_trie(trie *curr_trie);

// create a global root
trie *root = NULL;
// global word count
int word_count = 0;
int insert_count = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
	// variable for iterating through every letter of word, and a traversal pointer
	int word_len = strlen(word), curr_letter;
	trie *traversal = root;

	// go through every letter node for word until an empty node
	for (int i = 0; i < word_len; i++)
	{
		// convert current letter from ascii alphabet value (96-122) to array-like (0-26) value
		// if apostrohpe - put it in last index
		if (word[i] == 39)
			curr_letter = ALPHABET_LENGTH - 1;
		// if uppercase - calculate it for lowercase letter
		else if (word[i] < 96)
			curr_letter = tolower(word[i]) % 97;
		else
			curr_letter = word[i] % 97;

		// if next letter's node is null - word is misspelled, else go to next node
		if (traversal->children[curr_letter] == NULL)
			return false;
		else
			traversal = traversal->children[curr_letter];
	}

	if (traversal->is_word)
		return true;
	else
		return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
	// create trie variable
	init_trie();

	// open dictionary file
	FILE *filein = fopen(dictionary, "r");
	if (filein == NULL)
	{
		fprintf(stderr, "Could not open %s\n", dictionary);
		return false;
	}

	// read words into memory
	char *read_buffer = malloc(LONGEST_WORD * sizeof(char));
	// error check
	if (read_buffer == NULL)
	{
		free(read_buffer);
		unload();
		return false;
	}

	while (fscanf(filein, "%s", read_buffer) != EOF)
	{
		insert_word(read_buffer);
		insert_count++;
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
/*    int size = 0;
	size += count_words_trie(root);
	printf("loaded words: %d\n", insert_count); */
	return insert_count;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload()
{
	if (!destroy_trie(root))
    	return false;
    else
		return true;
}

/**
 * Creates a new trie
 */
void init_trie(void)
{
	root = create_node();
}

/**
 * Inserts new word from dictionary into trie
 */
void insert_word(char *word)
{
	int word_len = strlen(word) + 1, curr_letter;
	trie *traversal = root;

	for (int i = 0; i < word_len; i++)
	{
		// convert current letter from ascii alphabet value (96-122) to array-like (0-26) value
		// if apostrohpe - put it in last index
		if (word[i] == 39)
			curr_letter = ALPHABET_LENGTH - 1;
		// if uppercase - calculate it for lowercase letter
		else if (word[i] < 96)
			curr_letter = tolower(word[i]) % 97;
		else
			curr_letter = word[i] % 97;

		// if next letter node is empty - create/malloc it
		if (traversal->children[curr_letter] == NULL)
			traversal->children[curr_letter] = create_node();

		// travel to next letter in trie until end of word
		if (word[i] != '\0')
			traversal = traversal->children[curr_letter];
	}

	traversal->is_word = true;
}

bool destroy_trie(trie *curr_trie)
{
	bool success = false;
	trie *traversal = curr_trie;

	// search parent for non-null node
	for (int i = 0; i < ALPHABET_LENGTH; ++i)
	{
		// if found - search children for non-null node
		if (traversal->children[i] != NULL)
			destroy_trie(traversal->children[i]);
	}

	free(traversal);
	success = true;
	return success;
}

/**
 * Count total words in trie
 */
int count_words_trie(trie *curr_trie)
{
	trie *traversal = curr_trie;

	// search parent for non-null node
	for (int i = 0; i < ALPHABET_LENGTH; ++i)
	{
		// if found - search children for non-null node
		if (traversal->children[i] != NULL)
			count_words_trie(traversal->children[i]);
	}

	if (traversal->is_word == true)
		word_count++;

	return word_count;
}

/**
 * Creates and allocates memory for new node of Trie
 */ 
trie *create_node(void)
{
	// allocate memory for new_node
	trie *new_node = malloc(sizeof(trie));
	if (new_node == NULL)
	{
		fprintf(stderr, "Could not allocate memory for new node, exiting...\n");
		free(new_node);
		unload();
		exit(1);
	}
	// initialize bool variable
	new_node->is_word = false;

	// initialize every children node to NULL
	for (int i = 0; i < ALPHABET_LENGTH; i++)
		new_node->children[i] = NULL;

	return new_node;
}