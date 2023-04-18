#ifndef HASH_TABLE
#define HASH_TABLE

#include "list.h"

enum hash_err_t {
        HSH_NO_ERR = 0,
        HSH_ALLOC  = 1,
        HSH_LIST   = 2,
};

const int TABLE_SIZE = 25000;
const int WORD_NUM   = 370105;

struct hash_table_t {
        unsigned int (*hash)(const char *) = nullptr;
        list_t *table = nullptr;
};

// Different hash functions.
unsigned int
hash_one(const char *key);
unsigned int
hash_first_ascii(const char *key);
unsigned int
hash_len(const char *key);
unsigned int
hash_sum_ascii(const char *key);
unsigned int
hash_rol(const char *key);
unsigned int
hash_ror(const char *key);
unsigned int
hash_crc32(const char *key);
// Construct hash-table.
int
hash_ctor(hash_table_t *ht, unsigned int (*hash)(const char *key));
// Fill hash-table with array of data 'arr'.
void
hash_fill(hash_table_t *ht, char *buffer, int size);
// Creates an array with number of elements in i-th list.
int *
hash_make_data(hash_table_t *ht);
// Make test of specific hash function using 'arr' as data.
int
hash_test(unsigned int (*hash)(const char *key), char *buffer, const char *filename);
// Insert data.
void
hash_insert(hash_table_t *ht, char *key, char *data);
// Find data.
char *
hash_search(hash_table_t *ht, const char *key);
// Destruct hash-table.
void
hash_dtor(hash_table_t *ht);

#endif // HASH_TABLE

