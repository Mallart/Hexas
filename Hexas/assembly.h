#pragma once
#include "data_structures.h"
#include "files.h"

// TODO: assembly data structure
// TODO: CSV files reading for modular assembly conversion

// There are two "classes" of assembly: x32 bits and x64 bits.
// To use functions with 32 bits assemblies, 

// Assembly is a data structure containing relevant infos about an assembly.
typedef struct
{
	// assembly name, should be the first cell in first line
	dstr* name;
	// size of the target architecture: could be 4 / 8 / 16 / 32 / 64 bits
	byte size;
	// linked table of all the assembly's instruction set
	table* instructions;
} assembly, Assembly, ASSEMBLY, _asm_, ASM;

ASM asm_parse_csv(char* path);
void asm_display(ASM* asm);
// returns a two-dimensional point with max possible opcode coordinates for rows and columns.
LPOINT asm_get_max_index(ASM* asm);
// returns the instruction at the given number.
// can be used to disassemble.
// it is the largest type available, so the opcode can be translated to whatever instruction up to x64 systems.
char* asm_get_instruction(ASM* asm, int64 opcode);
// Will look for an instruction with the same name then return the opcode.
int64 asm_get_opcode(ASM* asm, char* instruction);