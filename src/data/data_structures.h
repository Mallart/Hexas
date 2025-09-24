#pragma once
#include <stdint.h>
#include "str.h"
#include "../error/enum.h"

typedef uint8_t byte;
// #region LEGACY
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

// #region STRUCTURES

typedef struct
{
	int64_t x;
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

// #region MATHS

// return the bit width (number of bits to write) n.
size_t size_of(size_t n);
// more reliable than size_of but slower.
size_t size_of_pow(size_t n);
// returns a mask with given bit width
size_t mask(size_t bit_width);

// prints any number in binary.
void bprint(size_t n);

// returns the biggest number between a and b.
static inline int64_t imax(int64_t a, int64_t b)
{
	return (a < b) ? b : a;
}