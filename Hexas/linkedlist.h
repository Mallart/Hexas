#pragma once
#include <stdlib.h>
#include "str.h"

// Linked list function
#define LINKED_LIST_FUNC(func, ...) linked_list_##func(__VA_ARGS__)
// Linked list function
#define LL_F(fname, ...) LINKED_LIST_FUNC(fname, __VA_ARGS__)
typedef struct ll
{
	void* content;
	struct ll* previous;
	struct ll* next;
} linked_element, linked_list, le, ll;

// creates a new linked list
linked_list* LINKED_LIST_FUNC(new);
// adds an element after a linked list element
void LINKED_LIST_FUNC(add, linked_list* list, void* element);
// removes an element of a linked list then fixes the chain.
void LINKED_LIST_FUNC(remove, linked_element* list_element);
// inserts an element at the given index, starting at the list_begin element.
// if the given index is too long, the element is appended at the end of the list.
void LINKED_LIST_FUNC(insert, linked_list* list_begin, void* element, size_t index);
size_t LINKED_LIST_FUNC(size, linked_list* list_begin);
// adds an element at the end of a linked list
void LINKED_LIST_FUNC(append, linked_list* list_begin, void* element);
// appends n elements of an array one by one at the end of the linked list.
void LINKED_LIST_FUNC(append_bulk, linked_list* list, void* array, size_t n_elements);
// insert n elements of an array one by one at the index "index" of the linked list.
void LINKED_LIST_FUNC(insert_bulk, linked_list* list, void* array, size_t n_elements, size_t index);
// returns the last element of the linked list.
linked_element* LINKED_LIST_FUNC(begin, linked_list* list);
// returns the first element of the linked list.
linked_element* LINKED_LIST_FUNC(end, linked_list* list);
// Gets the content from a linked list at a given index.
void* LINKED_LIST_FUNC(get, linked_list* list, size_t index);
// Gets a linked element from a linked list at a given index.
void* LINKED_LIST_FUNC(get_index, linked_list* list, size_t index);
// frees the memory from all the list data.
void LINKED_LIST_FUNC(free, linked_list* list);