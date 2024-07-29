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
	printf("0x%2x", asm_get_opcode(&test_asm, "PAUSE"));
	printf("\nsize of %i: %llu", 0b001100110011, size_of(819));
	bprint(819);
	size_t size_test = 0b11000100010001000;
	printf("\nsize of %llu: %llu", size_test, size_of(size_test));
	printf("\nsize of %i: %llu", 0b10010, size_of(0b10010));
	exit(0);
}
#endif