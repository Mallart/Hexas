#pragma once
#define _CRT_SECURE_NO_WARNINGS
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
// removes a single char from string.
char* str_remove_char(char* str, char c);
void str_ptr_remove_char(char* str, char c);
// returns an array of strings splitted by a delimiter. Last element of array is a null pointer.
char** str_split(char* str, char delimiter);
// returns the size of a string processed by the "str_split(char* str)" function
size_t str_table_size(char** strtable);
void delete_str_table(char** strtable);
// frees the original string to create a new dynamic string.
dstr* str_to_dstr(char* str);
inline char* dstr_to_str(dstr* _dstr);

// Returns a substring of the given string, starting at origin and ending at origin + count.
// if count is 0, will return a copy of the given string from origin to end of original string.
char* str_substr(char* str, size_t origin, size_t count);
// Finds a character in a string and returns its position.
size_t str_find_char(char* str, char c);
size_t str_find_last_char(char* str, char c);

// returns two characters for the hex value of the given byte
char* byte_bin_to_hex(unsigned char byte);
// converts two hexadecimal characters into a single 8-bit (byte) value 
unsigned char byte_hex_to_bin(char* hex);

// converts "count" bytes into hexadecimal values.
char* bin_to_hex(char* bin_data, size_t count);
// converts "count" hexadecimal bytes (pair of hex digits, ex: 0xF4) values into bytes.
char* hex_to_bin(char* bin_data, size_t count);

// removes any blank character before the first alphanumeric character and after the last.
char* str_trim(char* str);

unsigned char str_equals(char* str1, char* str2);