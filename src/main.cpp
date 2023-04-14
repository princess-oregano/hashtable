#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"
#include "file.h"
#include "list.h"

int
main()
{
        file_t text {};
        get_file("words_alpha.txt", &text, "a+");

        char *buffer = nullptr;
        read_file(&buffer, &text);
        
        char **arr = (char **) calloc(WORD_NUM, sizeof(char *));
        format_file(arr, buffer, &text);

        for (int i = 0; i < WORD_NUM; i++) {
                fprintf(stderr, "%s\n", arr[i]);
        }

        // Here hash table is filled/freed. Measuring.
        // ...

        free(arr);

        return 0;
}

