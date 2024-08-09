#pragma once
#define throw(code) exit(code);
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
} HEXAS_COMPILER_ERROR;