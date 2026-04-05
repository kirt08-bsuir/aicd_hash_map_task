#ifndef TERM_INDEX_H
#define TERM_INDEX_H


typedef struct SubSubTerm {
    char *name;
    unsigned short *pages;
    short pages_count;
    struct SubSubTerm *next;
} SubSubTerm;

typedef struct SubTerm {
    char *name;
    unsigned short *pages;
    short pages_count;
    SubSubTerm *subsub_list;
    struct SubTerm *next;
} SubTerm;

typedef struct Term {
    char *name;
    unsigned short *pages;
    short pages_count;
    SubTerm *sub_list;
    struct Term *next;
} Term;

typedef struct HashTable {
    Term **entries;
    int size;
} HashTable;


HashTable *hash_table_create(int size);
int hash_table_insert_term(HashTable *map, const char *name, const unsigned short *pages, short pages_count);
int hash_table_remove_term(HashTable *map, const char *name);
void hash_table_show(HashTable *map);
void hash_table_free(HashTable *map);

#endif