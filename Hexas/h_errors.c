#include "h_errors.h"

char* error_name(long long n)
{
	char const* const errors[64] = {
		"NO_ERROR",
		"MEMORY_ALLOCATION_NOT_ENOUGH_SPACE",
		"MEMORY_DEALLOCATION_EMPTY_SPACE",
		"MEMORY_DEREFERENCED_POINTER_USED",
		"MEMORY_OUT_OF_BOUNDS",
		"COMPILER_UNKNOWN_ARGUMENT",
		"COMPILER_NOT_ENOUGH_ARGUMENTS",
		"PARSER_INVALID_OPERAND",
		"PARSER_UNKOWN_INSTRUCTION",
		"PARSER_SYNTAX_ERROR",
	};
	return errors[n];
}

void exit_with_error(long long n)
{
	printf("A fatal error has occured and Hexas has been stopped.\nError code: %i\n Error name: %s\n"
		, n, error_name(n));
	exit(n);
}

void exit_with_error_message(long long n, char* msg)
{
	printf("A fatal error has occured and Hexas has been stopped.\nError code: %i\n Error name: %s\n"
		, n, msg);
	exit(n);
}