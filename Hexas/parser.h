#pragma once
#include "assembly.h"

// This file is for parsing assembly code and translating it to binary ("/hex code")

// parses an assembly code into a sequence of bytes, contained the returned buffer.
char* parse_asm(ASM* assembly, char* asm_code);
char* parse_asm_line(ASM* assembly, char* asm_line);