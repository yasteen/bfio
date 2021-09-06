#include <stdio.h>

#include "include/bfcc.h"

int bfcc_compile(char *src, char *filename)
{
    FILE *file = fopen(filename, "w+");
    add_string(file, "#include <stdio.h>\n\nint main()\n{", 0);
    // Max integer is 10 digits (hence we only need 29 characters)
    char *data_array[30];
    sprintf(data_array, "char data[%d] = {0};\n\tchar *ptr = &data[0];", DATA_MAX);
    add_string(file, data_array, 1);

    add_string(file, "return 0;\n}", 1);
    return src;
}