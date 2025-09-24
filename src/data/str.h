#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// general operator to create an instance of a struct of any type
#define build(type) type##_FUNC(new)
// general operator to create an instance of a struct of any type
#define build_args(type, ...) type##_FUNC(new, __VA_ARGS__)

// removes a single char from string.
char* str_remove_char(char* str, char c);
void str_ptr_remove_char(char* str, char c);
// returns an array of strings splitted by a delimiter. Last element of array is a null pointer.
char** str_split(char* str, char delimiter);
// returns the size of a string processed by the "str_split(char* str)" function
size_t str_table_size(char** strtable);
void delete_str_table(char** strtable);

// Returns a substring of the given string, starting at origin and ending at origin + count.
// if count is 0, will return a copy of the given string from origin to end of original string.
char* str_substr(char* str, size_t origin, size_t count);
// Finds a character in a string and returns its position.
size_t str_find_char(char* str, char c);
size_t str_find_last_char(char* str, char c);

// returns two characters for the hex value of the given byte
char* byte_bin_to_hex(unsigned char byte);
// converts two hexadecimal characters into a single 8-bit (byte) value 
char byte_hex_to_bin(char* hex);

// converts "count" bytes into hexadecimal values.
char* bin_to_hex(char* bin_data, size_t count);
// converts "count" hexadecimal bytes (pair of hex digits, ex: 0xF4) values into bytes.
char* hex_to_bin(char* bin_data, size_t count);

// removes any blank character before the first alphanumeric character and after the last.
char* str_trim(char* str);

// returns a copy of this string, but ensures it's allocated in memory.
// yeah it's better than the whole concept of dynamic string that was here before. since then I studied.
char* allocated_string(char* str);

unsigned char str_equals(char* str1, char* str2);