#pragma once
#include "table.h"
// TODO: assembly data structure
// TODO: CSV files reading for modular assembly conversion

// Assembly is a data structure containing relevant infos about an assembly.
typedef struct
{
	dstr name;
	table instructions;
} assembly, ASSEMBLY, _asm_, ASM;