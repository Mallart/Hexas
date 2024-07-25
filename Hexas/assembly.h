#pragma once
#include "data_structures.h"
#include "files.h"

// TODO: assembly data structure
// TODO: CSV files reading for modular assembly conversion

// Assembly is a data structure containing relevant infos about an assembly.
typedef struct
{
	// assembly name, should be the first cell in first line
	dstr* name;
	// size of the target architecture: could be 8 / 16 / 32 / 64 bits
	byte size;
	// linked table of all the assembly's instruction set
	table* instructions;
} assembly, Assembly, ASSEMBLY, _asm_, ASM;

ASM asm_parse_csv(char* path);