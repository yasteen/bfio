#include <stdio.h>
#include "include/io.h"
#include "include/bfi.h"

int main(int argc, char* argv[]) {
    if (argc == 1) {
        printf("Bfi is a brainfuck interpreter.\n\n");
        printf("Usage:\n\n\tbfi [FILE]\n\n");
        return 1;
    }
    printf("Starting brainfuck interpreter.\n");
    bfi_interpret(bfi_read_file(argv[1]));
    printf("\n");
    return 0;
}
