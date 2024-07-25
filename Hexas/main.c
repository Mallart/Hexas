// delete the following line to remove all debug infos and tests.
#define DEBUG
#include "gui.h"
#include "assembly.h"

#ifdef DEBUG
void tests();
#endif
void main(int argc, char** argv)
{
	tests();
}

#ifdef DEBUG
void tests()
{

	linked_list* _ll = new(LINKED_LIST);
	// note: cannot use const pointers and free them (obvious but we don't know)
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
	printf("\nbytes F2F403: %s", bin_to_hex("\xf2\xf4\x03", 3));
	LINKED_LIST_FUNC(free, _ll);
	printf("\nFA in int: %i", byte_hex_to_bin("FA"));
	printf("\n25300F in int: %i", hex_to_bin("25300F", 3)[2]);
	printf("\nA5 in int: %i", byte_hex_to_bin("A5"));
	printf("\n5A in int: %i\n\n", byte_hex_to_bin("5A"));
	char* csv_example = "this;is;an;example;please;work;properly";
	char** table = str_split(csv_example, ';');
	for (size_t i = 0; table[i]; ++i)
		printf("Element of test CSV table %u: %s\n", i, table[i]);
	exit(0);
}
#endif