#include "internal.h"

ljit_value _ljit_new_temporary(ljit_function *fun, ljit_types type)
{
    ljit_value val = NULL;

    if ((val = ljit_new_value(type)) == NULL)
        return NULL;

    val->is_tmp = 1;
    val->index = fun->uniq_index++;

    return val;
}

void _ljit_free_bytecode(ljit_bytecode *instr)
{
    if (!instr)
        return;

    ljit_free_value(instr->op1);
    ljit_free_value(instr->op2);
    ljit_free_value(instr->ret_val);

    free(instr);
}
