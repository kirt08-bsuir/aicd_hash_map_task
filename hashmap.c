#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "hashmap.h"


typedef struct _hash_map_entry_t {
    char *key;
    long value;
} hash_map_entry_t;


struct _hash_map_t {
    hash_map_entry_t *entries;
    size_t size;
};


static size_t hash(const char *key) {
    if (key == NULL) {
        printf("Incorrect key value");
        return 0;
    }

    size_t hash = 0x12345678;
    for (const char *c = key; *c != '\0'; c++) {
        hash ^= *c;
        hash *= 0x5bd1e995;
        hash ^= hash >> 15;
    }

    return hash;
}

static hash_map_t* hash_map_expand(hash_map_t *map) {
    if (map == NULL) {
        printf("Can't allocate memory");
        return NULL;
    }

    hash_map_t *expended = hash_map_create(map->size * 2);

    for (size_t idx = 0; idx < map->size; idx++) {
        if (map->entries[idx].key != NULL) {
            expended = hash_map_insert(
                expended,
                map->entries[idx].key,
                map->entries[idx].value
            );
        }
    }

    hash_map_free(map);
    return expended;
}

hash_map_t* hash_map_create(size_t size) {
    hash_map_t *map = malloc(sizeof(hash_map_t));
    if (map == NULL) {
        printf("Can't allocate memory");
        return NULL;
    }

    map->size = size;

    map->entries = calloc(map->size, sizeof(hash_map_entry_t));
    if (map->entries == NULL) {
        printf("Can't allocate memory");
        return NULL;
    }

    return map;
}

hash_map_t* hash_map_insert(hash_map_t *map, const char *key, const long value) {
    if (map == NULL) {
        printf("Map doesn't exist");
        return NULL;
    }

    if (key == NULL) {
        printf("Incorrect key value");
        return NULL;
    }

    size_t idx = hash(key) % map->size;
    while (map->entries[idx].key != NULL) {
        idx += 1;

        if (idx == map->size) {
            return hash_map_insert(hash_map_expand(map), key, value);
        }
    }

    map->entries[idx].key = calloc(strlen(key) + 1, sizeof(char));
    if (map->entries[idx].key == NULL) {
        printf("Failed to allocate memory for new key");
        return NULL;
    }
    strcpy(map->entries[idx].key, key);

    map->entries[idx].value = value;

    return map;
}

bool hash_map_has_key(hash_map_t *map, const char *key) {
    if (map == NULL) {
        printf("Map doesn't exist");
        return false;
    }

    if (key == NULL) {
        printf("Incorrect key value");
        return false;
    }

    for (size_t idx = hash(key) % map->size; idx < map->size; idx++) {
        char *current = map->entries[idx].key;

        if (current == NULL) continue;

        if (!strcmp(current, key)) {
            return true;
        }
    }
    return false;
}

long hash_map_at(hash_map_t *map, const char *key) {
    if (map == NULL) {
        printf("Map doesn't exist");
        return 0;
    }

    if (key == NULL) {
        printf("Incorrect key value");
        return 0;
    }

    for (size_t idx = hash(key) % map->size; idx < map->size; idx++) {
        char *current = map->entries[idx].key;

        if (current == NULL) continue;
        if (!strcmp(current, key)) return map->entries[idx].value;
    }

    printf("Record with key %s wasn't found\n", key);
    return 0;
}

void hash_map_free(hash_map_t *map) {
    if (map == NULL) {
        printf("Map doesn't exist");
        return;
    }

    for (size_t idx = 0; idx < map->size; idx++) 
        if (map->entries[idx].key != NULL) free(map->entries[idx].key);
    
    free(map->entries);
    free(map);
}