//
// Created by Christopher Szatmary on 2018-02-18.
//

#ifndef ATTIC_UTILS_H
#define ATTIC_UTILS_H

#include <stdio.h>
#include <stdbool.h>

#define ALL_RW_PERM 0666
#define ALL_RX_PERM 0555
#define MAX_RW_PERM 0766
#define MAX_RX_PERM 0755

#define BUFFER_SIZE 8192

#define STATUS_OK 0
#define ERROR_READ -1
#define ERROR_WRITE -2
#define ERROR_CREATE -3
#define ACTION_ABORTED -4

typedef int (*print_func)(FILE*, const char*, ...);

int copy_file(const char *file_name, const char *destination, mode_t permissions);
void set_verbose(bool value);
int fverbose_print(FILE *stream, const char *restrict format, ...);
int verbose_print(const char *restrict format, ...);
char* get_home_dir();
bool check_file_exists(const char *file_name);

#endif //ATTIC_UTILS_H
