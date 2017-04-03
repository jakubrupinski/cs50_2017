#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 10

// define hash_table
typedef struct hash_tab_elem
{
    char *string;
    struct hash_tab_elem *prev;
    struct hash_tab_elem *next;
} hash_table;

// prototyping
void insert(char *value);
int hash(char *string);
void print_values(hash_table *table);
void init_hashtable();

// global variable with pointer to head of list
hash_table *hashtable[HASH_SIZE];

int main(void)
{
    init_hashtable();
    insert("Joey");
    insert("Elo");
    insert("Dziony");
    insert("Roman");
    insert("Romanthony");
    insert("ziomek");
    insert("euhe");
    insert("a");
    insert("ziomek12");
    insert("ahaha");
    insert("CHUJU");

    // print whole hashtable
    for (int i = 0; i < HASH_SIZE; ++i)
    {
        print_values(hashtable[i]);
    }

    return 0;
}

int hash(char *string)
{
    int index = 0;

    for(int i = 0; string[i] != '\0'; i++)
    {
        index += string[i];
    }

    return index % HASH_SIZE;
}


void insert(char *value)
{
    // allocate memory for new node
    hash_table *new_node = malloc(sizeof(hash_table));
    if (new_node == NULL)
    {
        free(new_node);
        fprintf(stderr, "could not allocate memory for insertion of \"%s\"\n", value);
        exit(1);
    }

    // get hash value for hashtable index
    int index = hash(value);

    // assign values to new node of hash table
    new_node->string = value;
    new_node->prev = hashtable[index];
    // if there is a node in index already - chain it to new node
    if (hashtable[index]->next != NULL)
    {
        new_node->next = hashtable[index]->next;
        hashtable[index]->next = new_node;
    }

    // append it to hash table
    hashtable[index]->next = new_node;
}

void print_values(hash_table *table)
{
    hash_table *traversal = table;   
    // if table index is empty - return
    if (traversal == NULL)
        return;

    if (traversal->next != NULL)
        print_values(traversal->next);
    
    // if string isn't null print it
    if (traversal->string != NULL)
        printf("%s\n", traversal->string);
}

void init_hashtable()
{
    // iterate over every index of hash table
    for(int i = 0; i < HASH_SIZE; i++)
    {
        hashtable[i] = malloc(sizeof(hash_table));
        // check for memory allocation problems
        if (hashtable[i] == NULL)
        {
            fprintf(stderr, "could not allocate memory for hash table\n");
            free(hashtable[i]);
            return;
        }
        // change next pointer to NULL, just in case compiler doesn't do it itself
        hashtable[i]->next = NULL;
    }
}