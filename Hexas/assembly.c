#include "assembly.h"

ASM asm_parse_csv(char* path)
{
    ASM asm;
    asm.name = str_to_dstr(str_substr(path, str_find_last_char(path, '.'), 0));
    char* file_content = read_all_file(path);
    if (!file_content)
        return;
    // parsing csv content

    char** lines = str_split(file_content, '\n');
    asm.size = str_table_size(lines);
    // parsing a line of CSV
    asm.instructions = table_new();
    for (byte row = 0; row < asm.size; row++)
    {
        linked_list* ll = linked_list_new();
        char** csv_line = str_split(lines[row], ';');
        for (byte col = 0; col < asm.size; col++)
            linked_list_append(ll, csv_line[col]);
        delete_str_table(csv_line);
        table_add_row(asm.instructions, ll);
    }


    return asm;
}
