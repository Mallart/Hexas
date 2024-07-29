#pragma once
#include "str.h"
#include "linkedlist.h"
#include "table.h"

typedef unsigned char byte;
typedef short int16;
typedef int int32;
#ifdef _WIN32
typedef long long int64;
#else
typedef long int64;
#endif


typedef struct
{
	size_t x;
	size_t y;
} upoint, uPoint, UPOINT, upoint2;

typedef struct
{
	long x;
	long y;
} lpoint, lPoint, LPOINT, lpoint2;

typedef struct
{
	float x;
	float y;
} fpoint, fPoint, FPOINT, fpoint2;

typedef struct
{
	double x;
	double y;
} dpoint, dPoint, DPOINT, dpoint2;

// return the bit width (number of bits to write) n.
size_t size_of(size_t n);
// more reliable than size_of but slower.
size_t size_of_pow(size_t n);

// prints any number in binary.
void bprint(size_t n);