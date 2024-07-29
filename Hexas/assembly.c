#include "assembly.h"

ASM asm_parse_csv(char* path)
{
    size_t name_begin = 0;
    char* asm_name = str_substr(path, name_begin = str_find_last_char(path, '/') + 1, str_find_last_char(path, '.') - name_begin);
    char* file_content = read_all_file(path);
    if (!file_content)
        return;
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
            linked_list_append(ll, strlen(_str) ? str_to_dstr(_str) : new(DSTR, "\0"));
        }
        delete_str_table(csv_line);
        table_add_row(asm_table, ll);
    }

    return (ASM){ .name = str_to_dstr(asm_name), .size = asm_size, .instructions = asm_table };
}

LPOINT asm_get_max_index(ASM* asm)
{
    return (LPOINT) { .x = TBL_F(columns_number, asm->instructions), .y = TBL_F(rows_number, asm->instructions) };
}


char* asm_get_instruction(ASM* asm, int64 opcode)
{
    // TODO
    // getting the opcode size
    byte opcode_size = 0;

    if (opcode | 0xff0000000000)
    return 0;
}

int64 asm_get_opcode(ASM* asm, char* instruction)
{
    size_t opcode;
    ll* row = LL_F(begin, asm->instructions->rows);
    for (size_t irow = 0; irow < LL_F(size, row); ++irow, row = row->next)
    {
        ll* column = row->content;
        for (size_t icolumn = 0; icolumn < LL_F(size, column); ++icolumn, column = column->next)
        {
            opcode = irow << size_of(TBL_F(rows_number, asm->instructions)) | icolumn;
            if (str_equals(instruction, ((dstr*)LL_F(get, column, icolumn))->str))
                return opcode;
        }
    }
    return 0;
}

void asm_display(ASM* asm)
{
    printf("-- Assembly info display --\n");
    printf("Name: \t\t%s\n", asm->name->str);
    printf("Architecture: \t%i bits (x%i)\n", asm->size, asm->size);
    printf("Instructions set:\n");
    table_print(asm->instructions);
    printf("---------------------------\n");
}