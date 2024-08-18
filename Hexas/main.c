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
	// arguments and parsing
}

#ifdef DEBUG

void macros_tests()
{
	
	expand q_test =
	{
		.reexpand = 0,
		.result = "This %1 is expanded %3 %2.",
		.n_args = 0,
		.word = "rexp2"
	};
	char* arg =	"Macro";
	char* arg2 =	"indeed";
	char* arg3 =	"now,";
	expand t_test =
	{
		.reexpand = 1,
		.result = &q_test,
		.n_args = 1,
		.word = "rexp",
		.args = &arg3,
	};
	expand s_test =
	{
		.reexpand = 1,
		.result = &t_test,
		.n_args = 1,
		.word = "exp",
		.args = &arg2,
	};
	expand test =
	{
		.reexpand = 1,
		.word = "macro",
		.n_args = 1,
		.args = &arg,
		.result = &s_test,
	};

	printf("Trying to expand a macro: %s", exp_expand(&test));
}

void tests()
{
	ASM test_asm = asm_parse_csv("./asm_example.csv");
	asm_display(&test_asm);
	printf("0x%2x\n", asm_get_opcode(&test_asm, "PAUSE"));
	printf("Trying to get PAUSE instruction: %s\n", asm_get_instruction(&test_asm, asm_get_opcode(&test_asm, "PAUSE"))->name->str);
	printf("Trying to get RFX registry: %s\n", asm_get_registry(&test_asm, asm_get_regcode(&test_asm, "RFX"))->name->str);
	
	macros_tests();
	exit(0);
}
#endif
