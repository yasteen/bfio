#include <stdio.h>

int bfi_interpret(char * src)
{
    char DATA_ARRAY[32768] = {0};
    char * data_ptr = &DATA_ARRAY[0];
    char * current = src;

    // -1: back skip; 0: regular; 1: skip
    int operation = 0;

    while (*current != '\0') {
        if (operation == 0) {
            switch (*current) {
                case '>': data_ptr++; break;
                case '<': data_ptr--; break;
                case '+': *data_ptr = *data_ptr + 1; break;
                case '-': *data_ptr = *data_ptr - 1; break;
                case '.': putchar(*data_ptr); break;
                case ',': *data_ptr = getchar(); break;
                case '[': if (*data_ptr == 0) operation = 1; break;
                case ']': if (*data_ptr == 0) operation = -1; break;
                default: //printf("Invalid command");
                              break;
            }
            if (operation == 0) current++;
        } else if (operation == -1) {
            if (*current != '[') current--;
            current++;
            operation = 0;
        } else if (operation == 1) {
            if (*current != ']') current++;
            current++;
            operation = 0;
        } else {
            printf("Invalid operation\n");
            return 1;
        }
    }
    return 0;
}
