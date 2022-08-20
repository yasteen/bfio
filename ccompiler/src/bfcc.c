#include <stdio.h>
#include <stdlib.h>

#include "include/bfcc.h"
#include "include/io.h"

int is_op(char c)
{
    return c == '+' ||
           c == '-' ||
           c == '<' ||
           c == '>' ||
           c == '.' ||
           c == ',' ||
           c == '[' ||
           c == ']' ||
           c == '"' ||
           c == '\'' ||
           c == ':' ||
           c == ';';
}

int simple_op(FILE *file, char **current, int tab)
{
    char delta = 0;
    while (**current == '+' || **current == '-' || !is_op(**current))
    {
        if (**current == '+')
            delta++;
        else if (**current == '-')
            delta--;
        *current = *current + 1;
    }
    if (delta)
    {
        char str[13];
        sprintf(str, "*ptr += %d;", delta);
        add_string(file, str, tab);
    }
    int offset = 0;
    while (**current == '>' || **current == '<' || !is_op(**current))
    {
        if (**current == '>')
            offset++;
        else if (**current == '<')
            offset--;
        *current = *current + 1;
    }
    if (offset)
    {
        char str[20];
        sprintf(str, "ptr += %d;", offset);
        add_string(file, str, tab);
    }
    return 0;
}

int bfcc_compile(char *src, char *filename)
{
    FILE *file = fopen(filename, "w+");
    int tab = 0;
    add_string(file, "#include <stdio.h>", tab);
    add_string(file, "#include <stdlib.h>", tab);
    add_string(file, "#include <string.h>", tab);
    add_string(file, "int main()\n{", tab);
    char data_array[70];
    sprintf(data_array, "char data[%d] = {0};\n\tchar *ptr = &data[0];", DATA_MAX);
    add_string(file, data_array, ++tab);
    add_string(file, "FILE *f;", tab);
    add_string(file, "int len;", tab);
    add_string(file, "char *fileName;", tab);

    char *current = src;

    while (*current != '\0')
    {
        if (*current == '+' || *current == '-' || *current == '<' || *current == '>')
        {
            simple_op(file, &current, tab);
            continue;
        }
        switch (*current)
        {
        case '[':
            add_string(file, "while (*ptr)", tab);
            add_string(file, "{", tab++);
            break;
        case ']':
            add_string(file, "}", --tab);
            break;
        case '.':
            add_string(file, "printf(\"%c\", *ptr);", tab);
            break;
        case ',':
            add_string(file, "*ptr = getchar();", tab);
            break;
        case '"':
            add_string(file, "len = *ptr;", tab);
            add_string(file, "fileName = malloc(sizeof(char) * (len + 1));", tab);
            add_string(file, "strncpy(fileName, ptr + 1, len);", tab);
            add_string(file, "fileName[len] = '\\0';", tab);
            add_string(file, "f=fopen(fileName, \"w+\");", tab);
            add_string(file, "free(fileName);", tab);
            break;
        case '\'':
            add_string(file, "fclose(f);", tab);
            break;
        case ':':
            add_string(file, "fwrite(ptr, sizeof(char), 1, f);", tab);
            break;
        case ';':
            add_string(file, "fread(ptr, sizeof(char), 1, f);", tab);
            break;
        }
        current++;
    }

    add_string(file, "return 0;\n}", tab--);
    return fclose(file);
}
