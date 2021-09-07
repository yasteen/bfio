#ifndef BFI_IO_H
#define BFI_IO_H
#include <stdio.h>

int add_string(FILE *file, char *str, int level);
char *bfcc_read_file(const char *filename);

#endif
