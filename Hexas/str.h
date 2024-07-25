#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// general operator to create an instance of a struct of any type
#define new(type) type##_FUNC(new)
#define new(type, ...) type##_FUNC(new, __VA_ARGS__)

#define DSTR_FUNC(fname, ...) dstr_##fname(__VA_ARGS__)

// "Dynamic strings" are just strings allocated in memory. They aren't const and only differ from
// regular C strings by that.
// If you're looking for dynamic-sized strings, you better use linked lists.
// If you're storing C strings directly in linked lists, use this.
typedef struct
{
	char* str;
} dynamic_string, d_str, dstr, D_STR, DSTR;

dstr* DSTR_FUNC(new, char* content);
void DSTR_FUNC(set, dstr* str, char* content);
void DSTR_FUNC(free, dstr* str);
char* str_remove_char(char* str, char c);
void str_ptr_remove_char(char* str, char c);

// returns two characters for the hex value of the given byte
char* byte_bin_to_hex(unsigned char byte);
// converts two hexadecimal characters into a single 8-bit (byte) value 
unsigned char byte_hex_to_bin(char* hex);

// converts "count" bytes into hexadecimal values.
char* bin_to_hex(char* bin_data, size_t count);
// converts "count" hexadecimal values into bytes.
char* hex_to_bin(char* bin_data, size_t count);
