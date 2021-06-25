#include <stdio.h>

#define DATA_MAX 32768
int bfi_interpret(char * src, int debug)
{
    char DATA_ARRAY[DATA_MAX] = {0};
    char * data_ptr = &DATA_ARRAY[0];
    char * current = src;

    // negative: close bracket, positive: open bracket, zero: regular operation
    int skip_state = 0;

    while (*current != '\0') {
        if (*current == '[' && (skip_state != 0 || *data_ptr == 0)) skip_state++;
        if (*current == ']' && (skip_state != 0 || *data_ptr != 0)) skip_state--;
        if (skip_state == 0) {
            if (*current == '+' || *current == '-') {
                if (data_ptr < &DATA_ARRAY[0] ||
                        data_ptr > &DATA_ARRAY[DATA_MAX - 1]) {
                    printf("Data pointer out of bounds.");
                    printf("\tMin address: %p\n", (void *) &DATA_ARRAY[0]);
                    printf("\tMax address: %p\n", (void *) &DATA_ARRAY[DATA_MAX - 1]);
                    printf("\tPointer: %p\n", (void *) data_ptr);
                    return 1;
                }
            }
            switch (*current) {
                case '>': data_ptr++; break;
                case '<': data_ptr--; break;
                case '+': *data_ptr = *data_ptr + 1; break;
                case '-': *data_ptr = *data_ptr - 1; break;
                case '.': putchar(*data_ptr); break;
                case ',': *data_ptr = getchar(); break;
            }
        }
        if (skip_state < 0) current--;
        else current++;
    }
    if (skip_state != 0) {
        printf("Unmatched brackets");
        return 1;
    }
    if (debug) {
        printf("ALL CHARS: %s\n", DATA_ARRAY);
    }
    return 0;
}
