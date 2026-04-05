#include <stdio.h>
#include "hashmap.h"

int main(void) {
    hash_map_t *map = hash_map_create(1);
    const char *keys[4] = {
        "hello",
        "this",
        "wonderful",
        "world",
    };

    for (long idx = 0; idx < 4; idx++) {
        map = hash_map_insert(map, keys[idx], idx);
    }

    for (long idx = 0; idx < 4; idx++) {
        printf("map[\"%s\"] = %ld\n", keys[idx], hash_map_at(map, keys[idx]));
    }

    hash_map_free(map);
    return 0;
}