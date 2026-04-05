#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "task_term_index.h"


static unsigned int _hash_function(const char *str, int table_size) {
    unsigned int hash = 5381;
    int c;

    while ((c = *str++)) hash = ((hash << 5) + hash) + c;

    return hash % table_size;
}


HashTable *hash_table_create(int size) {

    HashTable *map = malloc(sizeof(HashTable));
    if (map == NULL) return NULL;

    map->entries = calloc(size, sizeof(Term*));
    if (map->entries == NULL) { free(map); return NULL; };

    map->size = size;
    return map;
}


static Term* create_term(const char *name, const unsigned short *pages, short pages_count) {
    Term *term = malloc(sizeof(Term));
    if (term == NULL) return NULL;

    term->name = malloc(strlen(name) + 1);
    if (term->name == NULL) { free(term); return NULL; };
    strcpy(term->name, name);

    term->pages = malloc(pages_count * sizeof(unsigned short));
    if (term->pages == NULL) { free(term->name); free(term); return NULL; };
    memcpy(term->pages, pages, pages_count * sizeof(unsigned short));
    
    term->pages_count = pages_count;
    term->sub_list = NULL;
    term->next = NULL;
    
    return term;
}

int hash_table_insert_term(HashTable *map, const char *name, const unsigned short *pages, short pages_count) {
    if (map == NULL) return -1;

    unsigned int index = _hash_function(name, map->size);

    Term *current = map->entries[index];
    while (current) {
        if (strcmp(name, current->name) == 0) {
            printf("Such termin already exists\n");
            return -1;
        }
        current = current->next;
    }

    Term *new_termin = create_term(name, pages, pages_count);
    if (new_termin == NULL) return -1;

    new_termin->next = map->entries[index];
    map->entries[index] = new_termin;

    printf("Termin %s appended\n", name);
    return 0;
}

static void free_subsub_list(SubSubTerm *head) {
    SubSubTerm *current = head;
    while (current) {
        SubSubTerm *next = current->next;
        free(current->name);
        if (current->pages) free(current->pages);
        free(current);
        current = next;
    }
}

static void free_sub_list(SubTerm *head) {
    SubTerm *current = head;
    while (current) {
        SubTerm *next = current->next;
        free(current->name);
        if (current->pages) free(current->pages);
        free_subsub_list(current->subsub_list);
        free(current);
        current = next;
    }
}

static void free_term(Term *term) {
    if (!term) return;
    free(term->name);
    if (term->pages) free(term->pages);
    free_sub_list(term->sub_list);
    free(term);
}

int hash_table_remove_term(HashTable *map, const char *name) {
    if (map == NULL) return -1;

    unsigned int index = _hash_function(name, map->size);

    Term *prev = NULL;
    Term *cur = map->entries[index];

    while (cur) {
        if (strcmp(cur->name, name) == 0) {
            if (prev) prev->next = cur->next; else map->entries[index] = cur->next;

            printf("Termin %s was successfully deleted\n", name);
            free_term(cur);
            return 0;
        }
        prev = cur;
        cur = cur->next;
    }

    printf("Error: term '%s' wasn't found\n", name);
    return -1;
}

void hash_table_show(HashTable *map) {
    if (!map) {
        printf("Wasn't initialized\n");
        return;
    }
    
    printf("\n=== Hash Table ===\n");
    int term_count = 0;
    
    for (int i = 0; i < map->size; i++) {
        Term *cur = map->entries[i];
        if (cur) {
            printf("\n[%d] ", i);
            while (cur) {
                printf("'%s' (page: ", cur->name);
                for (int j = 0; j < cur->pages_count; j++) {
                    printf("%d", cur->pages[j]);
                    if (j < cur->pages_count - 1) printf(", ");
                }
                printf(")");
                if (cur->next) printf(" -> ");
                cur = cur->next;
                term_count++;
            }
            printf("\n");
        }
    }
    
    if (term_count == 0) {
        printf("Hash table empty\n");
    } else {
        printf("\nNumber of terms: %d\n", term_count);
    }
    printf("================================\n");
}

void hash_table_free(HashTable *map) {
    if (map == NULL) return;

    for (int i = 0; i < map->size; i++) {
        Term *cur = map->entries[i];
        while (cur) {
            Term *next = cur->next;
            free_term(cur);
            cur = next;
        }
    }

    free(map->entries);
    free(map);
    printf("Memory fully freed\n");
}