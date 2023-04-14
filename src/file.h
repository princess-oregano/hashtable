#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <sys/stat.h>

// Structure to store information about file.
struct file_t {
        FILE  *stream = nullptr;
        struct stat stats = {};
        const char *filename = nullptr;
};

// Error codes.
enum file_err_t {
        F_ERR_NO_ERR = 0,
        F_ERR_ALLOC = 1,
        F_ERR_OPEN = 2,
        F_ERR_STATS = 3,
        F_ERR_SYNTAX = 4,
        F_ERR_MAP = 5,
        F_ERR_EMPTY = 6,
};

// Makes a structure with info about file.
int
get_file(const char *filename, file_t *file, const char *mode);
// Reads file and puts its contents to a buffer.
int
read_file(char **buffer, file_t *file);
// Changes text in buffer to simplify following operations.
void
format_file(char **arr, char *buffer, file_t *file);

#endif // FILE_H

