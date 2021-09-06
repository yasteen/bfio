#include <stdio.h>

#include "include/bfcc.h"

int bfcc_compile(char *src, char *filename)
{
    FILE *file = fopen(filename, "w+");
    int tab = 0;
    add_string(file, "#include <stdio.h>\n\nint main()\n{", tab);
    // Max integer is 10 digits (hence we only need 29 characters)
    char *data_array[30];
    sprintf(data_array, "char data[%d] = {0};\n\tchar *ptr = &data[0];\n\tFILE *f;", DATA_MAX);
    add_string(file, data_array, ++tab);

    char *current = *src;
    while(*current != '\0')
    {
        switch(*current)
        {
            case '+':
            case '-':
            case '<':
            case '>':
                simple_op(file, src, tab);
        }
    }

    add_string(file, "return 0;\n}", tab--);
    return fclose(file);
}

int simple_op(FILE *file, char *src, int tab)
{
    char delta = 0;
    while (*src == '+' || *src == '-')
    {
        if (*src == '+')
            delta++;
        else
            delta--;
    }
    if (delta)
    {
        char str[11] = sprintf("*ptr += %c;", delta);
        add_string(file, str, tab);
    }
    int offset = 0;
    while (*src == '>' || *src == '<')
    {
        if (*src == '>')
            offset++;
        else
            offset--;
    }
    if (offset)
    {
        char str[20] = sprintf("ptr += %d;", offset);
        add_string(file, str, tab);
    }
    return 0;
}
