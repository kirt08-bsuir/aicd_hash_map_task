#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"


typedef struct _Node {
    char *name;
    unsigned short *pages;
    size_t pages_count;
    struct _Node *next;
} Node;


void linked_list_append(Node **head, const char *name, const unsigned short *pages, size_t pages_count) {
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) return;

    new_node->name = malloc(strlen(name) + 1);
    if (new_node->name == NULL) {
        free(new_node);
        return;
    }
    strcpy(new_node->name, name);

    new_node->pages = malloc(pages_count * sizeof(unsigned short));
    if (new_node->pages == NULL) {
        free(new_node->name);
        free(new_node);
        return;
    }
    memcpy(new_node->pages, pages, pages_count * sizeof(unsigned short));

    new_node->pages_count = pages_count;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        Node *cur = *head;
        while (cur->next != NULL) cur = cur->next;

        cur->next = new_node;
    }
}

void linked_list_delete(Node **head, const char *name) {
    Node *cur = *head;
    Node *prev = NULL;

    while (cur) {
        if (!strcmp(cur->name, name)) {
            if (prev) prev->next = cur->next; else *head = cur->next;

            free(cur->name);
            free(cur->pages);
            free(cur);
            return;
        }

        prev = cur;
        cur = cur->next;
    }
}

void linked_list_sort_by_name(Node **head) {
    if (*head == NULL) return;

    int swapped;

    do {
        swapped = 0;
        Node *cur = *head;

        while (cur->next) {
            if (strcmp(cur->name, cur->next->name) > 0) {
                char *temp_name = cur->name;
                cur->name = cur->next->name;
                cur->next->name = temp_name;

                unsigned short *temp_pages = cur->pages;
                cur->pages = cur->next->pages;
                cur->next->pages = temp_pages;

                size_t temp_count = cur->pages_count;
                cur->pages_count = cur->next->pages_count;
                cur->next->pages_count = temp_count;

                swapped = 1;
            }
            cur = cur->next;
        }
    } while (swapped);
}

void linked_list_show(const Node *head) {
    while (head) {
        printf("Name %s\n", head->name);
        printf("Pages: ");
        for (size_t i = 0; i < head->pages_count; i++) printf("%hu", head->pages[i]);
        printf("\n\n");
        head = head->next;
    }
}

void linked_list_free(Node **head) {
    Node *cur = *head;
    
    while (cur) {
        Node *next = cur->next;
        free(cur->name);
        free(cur->pages);
        free(cur);
        cur = next;
    }
    *head = NULL;
}