#ifndef HASH_TABLE
#define HASH_TABLE

#include "list.h"

const int TABLE_SIZE = 25000;
const int WORD_NUM   = 370105;

struct hash_table_t {
        int (*hash)(char *);
        list_t *table[TABLE_SIZE] = {};
};

// Insert data.
void
hash_insert(list_t *table, char *key, char *data);
// Find data.
const char *
hash_search(list_t *table, char *key);

#endif // HASH_TABLE

