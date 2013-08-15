#include "bytecode.h"

static ljit_bytecode *ljit_new_bytecode(ljit_bytecode_type type,
                                        ljit_value op1,
                                        ljit_value op2)
{
    ljit_bytecode *instr = NULL;

    if ((instr = malloc(sizeof(ljit_bytecode))) == NULL)
        return NULL;

    instr->type = type;
    instr->op1 = op1;
    instr->op2 = op2;

    return instr;
}
