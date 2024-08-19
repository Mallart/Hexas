#include "parser.h"

char* parse_asm(ASM* assembly, char* asm_code)
{
	// TODO
	uint64 caret = 0;
	uint32 len = str_count_char(asm_code, strlen(asm_code), '\n');
	char* buffer;
	char** lines = str_split(asm_code, '\n');
	char* line = lines[0];
	for (uint32 i = 0; i < len; ++i, line++)
	{
		safe_malloc(buffer, sizeof(char) * (6));
		HSENTENCE parsed_line = parse_asm_line(assembly, NULL, line);
		memcpy(buffer + llround(caret / 8.f), parsed_line.content, parsed_line.size);
		caret += parsed_line.size;
	}
	return 0;
}

HSENTENCE parse_asm_line(ASM* assembly, char** expands, char* asm_line)
{
	asm_line = str_remove_comment(asm_line);
	byte n_words = str_count_char(asm_line, strlen(asm_line), ',');
	// caret in buffer;
	uint64 caret = 0;
	unsigned char* buffer = malloc(sizeof(char) * assembly->size * n_words);
	if (!buffer)
		throw(MEMORY_ALLOCATION_NOT_ENOUGH_SPACE);
	switch (n_words)
	{
	case 1:
	{
		// there is only one word and thus, must be separated with a space instead of a regular 
		// comma.
		char** sentence = str_split(asm_line, ' ');
		uint64 opcode = asm_get_opcode(assembly, sentence[0]);
		if (opcode == asm_error(assembly))
			throw(PARSER_UNKOWN_INSTRUCTION);
		LPHWORD instruction = asm_get_instruction(assembly, opcode);
		if (!strlen(sentence[1]))
		{
			buffer[caret] = opcode;
			return (HSENTENCE) { .content = buffer, .size = instruction->size};
		}
		uint64 code;
		// second word shouldn't be an instruction.
		if (asm_get_opcode(assembly, sentence[1]) != asm_error(assembly))
			throw(PARSER_INVALID_OPERAND);
		if (is_num(sentence[1]))
			code = str_parse_num(sentence[1]);
		else
			code = asm_get_regcode(assembly, str_parse_num(sentence[1]));
		buffer[caret] = opcode;
		caret += instruction->size;
		buffer[caret] = code;
		caret += size_of(code);
		buffer[caret] = 0;
		return (HSENTENCE) { .content = buffer, .size = instruction->size + size_of(code) };
	}
	case 2:
	{
		char** sentence = str_split(asm_line, ',');
		// first word 
		uint64 opcode = asm_get_opcode(assembly, sentence[0]);
		if (opcode == asm_error(assembly))
			throw(PARSER_UNKOWN_INSTRUCTION);
		LPHWORD instruction1 = asm_get_instruction(assembly, opcode);

	}
	case 3:
	{

	}
	}
	// TODO: 
	// 
	// - two words sentence
	// - three words sentence 
	// - add size in bits for each of them + one word sentence

	char** sentence = str_split(asm_line, ',');
	char* word = sentence[0];
	// first word is always instruction, other words are complementary but ONLY if the sentence
	// is one-word long.
	for (byte i = 0; i < n_words; ++i, word++)
	{
		char* trimmed = str_trim(word);
		uint64 opcode = asm_get_opcode(assembly, word);
		buffer[caret] = opcode;
		caret += size_of(opcode);
	}
	buffer[caret + 1] = 0;
	return (HSENTENCE) { .content = buffer };
}

char* parse_binary(ASM* assembly, char* binary_buffer)
{
	return 0;
}
