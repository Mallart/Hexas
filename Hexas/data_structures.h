#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef unsigned char byte;
typedef unsigned char BYTE;
typedef unsigned char uint8;
typedef short int16;
typedef int int32;
#ifdef _WIN32
typedef long long int64;
typedef unsigned long long uint64;
typedef unsigned long long QWORD;
#else
typedef long int64;
typedef unsigned long uint64;
typedef unsigned long QWORD;
#endif
typedef unsigned short WORD;
typedef unsigned short uint16;
typedef unsigned int DWORD;
typedef unsigned int uint32;

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
// returns a mask with given bit width
size_t mask(size_t bit_width);

// prints any number in binary.
void bprint(size_t n);