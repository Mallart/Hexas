// delete the following line to remove all debug infos and tests.
#define DEBUG
#include "assembly.h"


#ifdef DEBUG
void tests();
#endif

void main(int argc, char** argv)
{
#ifdef DEBUG
	tests();
#endif
	char* compiler_location = argv[0];
	argv++; argc--;
	char* asm_location = argv[0];
		
}

#ifdef DEBUG
void tests()
{
	dstr_print(new(DSTR, "Hey world !\n"), stdout);
	ASM test_asm = asm_parse_csv("./asm_example.csv");
	
	
	dstr_print(new(DSTR, "\0"), 0);
	le* third_row = LL_F(begin, TBL_F(get_row, test_asm.instructions, 3));
	for (size_t i = 0; i < LL_F(size, third_row); third_row = third_row->next, i++)
	{
		dstr_print(third_row->content, 0);
		char* s = str_trim(((dstr*)third_row->content)->str);
		size_t _len = dstr_len(third_row->content);
		for (size_t ii = 0; ii < TABLE_FUNC(max_column_width, test_asm.instructions, i) - _len; ++ii)
			printf(" ");
		printf(" | ");
	}


	asm_display(&test_asm);
	printf("0x%2x\n", asm_get_opcode(&test_asm, "PAUSE"));
	printf("Trying to get PAUSE instruction: %s\n", asm_get_instruction(&test_asm, asm_get_opcode(&test_asm, "PAUSE")));
	exit(0);
}
#endif