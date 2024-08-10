#include "parser.h"

char* parse_asm(ASM* assembly, char* asm_code)
{
	// TODO

	return 0;
}

char* parse_asm_line(ASM* assembly, char* asm_line)
{
	// there should be a maximum of 3 components by instructions line
	unsigned char* buffer = malloc(sizeof(char) * assembly->size * 3);

	return buffer;
}
