// delete the following line to remove all debug infos and tests.
#define DEBUG
#include "assembler/assembly.h"

#ifdef DEBUG
void tests();
#endif

int main(int argc, char** argv)
{
	tests();
	return 0;
}

#ifdef DEBUG
void tests()
{
	ASM test_asm = asm_parse_csv("./languages/asm_example.csv");
	asm_display(&test_asm, stdout);
	printf("0x%2lx\n", asm_get_opcode(&test_asm, "PAUSE"));
	printf("Trying to get PAUSE instruction: %s\n", asm_get_instruction(&test_asm, asm_get_opcode(&test_asm, "PAUSE")));
	exit(0);
}
#endif