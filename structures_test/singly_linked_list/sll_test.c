#include "sll_test.h"

int main(void)
{
    // create list
    sllnode *list1 = create(10);

    // insert new node
    list1 = insert(list1, 10);
    list1 = insert(list1, 20);
    list1 = insert(list1, 30);
    list1 = insert(list1, 40);
    list1 = insert(list1, 50);
    list1 = insert(list1, 60);


    // search list for value
    find(list1, 10);
    find(list1, 15);
    find(list1, 20);
    find(list1, 40);
    find(list1, 60);

    // destroy list and free memory
    destroy(list1);

    return 0;
}
