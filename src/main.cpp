#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "file.h"
#include "test.h"
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

        // Test module.
        //test(&hash_one, new_buf, "test1.csv");
        //test(&hash_first_ascii, new_buf, "test2.csv");
        //test(&hash_len, new_buf, "test3.csv");
        //test(&hash_sum_ascii, new_buf, "test4.csv");
        //test(&hash_rol, new_buf, "test5.csv");
        //test(&hash_ror, new_buf, "test6.csv");
        //test(&hash_crc32, new_buf, "test7.csv");

        // Search module.
        hash_table_t ht {};
        if (hash_ctor(&ht, &hash_crc32) != HSH_NO_ERR) {
                return HSH_ALLOC;
        }

        test_fill(&ht, new_buf, WORD_NUM);
        for (int j = 0; j < 100; j++) {
                for (int i = 0; i < WORD_NUM; i++) {
                        //fprintf(stderr, "%s %s\n", &new_buf[i * 32], hash_search(&ht, &new_buf[i * 32]));
                        //if (strcmp(&new_buf[i * 32], hash_search(&ht, &new_buf[i * 32])) != 0)
                                //fprintf(stderr, "Error\n");
                        hash_search(&ht, &new_buf[i * 32]);
                }
        }

        hash_dtor(&ht);
        free(new_buf);

        return 0;
}

