#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#include "data_structures.h"
#include "str.h"

char* read_all_file(char* path);
size_t file_size(FILE* stream);
void append_bytes(FILE*stream, char* buffer, size_t length);