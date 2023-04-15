#include <stdio.h>
#include <stdlib.h>
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
        
        char **arr = (char **) calloc(WORD_NUM, sizeof(char *));
        format_file(arr, buffer, &text);

        // Test module.
        hash_test(&hash_one, arr, "test1.csv");
        hash_test(&hash_first_ascii, arr, "test2.csv");
        hash_test(&hash_len, arr, "test3.csv");
        hash_test(&hash_sum_ascii, arr, "test4.csv");
        hash_test(&hash_rol, arr, "test5.csv");
        hash_test(&hash_ror, arr, "test6.csv");
        hash_test(&hash_crc32, arr, "test7.csv");

        free(arr);

        return 0;
}

