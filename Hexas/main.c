// delete the following line to remove all debug infos and tests.
#define DEBUG
#include "gui.h"
#include "assembly.h"

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
	printf("0x%64x", asm_get_opcode(&test_asm, "PAUSE"));
	printf("\nsize of %i: %i", 0b1100110011, size_of(819));
	printf("\nsize of %i: %i", 0b0010, size_of(2));
	exit(0);
}
#endif