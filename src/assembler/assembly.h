#pragma once
#include "../data/data_structures.h"
#include "../data/table.h"

// TODO: assembly data structure
// TODO: CSV files reading for modular assembly conversion

// Note on assembly files:
// It's really important to have a table with fixed width and length, as it's what's used to read and retrieve
// opcodes.
// It's not fixed in bytes, so you can have assembly tables with, for instance, 4 columns; leading to
// an opcode splitting of 3 bits (3 bits to write 4), meaning the first instruction will be 0x00, and the last
// reachable will be 0x44 (0b01000100).
// Assembly instructions data files must be squared (number of columns and of rows equal), and
// each row and each column must have the exact same length, as the rows length are used to split opcodes into
// two different coordinates (rows and columns).

// Assembly is a data structure containing relevant infos about an assembly.
typedef struct
{
	// assembly name, should be the import name
	char* name;
	// size of the target architecture: could be 4 / 8 / 16 / 32 / 64 bits
	byte size;
	// linked table of all the assembly's instruction set
	table* instructions;
} assembly, Assembly, ASSEMBLY, _asm_, ASM;

// Serializes a CSV file into an assembly structure
ASM asm_parse_csv(char* path);

void asm_display(ASM* _asm, FILE* stream);
// returns a two-dimensional point with max possible opcode coordinates for rows and columns.
LPOINT asm_get_max_index(ASM* _asm);
// returns the instruction at the given number.
// can be used to disassemble.
// it is the largest type available, so the opcode can be translated to whatever instruction up to x64 systems.
char* asm_get_instruction(ASM* _asm, int64 opcode);
// Will look for an instruction with the same name then return the opcode.
int64 asm_get_opcode(ASM* _asm, char* instruction);