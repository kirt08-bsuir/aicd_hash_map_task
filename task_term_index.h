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


// ADD
int hash_table_insert_term(HashTable *map, const char *name, const unsigned short *pages, short pages_count);
int hash_table_insert_sub_term(
    HashTable *map,
    const char *term_name,
    const char *name,
    const unsigned short *pages,
    short pages_count
);
int hash_table_insert_sub_sub_term(
    HashTable *map,
    const char *term_name,
    const char *sub_term_name,
    const char *name,
    const unsigned short *pages,
    short pages_count
);


// REMOVE
int hash_table_remove_term(HashTable *map, const char *name);
int hash_table_remove_sub_term(
    HashTable *map,
    const char *term_name,
    const char *name
);
int hash_table_remove_sub_sub_term(
    HashTable *map,
    const char *term_name,
    const char *sub_term_name,
    const char *name
);


// EDIT
int hash_table_edit_term(
    HashTable *map,
    const char *term_name,
    const unsigned short *new_pages,
    short new_pages_count
);
int hash_table_edit_sub_term(
    HashTable *map,
    const char *term_name,
    const char *sub_term_name,
    const unsigned short *new_pages,
    short new_pages_count
);
int hash_table_edit_sub_sub_term(
    HashTable *map,
    const char *term_name,
    const char *sub_term_name,
    const char *sub_sub_term_name,
    const unsigned short *new_pages,
    short new_pages_count
);


// FIND
int hash_table_find_term_by_sub_term(
    HashTable *map,
    const char *sub_term_name
);
int hash_table_find_sub_term_by_term(
    HashTable *map,
    const char *term_name
);


void hash_table_show(HashTable *map);
void hash_table_free(HashTable *map);

#endif