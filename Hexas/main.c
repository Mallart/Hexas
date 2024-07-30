// delete the following line to remove all debug infos and tests.
#define DEBUG
#include "gui.h"
#include "assembly.h"

#include <time.h>

#ifdef DEBUG
void tests();
#endif

void main(int argc, char** argv)
{
	tests();
}

#ifdef DEBUG
void tests()
{
	ASM test_asm = asm_parse_csv("./asm_example.csv");
	asm_display(&test_asm);
	printf("0x%2x\n", asm_get_opcode(&test_asm, "PAUSE"));
	printf("Trying to get PAUSE instruction: %s\n", asm_get_instruction(&test_asm, asm_get_opcode(&test_asm, "PAUSE")));
	exit(0);
}
#endif