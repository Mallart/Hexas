#pragma once
#include "str.h"
#include "linkedlist.h"
#include "table.h"

typedef char byte;

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