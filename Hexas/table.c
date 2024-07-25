#include "table.h"

table* TABLE_FUNC(new)
{
	table* t = malloc(sizeof(table));
	if(t)
		t->rows = new(LINKED_LIST);
	return t;
}

table* TABLE_FUNC(add_row, table* t, linked_list* _ll)
{
	LINKED_LIST_FUNC(append, t->rows, _ll);
}

linked_list* TABLE_FUNC(get_row, table* t, size_t index)
{
	return (linked_list*)LINKED_LIST_FUNC(get, t->rows, index);
}

void TABLE_FUNC(print, table* t)
{
	printf("\n");
	// current row
	le* _cr = LL_F(begin, t->rows);
	size_t max_row_size = TBL_F(max_width, t);
	for (size_t i = 0;i < max_row_size; ++i)
		printf("-");
	printf("\n");
	for (size_t i = 0; i < LL_F(size, _cr); _cr = _cr->next, i++)
	{
		TBL_F(print_row, t, i);
		printf("\n");
	}
	for (size_t i = 0; i < max_row_size; ++i)
		printf("-");
	printf("\n");
}

void TABLE_FUNC(print_row, table* t, size_t index)
{
	// current cell
	le* _cc = LL_F(begin, TBL_F(get_row, t, index));
	// ending cell
	le* _ec = LL_F(end, TBL_F(get_row, t, index));
	size_t ll_size = LL_F(size, _cc);
	printf("| ");
	for (size_t i = 0; i < ll_size; _cc = _cc->next, i++)
	{
		char* s = str_remove_char(((dstr*)_cc->content)->str, '\n');
		printf(s);
		free(s);
		printf(" | ");
	}
}

size_t TABLE_FUNC(max_width, table* t)
{
	le* _cr = LL_F(begin, t->rows);
	size_t max_row_size = 0;
	for (size_t i = 0; i < LL_F(size, _cr); _cr = _cr->next, i++)
	{
		// current cell of row
		le* _cc = LL_F(begin, _cr);
		// end cell of row
		le* _ec = LL_F(end, _cr);
		max_row_size = max_row_size > strlen(((dstr*)_cc->content)->str) ? max_row_size : strlen(((dstr*)_cc->content)->str);
		for (; _cc != _ec; _cc = _cc->next)
			max_row_size = max_row_size > strlen(((dstr*)_cc->content)->str) ? max_row_size : strlen(((dstr*)_cc->content)->str);
	}
	return max_row_size;
}

void TABLE_FUNC(free, table* t)
{
	ll* first_row = LL_F(begin, t->rows);
	ll* last_row = LL_F(end, t->rows);
	for (; first_row != last_row; first_row = first_row->next)
		LL_F(free, first_row);
	free(t);
}