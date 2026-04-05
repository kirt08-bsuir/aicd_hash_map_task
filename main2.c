#include <stdlib.h>
#include <stdio.h>

#include "linked_list.h"


int main(void) {
    Node *head = NULL;

    unsigned short p1[3] = {10, 20, 30};
    unsigned short p2[3] = {1, 2, 3};
    unsigned short p3[1] = {5};

    linked_list_append(&head, "hello", p1, 3);
    linked_list_append(&head, "hi", p2, 3);
    linked_list_append(&head, "bonguir", p3, 1);

    printf("Original list:\n");
    linked_list_show(head);

    linked_list_sort_by_name(&head);
    linked_list_show(head);

    linked_list_delete(&head, "hi");
    linked_list_show(head);

    linked_list_free(&head);
    return 0;
}