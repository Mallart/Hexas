#include "data_structures.h"

size_t size_of(size_t n)
{
	size_t i = sizeof(n) * 8 - 1;
	for (; !((1LL << i) & n); --i);
	return n ? i + 1 : 0;
}

// deprecated because slower (size_of takes 3ms and this 7514ms for 1 million iterations)
size_t size_of_pow(size_t n)
{
	size_t i = sizeof(n) * 8;
	for (; !(lround(powl(2, i)) & n); --i);
	return n ? i + 1 : 0;
}

void bprint(size_t n)
{
	size_t i = sizeof(n) * 8 - 2;
	printf("\n%llu in binary: ", n);
	for (; (1LL << i) > 0; --i)
		printf("%i", (1LL << i) & n ? 1 : 0);
	printf("\n");
}


