#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>

typedef struct _Node Node;

void linked_list_append(Node **head, const char *name, const unsigned short *pages, size_t pages_count);
void linked_list_delete(Node **head, const char *name);
void linked_list_sort_by_name(Node **head);
void linked_list_show(const Node *head);
void linked_list_free(Node **head);

#endif