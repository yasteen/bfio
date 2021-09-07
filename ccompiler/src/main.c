#include <stdio.h>
#include <stdlib.h>
#include "include/io.h"
#include "include/bfcc.h"

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("Bfi is a brainfuck C compiler.\n\n");
        printf("Usage:\n\n\tbfi [FILE]\n\n");
        return 1;
    }
    int status = bfcc_compile(bfcc_read_file(argv[1]), "b.c");
    if (status)
    {
        printf("An error occured.");
    }
    system("gcc b.c");
    return status;
}
