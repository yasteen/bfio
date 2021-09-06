#include "include/io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int add_string(FILE *file, char *new, int level)
{
    char tabs[level + 1];
    memset(tabs, '\t', level);
    fprintf(file, "%s%s\n", tabs, new);
}

int bfcc_write_file(const char *filename, char *src)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(filename, "w+");
    if (fp == NULL)
    {
        printf("Could not write to file %s \n", filename);
        exit(1);
    }
    if (fputs(src, fp) < 0)
    {
        printf("Error occured while writing to file %s \n", filename);
        exit(1);
    }
    return fclose(fp);
}

char *bfcc_read_file(const char *filename)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        printf("Could not read file `%s`\n", filename);
        exit(1);
    }

    char *buffer = (char *)calloc(1, sizeof(char));
    buffer[0] = '\0';

    while ((read = getline(&line, &len, fp)) != -1)
    {
        buffer = (char *)realloc(buffer, (strlen(buffer) + strlen(line) + 1) * sizeof(char));
        strcat(buffer, line);
    }

    fclose(fp);
    if (line)
        free(line);

    return buffer;
}
