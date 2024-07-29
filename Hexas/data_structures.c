#include "data_structures.h"

size_t size_of(size_t n)
{
	size_t i = sizeof(n) * 8;
	for (; !(lround(pow(2, i)) & n); --i);
	return n ? i + 1 : 0;
}