#include "data_structures.h"

// Returns the size in bits of a number.
size_t size_of(size_t n)
{
	size_t i = sizeof(n) * 8 - 1;
	for (; !((1LL << i) & n); --i);
	return n ? i + 1 : 0;
}

size_t mask(size_t bit_width)
{
	return (1 << bit_width) - 1;
}

void bprint(size_t n)
{
	size_t i = sizeof(n) * 8 - 2;
	printf("\n%lu in binary: ", n);
	for (; (1LL << i) > 0; --i)
		printf("%i", (1LL << i) & n ? 1 : 0);
	printf("\n");
}
