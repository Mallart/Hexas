#include "parser.h"

char* parse_asm(ASM* assembly, char* asm_code)
{
	// TODO

	return 0;
}

char* parse_asm_line(ASM* assembly, char* asm_line)
{
	// each space represents a different piece on binary code and thus, a different piece to encode.
	byte n_spaces = str_count_char(asm_line, strlen(asm_line), ' ');
	// caret in buffer;
	uint64 caret = 0;
	unsigned char* buffer = malloc(sizeof(char) * assembly->size * n_spaces);
	if (!buffer)
		throw(MEMORY_ALLOCATION_NOT_ENOUGH_SPACE);
	char** sentence = str_split(asm_line, ' ');
	char* word = sentence[0];
	for (byte i = 0; i < n_spaces; ++i, word++)
	{
		char* trimmed = str_trim(word);
		uint64 opcode = asm_get_opcode(assembly, word);
		buffer[caret] = opcode;
		caret += size_of(opcode);
	}
	buffer[caret + 1] = 0;
	return buffer;
}

char* parse_binary(ASM* assembly, char* binary_buffer)
{
	return 0;
}
