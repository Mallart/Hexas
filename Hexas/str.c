#include "str.h"

dstr* DSTR_FUNC(new, char* content)
{
	dstr* r = malloc(sizeof(dstr));
	if (!r)
		return 0;
	r->str = (char*)content;
}

void DSTR_FUNC(set, dstr* str, char* content)
{
	str->str = (char*)content;
}

void DSTR_FUNC(free, dstr* str)
{
	free(str->str);
	free(str);
}

char* str_remove_char(char* str, char c)
{
	size_t len = strlen(str);
	char* _s = malloc(sizeof(char) * (len + 1));
	if (!_s)
		return 0;
	char found = 0;
	size_t i = 0;
	for (; i < len; ++i)
		if (str[i] == c)
			found = 1;
		else
			_s[i] = str[i - found];
	_s[len - found] = '\0';
	return _s;
}

void str_ptr_remove_char(char* str, char c)
{
	size_t c_index = 0, _strlen = strlen(str);
	for (; c != str[c_index] && c <= _strlen; c_index++);
	for (size_t i = c_index; i < _strlen - 1; i++)
		str[i] = str[i + 1];
}

char* byte_bin_to_hex(char byte)
{
	char msd = (byte & 0xf0) >> 4;
	char lsd = byte & 0xf;
	char* hex = malloc(sizeof(char) * 3);
	if (!hex)
		return 0;
	hex[0] = msd < 10 ? msd + '0' : msd + 'A' - 10;
	hex[1] = lsd < 10 ? lsd + '0' : lsd + 'A' - 10;
	hex[2] = 0;
	return hex;
}

char byte_hex_to_bin(char* hex)
{
	if (strlen(hex) < 2)
		return hex[0] - (hex[0] < 'A' ? '0' : 'A' - 10);
	return ((hex[0] - (hex[0] < 'A' ? '0' : 'A' - 10)) << 4) + ((hex[1] - (hex[1] < 'A' ? '0' : 'A' - 10)));
}

char* bin_to_hex(char* bin_data, size_t count)
{
	// each byte is two hex characters
	char* s = malloc(sizeof(char) * (count * 2 + 1));
	if (!s)
		return 0;
	// TODO
	for (size_t i = 0; i < count; i+=2)
	{
		char* value = byte_bin_to_hex(bin_data[lround((i / 2.0))]);
		s[i] = value[0];
		s[i + 1] = value[1];
	}
	s[count] = 0;
	return s;
}

char* hex_to_bin(char* hex_values, size_t count)
{
	long _strcount = lround(count / 2.0);
	char* bin = malloc(sizeof(char) * (_strcount + 1));
	if (!bin)
		return 0;
	for (size_t i = 0; i < _strcount; ++i)
		bin[i] = byte_hex_to_bin(hex_values + i * 2);
	return bin;
}