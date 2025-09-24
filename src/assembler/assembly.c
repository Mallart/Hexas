#include "assembly.h"
#include "../data/files.h"
#include <stdlib.h>

ASM asm_parse_csv(char* path)
{
    size_t name_begin = str_find_last_char(path, '/') + 1;
    char* asm_name = str_substr(path, name_begin, str_find_last_char(path, '.') - name_begin);
    char* file_content = read_all_file(path);
    if (!file_content)
        exit_error(EXCEPTION_FILE_NOT_FOUND, path);
    // parsing csv content

    char** lines = str_split(file_content, '\n');
    byte asm_size = str_table_size(lines);
    // parsing a line of CSV
    table* asm_table = table_new();
    for (byte row = 0; row < asm_size; row++)
    {
        linked_list* ll = linked_list_new();
        char** csv_line = str_split(lines[row], ';');
        for (byte col = 0; col < asm_size; col++)
        {
            char* _str = str_trim(csv_line[col]);
            linked_list_append(ll, strlen(_str) ? _str : allocated_string("\0"));
        }
        delete_str_table(csv_line);
        table_add_row(asm_table, ll);
    }

    return (ASM){ .name = asm_name, .size = asm_size, .instructions = asm_table };
}

LPOINT asm_get_max_index(ASM* _asm)
{
    return (LPOINT) { .x = TBL_F(columns_number, _asm->instructions), .y = TBL_F(rows_number, _asm->instructions) };
}


char* asm_get_instruction(ASM* _asm, int64 opcode)
{
    // getting the opcode size
    byte opcode_size = size_of(opcode);
    if (opcode_size > TBL_F(rows_number, _asm->instructions) + TBL_F(columns_number, _asm->instructions))
        // opcode too big for this instruction set; error
        return "ERR";
    // TODO
    // row is most significant half of opcode, column the less significant half
    size_t opcode_width = TBL_F(rows_number, _asm->instructions);
    size_t 
        x = opcode & (mask(size_of(opcode_width))),
        y = (opcode & (mask(size_of(opcode_width)) << size_of(opcode_width))) >> size_of(opcode_width);
    return TBL_F(get, _asm->instructions, (LPOINT){x, y});
}

int64 asm_get_opcode(ASM* _asm, char* instruction)
{
    size_t opcode;
    ll* row = LL_F(begin, _asm->instructions->rows);
    for (size_t irow = 0; irow < LL_F(size, row); ++irow, row = row->next)
    {
        ll* column = row->content;
        for (size_t icolumn = 0; icolumn < LL_F(size, column); ++icolumn, column = column->next)
        {
            opcode = irow << size_of(TBL_F(rows_number, _asm->instructions)) | icolumn;
            if (str_equals(instruction, LL_F(get, column, icolumn)))
                return opcode;
        }
    }
    return 0;
}

void asm_display(ASM* _asm, FILE* stream)
{
    fprintf(stream, "-- Assembly info display --\n");
    fprintf(stream, "Name: \t\t%s\n", _asm->name);
    fprintf(stream, "Architecture: \t%i bits (x%i)\n", _asm->size, _asm->size);
    fprintf(stream, "Instructions set:\n");
    table_print(_asm->instructions, stream);
    fprintf(stream, "---------------------------\n");
}