#include "gui.h"
#include "assembly.h"
void main(int argc, char** argv)
{

	linked_list* _ll = new(LINKED_LIST);
	// note: cannot use const pointers and free them
	dstr* firstStr = new(DSTR, "hey hey");
	dstr* secondStr = new(DSTR, "hello, world !\n");
	LINKED_LIST_FUNC(append, _ll, firstStr);
	LINKED_LIST_FUNC(append, _ll, secondStr);
	printf(((dstr*)LL_F(get, _ll, 0))->str);

	table* testT = new(TABLE);
	TBL_F(add_row, testT, _ll);
	ll* first_row = TBL_F(get_row, testT, 0);
	TBL_F(print, testT);
	printf("\nbyte F2: %s", byte_bin_to_hex('\xf2'));
	LINKED_LIST_FUNC(free, _ll);
	printf("\nFA in int: %i", byte_hex_to_bin("FA"));
	exit(0);
}