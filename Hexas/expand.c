#include "expand.h"
char* exp_expand(expand* exp)
{
	expand* temp_exp = exp;
	byte temp_nargs = exp->n_args;
	for (; temp_exp->reexpand;)
	{
		temp_nargs = temp_exp->n_args;
		// current macro's args
		char** temp_args = temp_exp->args;
		// call next macro
		temp_exp = (expand*)temp_exp->result;
		// next macro arguments
		char** args = temp_exp->args;
		// array of previous and called combined args
		char** next_args = malloc(sizeof(char*) * (temp_exp->n_args + temp_nargs));
		if (!next_args)
			throw(MEMORY_ALLOCATION_NOT_ENOUGH_SPACE);
		// calling macro's args are appended after called macro's one.

		// add called arguments first
		for (byte i = 0; i < temp_exp->n_args; ++i)
		{
			next_args[i] = malloc(sizeof(char) * (strlen(args[i])));
			if (!next_args[i])
				throw(MEMORY_ALLOCATION_NOT_ENOUGH_SPACE);
			next_args[i] = str_cpy(next_args[i], args[i], sizeof(char) * strlen(args[i]));
		}

		// append calling macro's args
		for (byte i = 0; i < temp_nargs; ++i)
		{
			char* arg = temp_args[i];
			next_args[i + temp_exp->n_args] = malloc(sizeof(char) * (strlen(arg)));
			if (!next_args[i + temp_exp->n_args])
				throw(MEMORY_ALLOCATION_NOT_ENOUGH_SPACE);
			next_args[i + temp_exp->n_args] = str_cpy(next_args[i + temp_exp->n_args], temp_args[i], sizeof(char) * strlen(temp_args[i]));
		}
		temp_exp->args = next_args;
		temp_exp->n_args += temp_nargs;
	}
	char* result = (char*)temp_exp->result;
	char* old_result = 0;
	for (byte i = 0; i < temp_exp->n_args; i++)
	{
		uint64 number_place = str_find_char(result, '%') + 1;
		uint64 number = atoll(result + number_place);
		// replace the number + '%' by the corresponding argument.
		// %1 should be the first argument.
		result = str_replace(result, number_place - 1, n_decimals(number) + 1, temp_exp->args[number - 1]);
		if(old_result)
			free(old_result);
		old_result = result;
	}
	return result;
}