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
	size_t max_row_size = TBL_F(width, t) + (4 * (TBL_F(columns_number, t) - 1));
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
		char* s = str_trim(((dstr*)_cc->content)->str);
		printf(s);
		size_t _len = strlen(s);
		if(_len)
			free(s);
		for(size_t ii = 0; ii < TABLE_FUNC(max_column_width, t, i) - _len; ++ii)
				printf(" ");
		printf(" | ");
	}
}

size_t TABLE_FUNC(max_column_width, table* t, size_t column_index)
{
	size_t max_row_size = 0;

	le* _cr = LL_F(begin, TBL_F(get_row, t, 0));
	for (size_t row = 0; row < LL_F(size, _cr); ++row)
	{
		_cr = LL_F(begin, TBL_F(get_row, t, row));
		le* _cc = LL_F(get_index, _cr, column_index);
		size_t row_size = strlen(((dstr*)_cc->content)->str);
		max_row_size = max_row_size < row_size ? row_size : max_row_size;
	}
	return max_row_size;
}

size_t TABLE_FUNC(width, table* t)
{
	ll* _cr = LL_F(begin, t->rows);
	size_t biggest_row = 0;
	for (size_t row = 0; row < LL_F(size, _cr); ++row, _cr = _cr->next)
	{
		size_t row_size = 0;
		le* _cc = _cr->content;
		for (; _cc->next; _cc = _cc->next)
			row_size += strlen(((dstr*)_cc->content)->str);
		row_size += strlen(((dstr*)_cc->content)->str);
		biggest_row = biggest_row > row_size ? biggest_row : row_size;
	}
	return biggest_row;
}

size_t TABLE_FUNC(columns_number, table* t)
{
	size_t max_n_cols = 0;
	ll* _cr = TBL_F(get_row, t, 0);
	for (size_t i = 0; i < LL_F(size, _cr); ++i, _cr = TBL_F(get_row, t, i))
		max_n_cols = max(max_n_cols, LL_F(size, _cr));
	return max_n_cols;
}

size_t TABLE_FUNC(rows_number, table* t)
{
	return LL_F(size, t->rows);
}

void TABLE_FUNC(free, table* t)
{
	ll* first_row = LL_F(begin, t->rows);
	ll* last_row = LL_F(end, t->rows);
	for (; first_row != last_row; first_row = first_row->next)
		LL_F(free, first_row);
	free(t);
}