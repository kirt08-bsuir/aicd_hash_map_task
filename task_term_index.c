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

static SubTerm* create_sub_term(const char *name, const unsigned short *pages, short pages_count) {
    SubTerm *sub_term = malloc(sizeof(SubTerm));
    if (sub_term == NULL) return NULL;

    sub_term->name = malloc(strlen(name) + 1);
    if (sub_term->name == NULL) { free(sub_term); return NULL; };
    strcpy(sub_term->name, name);

    sub_term->pages = malloc(pages_count * sizeof(unsigned short));
    if (sub_term->pages == NULL) { free(sub_term->name); free(sub_term); return NULL; };
    memcpy(sub_term->pages, pages, pages_count * sizeof(unsigned short));

    sub_term->pages_count = pages_count;
    sub_term->subsub_list = NULL;
    sub_term->next = NULL;
    
    return sub_term;
}

static SubSubTerm* create_sub_sub_term(const char *name, const unsigned short *pages, short pages_count) {
    SubSubTerm *sub_sub_term = malloc(sizeof(SubSubTerm));
    if (sub_sub_term == NULL) return NULL;

    sub_sub_term->name = malloc(strlen(name) + 1);
    if (sub_sub_term->name == NULL) { free(sub_sub_term); return NULL; };
    strcpy(sub_sub_term->name, name);

    sub_sub_term->pages = malloc(pages_count * sizeof(unsigned short));
    if (sub_sub_term->pages == NULL) { free(sub_sub_term->name); free(sub_sub_term); return NULL; };
    memcpy(sub_sub_term->pages, pages, pages_count * sizeof(unsigned short));

    sub_sub_term->pages_count = pages_count;
    sub_sub_term->next = NULL;
    
    return sub_sub_term;
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

int hash_table_insert_sub_term(
    HashTable *map,
    const char *term_name,
    const char *name,
    const unsigned short *pages,
    short pages_count
) {
    if (map == NULL) return -1;

    unsigned int index = _hash_function(term_name, map->size);
    Term *term = map->entries[index];

    while (term) {
        if (strcmp(term->name, term_name) == 0) break;
        term = term->next;
    }

    if (term == NULL) {
        printf("Error: term '%s' not found\n", term_name);
        return -1;
    }

    SubTerm *cur = term->sub_list;
    while (cur) {
        if (strcmp(cur->name, name) == 0) {
            printf("Error: subterm '%s' already exists in term '%s'\n", name, term_name);
            return -1;
        }
        cur = cur->next;
    }

    SubTerm *new_term = create_sub_term(name, pages, pages_count);
    if (new_term == NULL) return -1;

    new_term->next = term->sub_list;
    term->sub_list = new_term;

    printf("Subterm '%s' added to term '%s'\n", name, term_name);
    return 0;
}

int hash_table_insert_sub_sub_term(
    HashTable *map,
    const char *term_name,
    const char *sub_term_name,
    const char *name,
    const unsigned short *pages,
    short pages_count
) {
    if (map == NULL) return -1;

    unsigned int index = _hash_function(term_name, map->size);
    Term *term = map->entries[index];
    
    while (term) {
        if (strcmp(term->name, term_name) == 0) {
            break;
        }
        term = term->next;
    }
    
    if (term == NULL) {
        printf("Error: term '%s' not found\n", term_name);
        return -1;
    }
    
    SubTerm *sub = term->sub_list;
    while (sub) {
        if (strcmp(sub->name, sub_term_name) == 0) {
            break;
        }
        sub = sub->next;
    }
    
    if (sub == NULL) {
        printf("Error: subterm '%s' not found in term '%s'\n", sub_term_name, term_name);
        return -1;
    }
    
    SubSubTerm *current = sub->subsub_list;
    while (current) {
        if (strcmp(current->name, name) == 0) {
            printf("Error: subsubterm '%s' already exists\n", name);
            return -1;
        }
        current = current->next;
    }

    SubSubTerm *new_sub_sub_term = create_sub_sub_term(name, pages, pages_count);
    if (new_sub_sub_term == NULL) return -1;

    new_sub_sub_term->next = sub->subsub_list;
    sub->subsub_list = new_sub_sub_term;

    printf("Subsubterm '%s' added to subterm '%s'\n", name, sub_term_name);
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
        printf("Hash table not initialized\n");
        return;
    }
    
    printf("\n========================================\n");
    printf("           TERM INDEX\n");
    printf("========================================\n");
    
    int term_count = 0;
    int sub_count = 0;
    int subsub_count = 0;
    
    Term **all_terms = malloc(map->size * sizeof(Term*));
    int total_terms = 0;
    
    for (int i = 0; i < map->size; i++) {
        Term *cur = map->entries[i];
        while (cur) {
            all_terms[total_terms++] = cur;
            cur = cur->next;
        }
    }
    
    for (int i = 0; i < total_terms - 1; i++) {
        for (int j = 0; j < total_terms - i - 1; j++) {
            if (strcmp(all_terms[j]->name, all_terms[j+1]->name) > 0) {
                Term *temp = all_terms[j];
                all_terms[j] = all_terms[j+1];
                all_terms[j+1] = temp;
            }
        }
    }
    
    for (int i = 0; i < total_terms; i++) {
        Term *term = all_terms[i];
        term_count++;
        
        printf("\n[%d] TERM: %s", term_count, term->name);
        printf(" [pages: ");
        for (int j = 0; j < term->pages_count; j++) {
            printf("%d", term->pages[j]);
            if (j < term->pages_count - 1) printf(", ");
        }
        printf("]\n");
        
        SubTerm *sub = term->sub_list;
        int sub_idx = 0;
        while (sub) {
            sub_count++;
            sub_idx++;
            printf("    %d.%d SUBTERM: %s", term_count, sub_idx, sub->name);
            printf(" [pages: ");
            for (int j = 0; j < sub->pages_count; j++) {
                printf("%d", sub->pages[j]);
                if (j < sub->pages_count - 1) printf(", ");
            }
            printf("]\n");
            
            SubSubTerm *subsub = sub->subsub_list;
            int subsub_idx = 0;
            while (subsub) {
                subsub_count++;
                subsub_idx++;
                printf("        %d.%d.%d SUBSUBTERM: %s", term_count, sub_idx, subsub_idx, subsub->name);
                printf(" [pages: ");
                for (int j = 0; j < subsub->pages_count; j++) {
                    printf("%d", subsub->pages[j]);
                    if (j < subsub->pages_count - 1) printf(", ");
                }
                printf("]\n");
                
                subsub = subsub->next;
            }
            
            sub = sub->next;
        }
    }
    
    printf("\n========================================\n");
    printf("STATISTICS:\n");
    printf("  Terms: %d\n", term_count);
    printf("  Subterms: %d\n", sub_count);
    printf("  Subsubterms: %d\n", subsub_count);
    printf("========================================\n");
    
    free(all_terms);
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