#pragma once
#include "assembly.h"

// This file is for parsing assembly code and translating it to binary ("/hex code")

// returns 1 if the word is a constant, 2 if it is a macro, 0 otherwise.
byte is_expandable(char** expands, char* word);

// parses an assembly code into a sequence of bytes, contained the returned buffer.
char* parse_asm(ASM* assembly, char* asm_code);
HSENTENCE parse_asm_line(ASM* assembly, char** expands, char* asm_line);

// Used to disassemble code (reverse engineering for instance).
// Returns a buffer with the translated assembly.
char* parse_binary(ASM* assembly, char* binary_buffer);