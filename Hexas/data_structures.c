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

size_t mask(size_t bit_width)
{
	size_t _mask = 0;
	for (size_t i = 0; i < bit_width; ++i, _mask = (_mask << 1) + 1);
	return _mask;
}

void bprint(size_t n)
{
	size_t i = sizeof(n) * 8 - 2;
	printf("\n%llu in binary: ", n);
	for (; (1LL << i) > 0; --i)
		printf("%i", (1LL << i) & n ? 1 : 0);
	printf("\n");
}

byte hbyte_to_byte(HBYTE hb)
{
	return hb.b8 | hb.b7 | hb.b6 | hb.b5 | hb.b4 | hb.b3 | hb.b2 | hb.b1;
}

HBYTE byte_to_hbyte(byte b)
{
	return (HBYTE)
	{
		.b1 = b & 0b1,
		.b2 = b & 0b10,
		.b3 = b & 0b100,
		.b4 = b & 0b1000,
		.b5 = b & 0b10000,
		.b6 = b & 0b100000,
		.b7 = b & 0b1000000,
		.b8 = b & 0b10000000
	};
}

HBYTE and(HBYTE hb, byte b)
{
	return (HBYTE)
	{
		.b1 = hb.b1 & b,
		.b2 = hb.b2 & b,
		.b3 = hb.b3 & b,
		.b4 = hb.b4 & b,
		.b5 = hb.b5 & b,
		.b6 = hb.b6 & b,
		.b7 = hb.b7 & b,
		.b8 = hb.b8 & b
	};
}

HBYTE or(HBYTE hb, byte b)
{
	return (HBYTE)
	{
		.b1 = hb.b1 | b,
		.b2 = hb.b2 | b,
		.b3 = hb.b3 | b,
		.b4 = hb.b4 | b,
		.b5 = hb.b5 | b,
		.b6 = hb.b6 | b,
		.b7 = hb.b7 | b,
		.b8 = hb.b8 | b
	};
}

HBYTE xor(HBYTE hb, byte b)
{
	return (HBYTE)
	{
		.b1 = hb.b1 ^ b,
		.b2 = hb.b2 ^ b,
		.b3 = hb.b3 ^ b,
		.b4 = hb.b4 ^ b,
		.b5 = hb.b5 ^ b,
		.b6 = hb.b6 ^ b,
		.b7 = hb.b7 ^ b,
		.b8 = hb.b8 ^ b
	};
}

HBYTE lshift(HBYTE hb, byte b)
{
	for(byte i = 0; i < b; ++i)
	{
		hb.b1 = 0;
		hb.b2 = hb.b1;
		hb.b3 = hb.b2;
		hb.b4 = hb.b3;
		hb.b5 = hb.b4;
		hb.b6 = hb.b5;
		hb.b7 = hb.b6;
		hb.b8 = hb.b7;
	};
	return hb;
}

HBYTE rshift(HBYTE hb, byte b)
{
	for (byte i = 0; i < b; ++i)
	{
		hb.b1 = hb.b2;
		hb.b2 = hb.b3;
		hb.b3 = hb.b4;
		hb.b4 = hb.b5;
		hb.b5 = hb.b6;
		hb.b6 = hb.b7;
		hb.b7 = hb.b8;
		hb.b8 = hb.b8;
	};
	return hb;
}

uint64 n_decimals(int64 n)
{
	return llround(log10(n)) + 1;
}

HBYTE not(HBYTE hb, byte b)
{
	return (HBYTE)
	{
		.b1 = ~hb.b1,
		.b2 = ~hb.b2,
		.b3 = ~hb.b3,
		.b4 = ~hb.b4,
		.b5 = ~hb.b5,
		.b6 = ~hb.b6,
		.b7 = ~hb.b7,
		.b8 = ~hb.b8
	};
}
