#include "linkedlist.h"

linked_list* LINKED_LIST_FUNC(new)
{
	linked_list* ll = malloc(sizeof(linked_list));
	ll->content = 0,
	ll->next = 0;
	ll->previous = 0;
	return ll;
}

void LINKED_LIST_FUNC(add, linked_list* list, void* element)
{
	// if the current element doesn't have content, set it to something.
	if (!list->content)
	{
		list->content = element;
		return;
	}
	list->next = malloc(sizeof(linked_list));
	list->next->content = element;
	list->next->next = 0;
	list->next->previous = list;
}

void LINKED_LIST_FUNC(remove, linked_element* list_element)
{
	list_element->previous->next = list_element->next;
	if(list_element->next)
		list_element->next->previous = list_element->previous;
	if(list_element->content)
		free(list_element->content);
	free(list_element);
}

void LINKED_LIST_FUNC(insert, linked_list* list_begin, void* element, size_t index)
{
	linked_element* l_elem = list_begin;
	size_t i = 0;
	for (; i < index; ++i)
		if(l_elem->next)
			l_elem = l_elem->next;
	// if the index was too long, just add an element.
	if (i - 1 != index)
	{
		LINKED_LIST_FUNC(add, l_elem, element);
		return;
	}
	linked_element* new_elem = malloc(sizeof(linked_element));
	new_elem->previous = l_elem;
	new_elem->next = l_elem->next;
	l_elem->next->previous = new_elem;
	l_elem->next = new_elem;
}

size_t LINKED_LIST_FUNC(size, linked_list* list_begin)
{
	size_t i = 1 && list_begin;
	if (!i)
		return 0;
	linked_element* iterator = LL_F(begin, list_begin);
	for (; iterator->next; ++i)
		iterator = iterator->next;
	return i;
}

void LINKED_LIST_FUNC(append, linked_list* list_begin, void* element)
{
	le* begin = LL_F(begin, list_begin);
	if(!begin->content)
		LINKED_LIST_FUNC(add, begin, element);
	else
		LINKED_LIST_FUNC(add, LINKED_LIST_FUNC(end, list_begin), element);
}

void LINKED_LIST_FUNC(append_bulk, linked_list* list, void* array, size_t n_elements)
{
	for (size_t i = 0; i < n_elements; ++i)
		LL_F(append, list, (char*)(array) + i);
}

void LINKED_LIST_FUNC(insert_bulk, linked_list* list, void* array, size_t n_elements, size_t index)
{
	for (size_t i = 0; i < n_elements; ++i)
		LL_F(insert, list, (char*)(array) + i, index);
}

linked_element* LINKED_LIST_FUNC(end, linked_list* list_begin)
{
	linked_element* le = list_begin;
	for (; le->next; le = le->next);
	return le;
}

linked_element* LINKED_LIST_FUNC(begin, linked_list* list_begin)
{
	linked_element* fe = list_begin;
	for (; fe->previous; fe = fe->previous);
	return fe;
}

void* LINKED_LIST_FUNC(get, linked_list* list, size_t index)
{
	// linked list iterator
	le* _le = LL_F(begin, list);
	for (size_t i = 0; i < index && _le->next; ++i)
		_le = _le->next;
	return _le->content;
}

void LINKED_LIST_FUNC(free, linked_list* list)
{
	linked_element* fe = LINKED_LIST_FUNC(begin, list);
	linked_element* le = LINKED_LIST_FUNC(end, list);
	for (; fe != le; fe = fe->next)
	{
		if (fe->content)
		{
			free(fe->content);
			fe->content = 0;
		}
		if (fe->previous)
		{
			free(fe->previous);
			fe->previous = 0;
		}
	}
	free(le);
}