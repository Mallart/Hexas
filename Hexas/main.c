// delete the following line to remove all debug infos and tests from the program.
#define DEBUG
#include "assembly.h"
#define N_ARGS 10

// arguments that the compiler can take
static char const * const arguments[N_ARGS] = {
	""
};

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
	// csv module location
	if (argc < 2)
		throw(COMPILER_NOT_ENOUGH_ARGUMENTS);
	char* asm_location = argv[0];
	char* codefile_location = argv[1];
	asm_parse_csv(asm_location);
}

#ifdef DEBUG
void tests()
{
	ASM test_asm = asm_parse_csv("./asm_example.csv");
	asm_display(&test_asm);
	printf("0x%2x\n", asm_get_opcode(&test_asm, "PAUSE"));
	printf("Trying to get PAUSE instruction: %s\n", asm_get_instruction(&test_asm, asm_get_opcode(&test_asm, "PAUSE")));
	printf("Trying to get RFX registry: %s\n", asm_get_registry(&test_asm, asm_get_regcode(&test_asm, "RFX")));
	exit(0);
}
#endif