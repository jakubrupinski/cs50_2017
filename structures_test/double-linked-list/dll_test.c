#include <stdio.h>

#include "dll_test.h"

int main(void)
{
    // create new doubly-linked list
    dll_node *dll_list_1 = create_dll(10);

    // insert new nodes
    dll_list_1 = insert(dll_list_1, 22);
    dll_list_1 = insert(dll_list_1, 20);
    dll_list_1 = insert(dll_list_1, 30);
    dll_list_1 = insert(dll_list_1, 40);
    dll_list_1 = insert(dll_list_1, 50);
    dll_list_1 = insert(dll_list_1, 60);
    dll_list_1 = insert(dll_list_1, 70);

    // remove single nodes
    remove_node(&dll_list_1, 70);
    remove_node(&dll_list_1, 10);
    remove_node(&dll_list_1, 40);


    printf("current head: \n");
    printf("n = %d\nprev = %p\nnext = %p\n", dll_list_1->n, dll_list_1->prev, dll_list_1->next);

    // search for values
    search(dll_list_1, 10);
    search(dll_list_1, 22);
    search(dll_list_1, 50);
    search(dll_list_1, 40);
    search(dll_list_1, 55);
    search(dll_list_1, 70);

    // destroy whole tree
    destroy(dll_list_1);
    printf("deleted list!\n");
}
