#pragma once
#include "data_structures.h"
#include "table.h"
#include "files.h"

// Note on assembly files:
// It's really important to have a table with fixed width and length, as it's what's used to read and retrieve
// opcodes.
// It's not fixed in bytes, so you can have assembly tables with, for instance, 4 columns; leading to
// an opcode splitting of 3 bits (3 bits to write 4), meaning the first instruction will be 0x00, and the last
// reachable will be 0x44 (0b01000100).
// Assembly instructions data files must be squared (number of columns and of rows equal), and
// each row and each column must have the exact same length, as the rows length are used to split opcodes into
// two different coordinates (rows and columns).

// some words that aren't instructions needs the same bytecode than instructions. To comply with this, 
// there's a special character, ';' (semicolon) than enables several words to be in the same cell.
// Be careful though, the first word (the one before the first semicolon in one "cell", a "cell" being
// the space between two commas) must ALWAYS be the assembly instruction. Then can be appended man other
// elements, the first one being the assembly instruction, then registry, then flag. Note that
// on some assembly languages, the "flag registry" is just a registry.
// And yes, that, in some way, enables "3D CSV".

// Assembly is a data structure containing relevant infos about an assembly.
typedef struct
{
	// assembly name, should be the first cell in first line
	dstr* name;
	// size of the target architecture: could be 4 / 8 / 16 / 32 / 64 bits
	byte size;
	// linked table of all the assembly's instruction set
	table* instructions;
	// linked table of all the assembly's registries and flags.
	table* registries;
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