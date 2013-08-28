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
        case LJIT_LABEL:
            fprintf(f, "l%u", ((ljit_label*)(val->data))->index);
            break;
        case LJIT_VOID:
            break;
        case LJIT_CHAR:
            fprintf(f, "%i", *((char*)val->data));
            break;
        case LJIT_SHORT:
            fprintf(f, "%i", *((short*)val->data));
            break;
        case LJIT_INT:
            fprintf(f, "%i", *((int*)val->data));
            break;
        case LJIT_LONG:
            fprintf(f, "%li", *((long*)val->data));
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
        case LJIT_ULONG:
            fprintf(f, "%lu", *((unsigned long*)val->data));
            break;
    }
}

static void _ljit_dump_operation(FILE *f, ljit_bytecode *instr, char *name)
{
    _ljit_dump_value(f, instr->ret_val);
    fprintf(f, " = %s ", name);
    _ljit_dump_value(f, instr->op1);
    fprintf(f, " ");
    _ljit_dump_value(f, instr->op2);
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
        case LABEL:
            _ljit_dump_value(f, instr->op1);
            fprintf(f, ":");
            return;
        case JUMP:
            fprintf(f, "jmp ");
            _ljit_dump_value(f, instr->op1);
            break;
        case JUMP_IF:
            fprintf(f, "jmp_if ");
            _ljit_dump_value(f, instr->op1);
            fprintf(f, " ");
            _ljit_dump_value(f, instr->op2);
            break;
        case JUMP_IF_NOT:
            fprintf(f, "jmp_if_not ");
            _ljit_dump_value(f, instr->op1);
            fprintf(f, " ");
            _ljit_dump_value(f, instr->op2);
            break;
        case ADD:
            _ljit_dump_operation(f, instr, "add");
            break;
        case SUB:
            _ljit_dump_operation(f, instr, "sub");
            break;
        case MUL:
            _ljit_dump_operation(f, instr, "mul");
            break;
        case DIV:
            _ljit_dump_operation(f, instr, "div");
            break;
    }
}

void ljit_bytecode_dumper(FILE *f, ljit_function *fun)
{
    ljit_block *b = fun->start_blk;

    /* Display all block contained by the function */
    while (b)
    {
        struct _ljit_bytecode_list_element_s *instr = b->instrs->head;

        /* Display all the instructions of the block */
        while (instr)
        {
            /* Display the current instruction */
            _ljit_dump_instr(f, instr->instr);

            /* Skip to the next instruction */
            instr = instr->next;

            fprintf(f, "\n");
        }

        /* Skip to the next block */
        b = b->next;

        printf(";******\n");
    }
}
