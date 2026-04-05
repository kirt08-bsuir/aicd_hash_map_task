#include <stdio.h>
#include "task_term_index.h"

int main(void) {
    printf("=== Term Index System ===\n\n");
    
    HashTable *ht = hash_table_create(20);
    if (!ht) {
        printf("Failed to create hash table\n");
        return 1;
    }
    
    unsigned short pages1[] = {1, 5, 10};
    unsigned short pages2[] = {2, 7};
    unsigned short pages3[] = {3, 8, 12};
    
    hash_table_insert_term(ht, "Programming", pages1, 3);
    hash_table_insert_term(ht, "Databases", pages2, 2);
    hash_table_insert_term(ht, "Networks", pages3, 3);
    
    unsigned short sub_pages1[] = {5, 6};
    unsigned short sub_pages2[] = {7};
    unsigned short sub_pages3[] = {8, 9, 10};
    
    hash_table_insert_sub_term(ht, "Programming", "Algorithms", sub_pages1, 2);
    hash_table_insert_sub_term(ht, "Programming", "Data Structures", sub_pages2, 1);
    hash_table_insert_sub_term(ht, "Databases", "SQL", sub_pages3, 3);
    
    unsigned short subsub_pages1[] = {10};
    unsigned short subsub_pages2[] = {11, 12};
    
    hash_table_insert_sub_sub_term(ht, "Programming", "Algorithms", "Sorting", subsub_pages1, 1);
    hash_table_insert_sub_sub_term(ht, "Programming", "Algorithms", "Searching", subsub_pages2, 2);
    hash_table_insert_sub_sub_term(ht, "Databases", "SQL", "SELECT", subsub_pages1, 1);
    
    unsigned short subsub_pages3[] = {1, 2, 3};
    hash_table_insert_sub_sub_term(ht, "Programming", "Data Structures", "bla-bla-bla", subsub_pages3, 3);

    hash_table_show(ht);
    
    hash_table_free(ht);
    
    return 0;
}