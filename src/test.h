#ifndef TEST_H
#define TEST_H

#include "hash_table.h"

// Fill hash-table with array of data 'arr'.
int
test_fill(hash_table_t *ht, char *buffer, int size);
// Creates an array with number of elements in i-th list.
int *
test_make_data(hash_table_t *ht);
// Make test of specific hash function using 'arr' as data.
int
test(unsigned int (*hash)(const char *key), char *buffer, const char *filename);

#endif // TEST_H
