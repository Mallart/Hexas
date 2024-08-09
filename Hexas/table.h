#pragma once
#include "linkedlist.h"

// Table function
#define TABLE_FUNC(fname, ...) table_##fname(__VA_ARGS__)
// Table function
#define TBL_F(fname, ...) TABLE_FUNC(fname, __VA_ARGS__)

// basically a linked list of linked lists.
typedef struct
{
	linked_list* rows;
} table, TABLE;

table* TABLE_FUNC(new);
table* TABLE_FUNC(add_row, table* t, linked_list* _ll);
linked_list* TABLE_FUNC(get_row, table* t, size_t index);
void* TABLE_FUNC(get, table* t, LPOINT coordinates);
void TABLE_FUNC(print, table* t);
void TABLE_FUNC(print_row, table* t, size_t index);
// in number of chars
size_t TABLE_FUNC(max_column_width, table* t, size_t colmun_index);
// in number of chars
size_t TABLE_FUNC(width, table* t);
size_t TABLE_FUNC(columns_number, table* t);
size_t TABLE_FUNC(rows_number, table* t);
// Returns 1 if the table is empty (not instantiated), 0 otherwise.
byte TABLE_FUNC(empty, table* t);
void TABLE_FUNC(free, table* t);

// returns all the table content as a single linked list, iterable.
linked_list* TABLE_FUNC(aslist, table* t);