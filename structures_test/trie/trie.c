#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "trie.h"

#define ALPHABET_LENGTH 27

typedef struct node
{
	bool is_word;
	struct node *children[ALPHABET_LENGTH];
} trie;

// prototyping
void init_trie(void);
void insert(char *word);
bool is_correct(char *word);
void print_trie(trie *head);
void destroy_trie(trie *curr_trie);

// global root
trie *root = NULL;

int main(void)
{
	init_trie();

	insert("elo");
	insert("elo's");
	insert("dls");
	insert("eldo");
	insert("bobo");
	insert("zez");
	
	printf("%s is in dictionary - %d\n", "Elo", is_correct("Elo"));
	printf("%s is in dictionary - %d\n", "elo's", is_correct("elo's"));
	printf("%s is in dictionary - %d\n", "ELO'", is_correct("ELO'"));
	printf("%s is in dictionary - %d\n", "dls", is_correct("dls"));
	printf("%s is in dictionary - %d\n", "eldo", is_correct("eldo"));
	printf("%s is in dictionary - %d\n", "eld", is_correct("eld"));
	printf("%s is in dictionary - %d\n", "vld", is_correct("vld"));

	destroy_trie(root);
	return 0;
}

void init_trie(void)
{
	root = malloc(sizeof(trie));
	root->is_word = false;
}

void insert(char *word)
{
	int word_len = strlen(word) + 1, curr_letter;
	trie *traversal = root;

	for (int i = 0; i < word_len; i++)
	{
		// convert current letter/apostrophe from ascii alphabet value (96-122) to array-like (0-26) value
		// if uppercase - calculate it for lowercase letter
		if (word[i] < 96)
			curr_letter = tolower(word[i]) % 97;
		else
			curr_letter = word[i] % 97;

		// if next letter node is empty - malloc it
		if (traversal->children[curr_letter] == NULL)
		{
			traversal->children[curr_letter] = malloc(sizeof(trie));
		}

		// travel to next letter in trie until end of word
		if (word[i] != '\0')
			traversal = traversal->children[curr_letter];
	}

	traversal->is_word = true;
}

bool is_correct(char *word)
{
	// variable for iterating through every letter of word, and a traversal pointer
	int word_len = strlen(word), curr_letter;
	trie *traversal = root;

	// go through every letter node for word until an empty node
	for (int i = 0; i < word_len; i++)
	{
		// current letter index in trie array, if uppercase - calculate it for lowercase letter
		if (word[i] < 96)
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

void destroy_trie(trie *curr_trie)
{
	trie *traversal = curr_trie;

	// search parent for non-null node
	for (int i = 0; i < ALPHABET_LENGTH; ++i)
	{
		// if found - search children for non-null node
		if (traversal->children[i] != NULL)
			destroy_trie(traversal->children[i]);
	}

	free(traversal);
}