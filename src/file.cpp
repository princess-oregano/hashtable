#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <assert.h>
#include "file.h"
#include "hash_table.h"

int
get_file(const char *filename, file_t *file, const char *mode)
{
        if ((file->stream = fopen(filename, mode)) == nullptr) {
                fprintf(stderr, "Error: Couldn't open %s.\n", filename);

                return F_ERR_OPEN;
        }
        rewind(file->stream);
        if (stat(filename, &file->stats) != 0) {
                fprintf(stderr, "Error: Coudn't get stats of %s.\n", filename);
                return F_ERR_STATS;
        }

        file->filename = filename;

        return F_ERR_STATS;
}

int
read_file(char **buffer, file_t *file)
{
        assert(file);
        assert(buffer);

        *buffer = (char *) mmap(NULL, (size_t) file->stats.st_size, PROT_WRITE,
                               MAP_PRIVATE, fileno(file->stream), 0);

        if (*buffer == MAP_FAILED) {
                fprintf(stderr, "Error: Couldn't allocate memory.\n");
                return F_ERR_MAP;
        }

        return F_ERR_NO_ERR;
}

void
format_file(char **new_buffer, char *buffer, file_t *file)
{
        assert(new_buffer);
        assert(file);
        assert(buffer);

        char *new_buf = (char *) calloc(WORD_NUM * 32, sizeof(char));

        int count = 0;
        for (int i = 0; i < file->stats.st_size; i++) {
                if (buffer[i] == '\n') {
                        new_buf[count] = '\0';
                        count = (count / 32) * 32 + 32;
                } else {
                        new_buf[count] = buffer[i];
                        count++;
                }
        }
        
        *new_buffer = new_buf;
}
