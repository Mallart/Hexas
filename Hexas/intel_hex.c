#include "formats.h"

typedef enum
{
	DATA_RECORD,
	END_OF_FILE_RECORD,
	EXTENDED_SEGMENT_ADDRESS_RECORD,
	START_SEGMENT_ADDRESS_RECORD,
	EXTENDED_LINEAR_ADDRESS_RECORD,
	START_LINEAR_ADDRESS_RECORD
};

char* intel_hex(char* byte_instructions)
{
	const expanded_length = strlen(":00000001FF") + 11 * str_count_char(byte_instructions, strlen(byte_instructions), '\n') + 1;
	char* buffer = malloc(sizeof(char) * (strlen(byte_instructions) + expanded_length));
	while (str_count_char(byte_instructions, strlen(byte_instructions), '\n'))
	{
		// parse each line of assembly
	}
	if (!buffer)
		return;
	// standard intel HEX end of file
	buffer[strlen(byte_instructions) + expanded_length - strlen(":00000001FF")] = ":00000001FF";
	buffer[strlen(byte_instructions) + expanded_length - 1] = 0;
	return buffer;
}