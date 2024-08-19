#pragma once
#include "data_structures.h"
#include "expand.h"
#include "table.h"
#include "files.h"

// What separates two entries / cells
#define HEXAS_ENTRY_SEPARATOR ','
// What enables several tables to overlap in a single CSV ("3D CSV")
#define HEXAS_KEYWORD_SEPARATOR ';'
// What enables custom word sizing (what makes the compiler write "0xBF00" instead of "0xBF")
#define HEXAS_WORD_SIZE_INDICATOR ':'
// Where the name is located related to the size indicator.
#define HEXAS_CELL_NAME 0
// Where the size is located related to the size indicator.
#define HEXAS_CELL_SIZE 1

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
// elements, the first one being the assembly instruction, then registry, then keyword. Note that
// on some assembly languages, the "flag registry" is just a registry.
// And yes, that, in some way, enables "3D CSV".

// I recently came across the fact that some opcodes are smaller than others. For this kind of assemblers,
// I added some syntactic sugar to my "CSV" (if we still can call it like that) parsing to tell the parser
// the exact size (IN BITS, NOT IN BYTES) of any code (registers, instructions, flags...).
// In order to do that, simply add "XXX:n", where 'n' is the word size in bits, ':' is a constant delimiter
// (in other words, don't change that), and "XXX" is a the word name (variable in length, not limited to
// only 3 characters. Saying that just in case you want to add an instruction whose name is
// PLZCANTHECPUPOPONTHESTACKWITHOUTCRASHINGAGAIN. Though it will make your code harder to read and bigger.
// Just saying. You do you).

// A "hword" is either an instruction, a register or a flag in an assembly table.
typedef struct HEXAS_WORD
{
	// The word name. Could be an instruction's name, a register name...
	// Anything as long as it's the same as in the assembly table and in parsed assembly code.
	dstr* name;
	// The word size. Some words are larger than others, and need to be filled with null bits.
	// The size is in bits, not in bytes.
	// If 0, will use default size to write the code (just enough for it to fit).
	byte size;
} hword, HWORD, HEXAS_WORD, HexasWord, HWord;

typedef HEXAS_WORD* LPHWORD;

// Assembly is a data structure containing relevant infos about an assembly.
typedef struct HEXAS_ASSEMBLY
{
	// assembly name, should be the first cell in first line
	dstr* name;
	// size of the target architecture: could be 4 / 8 / 16 / 32 / 64 bits
	byte size;
	// linked table of all the assembly's instruction set
	table* instructions;
	// linked table of all the assembly's registries and flags.
	table* registries;
	// linked table of all the assembly's keywords (WORD, DWORD...)
	table* keywords;
} assembly, Assembly, ASSEMBLY, _asm_, ASM;

ASM asm_parse_csv(char* path);
// Constructs a HWORD from the content of a cell.
LPHWORD asm_build_hword(char* cell_content);
void asm_display(ASM* asm);
// returns a two-dimensional point with max possible opcode coordinates for rows and columns.
LPOINT asm_get_max_index(ASM* asm);
// returns the instruction at the given number.
// can be used to disassemble.
// uint64 it is the largest type available, so the opcode can be translated to whatever instruction up to x64 systems.
char* asm_get_instruction_name(ASM* asm, uint64 opcode);
LPHWORD asm_get_instruction(ASM* asm, uint64 opcode);
// returns the registry at the given number.
LPHWORD asm_get_registry(ASM* asm, uint64 regcode);
char* asm_get_registry_name(ASM* asm, uint64 regcode);
// Will look for an instruction with the same name then return the opcode.
uint64 asm_get_opcode(ASM* asm, char* instruction);
// Will look for a registry with the same name then return that identification code.
uint64 asm_get_regcode(ASM* asm, char* registry);
// Display an assembly table.
void asm_table_display(table* t);
void asm_table_display_line(table* t, uint64 index);
// when an operation on assembly fails, it returns this.
uint64 asm_error(ASM* asm);
