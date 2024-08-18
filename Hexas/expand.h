#pragma once
#include "data_structures.h"
#include "str.h"

// A word that expands to another / several others.
typedef struct HEXAS_EXPAND
{
	// the word that will be expanded
	char* word;
	// what it will expand to. is another string (char*) if reexpand is 0, otherwise will expand
	// to another expand.
	void* result;
	// just a boolean, if 0 it will expand to a simple string, and if not, will expand to
	// another expand's expand
	byte reexpand : 1;
	// macro number of arguments
	byte n_args;
	// macro arguments
	char** args;
} expand, hexpand;

char* exp_expand(expand* exp);