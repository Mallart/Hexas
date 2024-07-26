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

char** str_split(char* str, char delimiter)
{
	size_t _strlen = strlen(str);
	size_t n_delims = 0;
	for (size_t i = 0; i < _strlen; ++i)
		if (str[i] == delimiter)
			n_delims++;
	char** _array = malloc(sizeof(char*) * (n_delims + 2));
	if (!_array)
		return 0;
	size_t alloc_number = 0;
	for (size_t i = 0; alloc_number < n_delims + 1; i = str_find_char(str, delimiter) + 1, alloc_number++, str += i)
	{
		size_t str_size = str_find_char(str, delimiter);
		_array[alloc_number] = malloc(sizeof(char) * (str_size + 1));
		for (size_t ii = 0; ii < str_size; ++ii)
			_array[alloc_number][ii] = str[ii];
		_array[alloc_number][str_size] = 0;
	}
	_array[n_delims + 1] = 0;
	return _array;
}

size_t str_table_size(char** strtable)
{
	size_t i = 0;
	for (; strtable[i]; ++i);
	return i;
}

void delete_str_table(char** strtable)
{
	for (size_t i = 0; i < str_table_size(strtable); ++i)
		free(strtable[i]);
	free(strtable);
}

dstr* str_to_dstr(char* str)
{
	dstr* d = dstr_new(str);
	free(str);
	return d;
}

char* str_substr(char* str, size_t origin, size_t count)
{
	if (!count)
		count = strlen(str) - origin;
	char* _str = malloc(sizeof(char) * (count + 1));
	str += origin;
	if (!str || !_str)
		return 0;
	for (size_t i = 0; i < count; ++i)
		_str[i] = str[i];
	_str[count] = '\0';
	return _str;
}

size_t str_find_char(char* str, char c)
{
	size_t i = 0;
	for (; str[i]; i++)
		if (str[i] == c || str[i] == 0)
			return i;
	return i;
}

size_t str_find_last_char(char* str, char c)
{
	size_t i = strlen(str);
	for (; i; i--)
		if (str[i] == c)
			return i;
	return i;
}

char* byte_bin_to_hex(unsigned char byte)
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
	for (size_t i = 0; i < count * 2; i+=2)
	{
		char* value = byte_bin_to_hex(bin_data[lround((i / 2.0))]);
		s[i] = value[0];
		s[i + 1] = value[1];
	}
	s[count * 2] = 0;
	return s;
}

char* hex_to_bin(char* hex_values, size_t count)
{
	long _strcount = count;
	char* bin = malloc(sizeof(char) * (_strcount + 1));
	if (!bin)
		return 0;
	for (size_t i = 0; i < _strcount; ++i)
		bin[i] = byte_hex_to_bin(hex_values + i * 2);
	bin[_strcount] = 0;
	return bin;
}

// returns 0 if a character is alphanumeric, otherwise returns 1
char prv_is_blank(char c)
{
	const char* blank_characters = " \n\t\r\0";
	for (size_t _c = 0; blank_characters[_c]; ++_c)
		if (c == blank_characters[_c])
			return 1;
	return 0;
}

char* str_trim(char* str)
{
	// TODO:make this work for the end of the string
	size_t begin = 0;
	for (; str[begin] && prv_is_blank(str[begin]); ++begin);
	str += begin;
	size_t end = strlen(str);
	for (; end > begin && prv_is_blank(str[end]); --end);
	str[end] = 0;
	return str;
}
