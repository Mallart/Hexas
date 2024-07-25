#include "files.h"

char* read_all_file(char* path)
{
    FILE* f;
    if (f = fopen(path, "rb"))
    {
        size_t _file_size = file_size(f);
        char* file_content = malloc(sizeof(char) * _file_size);
        if (!file_content)
            return 0;
        fread(file_content, sizeof(char), _file_size, f);
        fclose(f);
        return file_content;
    }
    return 0;
}

size_t file_size(FILE* stream)
{
    if (!stream)
        return 0;
    fseek(stream, SEEK_END, 0);
    size_t size = ftell(stream);
    fseek(stream, SEEK_SET, 0);
    return size;
}
