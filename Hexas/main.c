// delete the following line to remove all debug infos and tests from the program.
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
	
	
	asm_display(&test_asm);
	printf("0x%2x\n", asm_get_opcode(&test_asm, "PAUSE"));
	printf("Trying to get PAUSE instruction: %s\n", asm_get_instruction(&test_asm, asm_get_opcode(&test_asm, "PAUSE")));
	exit(0);
}
#endif