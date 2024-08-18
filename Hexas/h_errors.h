#pragma once
// stops the program with given code
#define throw(code) exit(code);
// ensures the program stops if the memory couldn't be allocated
#define safe_malloc(var, size) var = malloc(size); if(!var) throw(MEMORY_ALLOCATION_NOT_ENOUGH_SPACE)
// tests heap with a quick and light memory allocation to know if it is corrupted
#define test_heap { char* safe_malloc(__testptr__, 4); __testptr__[0] = 't'; printf("Testing %i in file %s...\n ", __LINE__, __FILE__); free(__testptr__); };
typedef enum
{
	// normal behavior, usually returned at the end of the program.
	NO_ERROR,
	// when the program cannot allocate enough memory for any needed variable.
	MEMORY_ALLOCATION_NOT_ENOUGH_SPACE,
	// when freeing an empty space.
	MEMORY_DEALLOCATION_EMPTY_SPACE,
	// when using a dereferenced pointer.
	MEMORY_DEREFERENCED_POINTER_USED,
	// when accessing an offset from a pointer that's not allocated by the program.
	MEMORY_OUT_OF_BOUNDS,

	// About the executable and arguments errors,

	// When an argument isn't recognized by the program
	COMPILER_UNKNOWN_ARGUMENT,
	// When the minimum argument count required isn't met
	COMPILER_NOT_ENOUGH_ARGUMENTS,

	// Now for the compiler errors occuring during the compilation process itself;
	
	// Invalid operator used in assembly code.
	CODE_INVALID_OPERATOR,
	// Invalid instruction used in assembly code. Try changing assembly reference ?
	CODE_UNKOWN_INSTRUCTION,

} HEXAS_COMPILER_ERROR;