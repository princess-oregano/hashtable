#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "file.h"
#include "test.h"

int
test_fill(hash_table_t *ht, char *buffer, int size)
{
        assert(ht);
        assert(buffer);

        for (int i = 0; i < size; i++) {
                if (hash_insert(ht, &buffer[i * 32], &buffer[32 * i]) != HSH_NO_ERR) {
                        return HSH_LIST;
                }
        } 

        return HSH_NO_ERR;
}

int *
test_make_data(hash_table_t *ht)
{
        int *data = (int *) calloc(TABLE_SIZE, sizeof(int));
        if (!data) {
                return data;
        }

        for (int i = 0; i < TABLE_SIZE; i++) {
                data[i] = ht->table[i].elem[0].prev;
        }

        return data;
}

int
test(unsigned int (*hash)(const char *key), char *buffer, const char *filename)
{
        // File preparing module.
        file_t data_file {};
        get_file(filename, &data_file, "w"); 
        fprintf(data_file.stream, "x,y\n");

        // Hash-table(experiment) module.
        hash_table_t ht {};
        if (hash_ctor(&ht, hash) != HSH_NO_ERR) {
                return HSH_ALLOC;
        }

        if (test_fill(&ht, buffer, WORD_NUM) != HSH_NO_ERR) {
                return HSH_LIST;
        }

        // Data collecting module.
        int *data = test_make_data(&ht);
        if (data == nullptr) {
                fprintf(stderr, "Couldn't allocate memory for data.\n");
                return HSH_ALLOC;
        }

        // Data writing module.
        for (int i = 0; i < TABLE_SIZE; i++) {
                fprintf(data_file.stream, "%d,%d\n", i, data[i]);
        }

        free(data);
        hash_dtor(&ht);

        return HSH_NO_ERR;
}

