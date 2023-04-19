#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "file.h"
#include "list.h"

int
main()
{
        // File reading and preparing module.
        file_t text {};
        get_file("words_alpha.txt", &text, "a+");

        char *buffer = nullptr;
        read_file(&buffer, &text);
        
        char *new_buf = nullptr;
        format_file(&new_buf, buffer, &text);
        /*
         *for (int i = 0; i < 100; i++) {
         *        fprintf(stderr, "%s\n", &new_buf[i * 32]);
         *}
         */

        // Test module.
        /*
         *hash_test(&hash_one, arr, "test1.csv");
         *hash_test(&hash_first_ascii, arr, "test2.csv");
         *hash_test(&hash_len, arr, "test3.csv");
         *hash_test(&hash_sum_ascii, arr, "test4.csv");
         *hash_test(&hash_rol, arr, "test5.csv");
         *hash_test(&hash_ror, arr, "test6.csv");
         *hash_test(&hash_crc32, arr, "test7.csv");
         */

        // Search module.
        hash_table_t ht {};
        if (hash_ctor(&ht, &hash_crc32) != HSH_NO_ERR) {
                return HSH_ALLOC;
        }

        hash_fill(&ht, new_buf, WORD_NUM);
        for (int i = 0; i < WORD_NUM; i++) {
                fprintf(stderr, "%s %s\n", &new_buf[i * 32], hash_search(&ht, &new_buf[i * 32]));
                /*
                 *if (strcmp(&new_buf[i * 32], hash_search(&ht, &new_buf[i * 32])) != 0)
                 *        fprintf(stderr, "Error\n");
                 */
                /*
                 *hash_search(&ht, &new_buf[i * 32]);
                 */
        }

        hash_dtor(&ht);
        free(new_buf);

        return 0;
}

