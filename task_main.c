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
    unsigned short pages2[] = {2, 7, 15, 20};
    unsigned short pages3[] = {3, 8};
    unsigned short pages4[] = {4};
    
    hash_table_insert_term(ht, "Programming", pages1, 3);
    hash_table_insert_term(ht, "Databases", pages2, 4);
    hash_table_insert_term(ht, "Networks", pages3, 2);
    hash_table_insert_term(ht, "Algorithms", pages4, 1);
    hash_table_insert_term(ht, "Programming", pages1, 3);
    
    hash_table_show(ht);
    
    hash_table_remove_term(ht, "Databases");
    hash_table_show(ht);
    
    hash_table_remove_term(ht, "AI");
    
    hash_table_free(ht);
    
    return 0;
}