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
    table* asm_table = new(TABLE);
    table* reg_table = new(TABLE);
    table* kwo_table = new(TABLE);
    for (byte row = 0; row < asm_size; row++)
    {
        linked_list* ll = new(LINKED_LIST);
        linked_list* reg_line = new(LINKED_LIST);
        linked_list* kwo_line = new(LINKED_LIST);
        char** csv_line = str_split(lines[row], ',');
        for (byte col = 0; col < asm_size; col++)
        {
            char* _str = str_trim(csv_line[col]);
            byte n_subelements = str_count_char(_str, strlen(_str), ';');
            if (n_subelements)
            {
                char** cell = str_split(_str, ';');
                for (byte cell_element = 0; cell_element <= n_subelements; cell_element++)
                {
                    char* content = str_trim(cell[cell_element]);
                    // if it's the first element, it's an instruction
                    if (!cell_element)
                        linked_list_append(ll, strlen(content) ? str_to_dstr(content) : new(DSTR, "\0"));
                    else if(cell_element == 1)
                        // it's a registry, put it in the registry table. No need to put an empty instruction there,
                        // it has already been added (index 0).
                        linked_list_append(reg_line, strlen(content) ? str_to_dstr(content) : new(DSTR, "\0"));
                    else
                        linked_list_append(kwo_line, strlen(content) ? str_to_dstr(content) : new(DSTR, "\0"));
                }
                free(cell);
            }
            else
            {
                linked_list_append(ll, strlen(_str) ? str_to_dstr(_str) : new(DSTR, "\0"));
                // no registry detected, add an empty cell
                linked_list_append(reg_line, new(DSTR, "\0"));
                linked_list_append(kwo_line, new(DSTR, "\0"));
            }
        }
        delete_str_table(csv_line);
        table_add_row(asm_table, ll);
        table_add_row(reg_table, reg_line);
        table_add_row(kwo_table, kwo_line);
    }

    return (ASM){ .name = str_to_dstr(asm_name), .size = asm_size, .instructions = asm_table, .registries = reg_table, .keywords = kwo_table };
}

LPOINT asm_get_max_index(ASM* asm)
{
    return (LPOINT) { .x = TBL_F(columns_number, asm->instructions), .y = TBL_F(rows_number, asm->instructions) };
}


char* asm_get_instruction(ASM* asm, uint64 opcode)
{
    // getting the opcode size
    byte opcode_size = size_of(opcode);
    if (opcode_size > TBL_F(rows_number, asm->instructions) + TBL_F(columns_number, asm->instructions))
        // opcode too big for this instruction set; error
        return "ERR";
    // TODO
    // row is most significant half of opcode, column the less significant half
    size_t opcode_width = TBL_F(rows_number, asm->instructions);
    size_t 
        x = opcode & (mask(size_of(opcode_width))),
        y = (opcode & (mask(size_of(opcode_width)) << size_of(opcode_width))) >> size_of(opcode_width);
    return ((dstr*)TBL_F(get, asm->instructions, (LPOINT){x, y}))->str;
}

char* asm_get_registry(ASM* asm, uint64 regcode)
{
    // getting the opcode size
    byte opcode_size = size_of(regcode);
    if (opcode_size > TBL_F(rows_number, asm->registries) + TBL_F(columns_number, asm->registries))
        // opcode too big for this instruction set; error
        return "ERR";
    // TODO
    // row is most significant half of opcode, column the less significant half
    size_t opcode_width = TBL_F(rows_number, asm->registries);
    size_t
        x = regcode & (mask(size_of(opcode_width))),
        y = (regcode & (mask(size_of(opcode_width)) << size_of(opcode_width))) >> size_of(opcode_width);
    return ((dstr*)TBL_F(get, asm->registries, (LPOINT) { x, y }))->str;
}

uint64 asm_get_opcode(ASM* asm, char* instruction)
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

uint64 asm_get_regcode(ASM* asm, char* registry)
{
    size_t opcode;
    ll* row = LL_F(begin, asm->registries->rows);
    for (size_t irow = 0; irow < LL_F(size, row); ++irow, row = row->next)
    {
        ll* column = row->content;
        for (size_t icolumn = 0; icolumn < LL_F(size, column); ++icolumn, column = column->next)
        {
            opcode = irow << size_of(TBL_F(rows_number, asm->registries)) | icolumn;
            if (str_equals(registry, ((dstr*)LL_F(get, column, icolumn))->str))
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
    printf("Registries set:\n");
    table_print(asm->registries);
    printf("---------------------------\n");
    printf("Keywords set:\n");
    table_print(asm->keywords);
    printf("---------------------------\n");
}