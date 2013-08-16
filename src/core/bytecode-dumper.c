#include <ljit/bytecode.h>
#include "internal.h"

static void _ljit_dump_value(FILE *f, ljit_value val)
{
    if (!val)
        return;

    if (val->is_tmp)
    {
        fprintf(f, "t%u", val->index);
        return;
    }

    switch (val->type)
    {
        case LJIT_VOID:
            break;
        case LJIT_UCHAR:
            fprintf(f, "%u", *((unsigned char*)val->data));
            break;
        case LJIT_USHORT:
            fprintf(f, "%u", *((unsigned short*)val->data));
            break;
        case LJIT_UINT:
            fprintf(f, "%u", *((unsigned int*)val->data));
            break;
    }
}

static void _ljit_dump_instr(FILE *f, ljit_bytecode *instr)
{
    switch (instr->type)
    {
        case GET_PARAM:
            _ljit_dump_value(f, instr->ret_val);
            fprintf(f, " = get_param ");
            _ljit_dump_value(f, instr->op1);
            break;
        case RETURN:
            fprintf(f, "return ");
            _ljit_dump_value(f, instr->op1);
            break;
        case MUL:
            _ljit_dump_value(f, instr->ret_val);
            fprintf(f, " = mul ");
            _ljit_dump_value(f, instr->op1);
            fprintf(f, " ");
            _ljit_dump_value(f, instr->op2);
            break;
    }
}

void ljit_bytecode_dumper(FILE *f, ljit_function *fun)
{
    struct _ljit_bytecode_list_element_s *instr = fun->bytecode->head;

    while (instr)
    {
        _ljit_dump_instr(f, instr->instr);
        instr = instr->next;
        fprintf(f, "\n");
    }
}
