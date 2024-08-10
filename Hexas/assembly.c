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
        // instructions line
        linked_list* asm_line = new(LINKED_LIST);
        // registries line
        linked_list* reg_line = new(LINKED_LIST);
        // keywords line
        linked_list* kwo_line = new(LINKED_LIST);
        char** csv_line = str_split(lines[row], HEXAS_ENTRY_SEPARATOR);
        for (byte col = 0; col < asm_size; col++)
        {
            char* _str = str_trim(csv_line[col]);
            byte n_subelements = str_count_char(_str, strlen(_str), HEXAS_KEYWORD_SEPARATOR);
            if (n_subelements)
            {
                char** cell = str_split(_str, HEXAS_KEYWORD_SEPARATOR);
                for (byte cell_element = 0; cell_element <= n_subelements; cell_element++)
                {
                    char* content = str_trim(cell[cell_element]);
                    linked_list* list;
                    // if it's the first element, it's an instruction
                    if (!cell_element)
                        list = asm_line;
                    else if (cell_element == 1)
                    // it's a registry, put it in the registry table. No need to put an empty instruction there,
                    // it has already been added (index 0).
                        list = reg_line;
                    else
                        list = kwo_line;
                    linked_list_append(list, asm_build_hword(content));
                }
                free(cell);
            }
            else
            {
                linked_list_append(asm_line, asm_build_hword(_str));
                // no registry detected, add an empty cell
                linked_list_append(reg_line, asm_build_hword("\0"));
                linked_list_append(kwo_line, asm_build_hword("\0"));
            }
        }
        delete_str_table(csv_line);
        table_add_row(asm_table, asm_line);
        table_add_row(reg_table, reg_line);
        table_add_row(kwo_table, kwo_line);
    }

    return (ASM){ 
        .name = str_to_dstr(asm_name),
        .size = asm_size, 
        .instructions = asm_table,
        .registries = reg_table, 
        .keywords = kwo_table
    };
}

LPHWORD asm_build_hword(char* cell_content)
{
    char** cell = str_split(cell_content, HEXAS_WORD_SIZE_INDICATOR);
    LPHWORD _hword = malloc(sizeof(HWORD));
    if (!_hword)
        throw(MEMORY_ALLOCATION_NOT_ENOUGH_SPACE);
    _hword->name = strlen(cell[HEXAS_CELL_NAME]) ? str_to_dstr(cell[HEXAS_CELL_NAME]) : new(DSTR, "\0");
    _hword->size = str_table_size(cell) > 1 ? atoi(cell[HEXAS_CELL_SIZE]) : 0;
    free(cell);
    return _hword;
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
    return ((LPHWORD)TBL_F(get, asm->instructions, (LPOINT){x, y}))->name->str;
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
    return ((LPHWORD)TBL_F(get, asm->registries, (LPOINT) { x, y }))->name->str;
}

uint64 asm_get_opcode(ASM* asm, char* instruction)
{
    ll* row = LL_F(begin, asm->instructions->rows);
    for (size_t irow = 0; irow < LL_F(size, row); ++irow, row = row->next)
    {
        ll* column = LL_F(begin, row->content);
        for (size_t icolumn = 0; icolumn < LL_F(size, column); ++icolumn, column = column->next)
        {
            if (str_equals(instruction, ((LPHWORD)LL_F(get, column, icolumn))->name->str))
                // this is the opcode
                return irow << size_of(TBL_F(rows_number, asm->instructions)) | icolumn;
        }
    }
    return 0;
}

uint64 asm_get_regcode(ASM* asm, char* registry)
{
    ll* row = LL_F(begin, asm->registries->rows);
    for (size_t irow = 0; irow < LL_F(size, row); ++irow, row = row->next)
    {
        ll* column = row->content;
        for (size_t icolumn = 0; icolumn < LL_F(size, column); ++icolumn, column = column->next)
        {
            if (str_equals(registry, ((LPHWORD)LL_F(get, column, icolumn))->name->str))
                return irow << size_of(TBL_F(rows_number, asm->registries)) | icolumn;
        }
    }
    return 0;
}

void asm_table_display(table* t)
{
    printf("\n");
    if (TABLE_FUNC(empty, t))
    {
        printf("The given table is empty.\n");
        return;
    }
    // current row
    le* _cr = LL_F(begin, t->rows);
    size_t max_row_size = TBL_F(width, t) + (4 * (TBL_F(columns_number, t) - 1));
    for (size_t i = 0; i < max_row_size; ++i)
        printf("-");
    printf("\n");
    for (size_t i = 0; i < LL_F(size, _cr); _cr = _cr->next, i++)
    {
        asm_table_display_line(t, i);
        printf("\n");
    }
    for (size_t i = 0; i < max_row_size; ++i)
        printf("-");
    printf("\n");
}


void asm_table_display_line(table* t, uint64 index)
{
    // current cell
    le* _cc = LL_F(begin, TBL_F(get_row, t, index));
    // ending cell
    le* _ec = LL_F(end, TBL_F(get_row, t, index));
    size_t ll_size = LL_F(size, _cc);
    printf("| ");
    for (size_t i = 0; i < ll_size; _cc = _cc->next, i++)
    {
        dstr* _str = ((LPHWORD)_cc->content)->name;
        dstr_print(_str, 0);
        if(((LPHWORD)_cc->content)->size)
            printf(" :%i", ((LPHWORD)_cc->content)->size);
        char* s = str_trim(_str->str);
        int64 _len = dstr_len(_str) + (((LPHWORD)_cc->content)->size ? 3 : 0);
        for (int64 ii = 0; ii < (int64)TABLE_FUNC(max_column_width, t, i) - _len; ++ii)
            printf(" ");
        printf(" | ");
    }
}

void asm_display(ASM* asm)
{
    printf("-- Assembly info display --\n");
    printf("Name: \t\t%s\n", asm->name->str);
    printf("Architecture: \t%i bits (x%i)\n", asm->size, asm->size);
    printf("Instructions set:\n");
    asm_table_display(asm->instructions);
    printf("---------------------------\n");
    printf("Registries set:\n");
    asm_table_display(asm->registries);
    printf("---------------------------\n");
    printf("Keywords set:\n");
    asm_table_display(asm->keywords);
    printf("---------------------------\n");
}
