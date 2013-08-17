#include <ljit/bytecode.h>
#include "internal.h"

/* FIXME : Type check */
static ljit_value _ljit_build_operation(ljit_function *fun,
                                        ljit_value op1,
                                        ljit_value op2,
                                        ljit_bytecode_type type)
{
    ljit_value ret_val = NULL;
    ljit_bytecode *instr = NULL;

    /* Build the instruction with the 2 operands */
    if ((instr = _ljit_new_bytecode(type, op1, op2)) == NULL)
        return NULL;

    /* Allocate new temporary that hold the return value */
    if ((ret_val = _ljit_new_temporary(fun, op1->type)) == NULL)
    {
        _ljit_free_bytecode(instr);
        return NULL;
    }

    /* Set the return temporary as return value of the instruction */
    instr->ret_val = ret_val;

    /*
    Add the created instruction to the current constructed block of the
    function
    */
    ljit_bytecode_list_add(&fun->current_blk->instrs, instr);

    return ret_val;
}

ljit_bytecode *_ljit_new_bytecode(ljit_bytecode_type type,
                                  ljit_value op1,
                                  ljit_value op2)
{
    ljit_bytecode *instr = NULL;

    if ((instr = malloc(sizeof(ljit_bytecode))) == NULL)
        return NULL;

    if (op1)
        ++op1->count;
    if (op2)
        ++op2->count;

    instr->type = type;
    instr->op1 = op1;
    instr->op2 = op2;
    instr->ret_val = NULL;

    return instr;
}

ljit_value ljit_inst_get_param(ljit_function *fun, ljit_uchar pos)
{
    ljit_value ret_val = NULL;
    ljit_bytecode *instr = NULL;
    ljit_value pos_cst = NULL;

    /* Allocate new constant that represent the number of the parameter */
    if ((pos_cst = ljit_new_uchar_cst(pos)) == NULL)
        return NULL;

    /* Allocate the instruction */
    if ((instr = _ljit_new_bytecode(GET_PARAM, pos_cst, NULL)) == NULL)
    {
        ljit_free_value(pos_cst);
        return NULL;
    }

    /* Create the new temporary that holds the result of the instruction */
    if ((ret_val = _ljit_new_temporary(fun,
                                       fun->signature->params_type[pos])) == NULL)
    {
        ljit_free_value(pos_cst);
        _ljit_free_bytecode(instr);
        return NULL;
    }

    /* Set the return temporary as result of the instruction */
    instr->ret_val = ret_val;

    /* Add this instruction to the instruction list of the current block */
    ljit_bytecode_list_add(&fun->current_blk->instrs, instr);

    return ret_val;
}

/* FIXME : Check return type and the value type */
int ljit_inst_return(ljit_function *fun, ljit_value val)
{
    ljit_bytecode *instr = NULL;

    /* Create the instruction */
    if ((instr = _ljit_new_bytecode(RETURN, val, NULL)) == NULL)
        return -1;

    /* Add the instruction to the instruction list of the current block */
    ljit_bytecode_list_add(&fun->current_blk->instrs, instr);

    return 0;
}

int ljit_bind_label(ljit_function *fun, ljit_label *lbl)
{
    ljit_bytecode *instr = NULL;
    ljit_value value = NULL;

    if ((value = ljit_new_value(LJIT_LABEL)) == NULL)
        return -1;

    if ((instr = _ljit_new_bytecode(LABEL, value, NULL)) == NULL)
    {
        ljit_free_value(value);
        return -1;
    }

    /* FIXME : Create new block if this close a basic block */

    ++lbl->count;
    value->data = lbl;

    /*
    Decrement count because ljit_new_bytecode does an unecessery +1 in this
    case.
     */
    --value->count;

    /* Add the instruction to the instruction list of the current block */
    lbl->instr = ljit_bytecode_list_add(&fun->current_blk->instrs, instr);

    if (!lbl->instr)
        return -1;

    return 0;
}

int ljit_inst_jump(ljit_function *fun, ljit_label *lbl)
{
    ljit_bytecode *instr = NULL;
    ljit_value val = NULL;

    if ((val = ljit_new_value(LJIT_LABEL)) == NULL)
        return -1;

    if ((instr = _ljit_new_bytecode(JUMP, val, NULL)) == NULL)
    {
        ljit_free_value(val);
        return -1;
    }

    val->data = lbl;

    /* Label is now referenced on more time */
    ++lbl->count;

    /*
    Decrement count because ljit_new_bytecode does an unecessery +1 in this
    case.
     */
    --val->count;

    /* Add the instruction to the instruction list of the current block */
    ljit_bytecode_list_add(&fun->current_blk->instrs, instr);

    return 0;
}

int ljit_inst_jump_if(ljit_function *fun, ljit_value val, ljit_label *lbl)
{
    ljit_bytecode *instr = NULL;
    ljit_value val_lbl = NULL;

    if ((val_lbl = ljit_new_value(LJIT_LABEL)) == NULL)
        return -1;

    if ((instr = _ljit_new_bytecode(JUMP_IF, val, val_lbl)) == NULL)
    {
        ljit_free_value(val_lbl);
        return -1;
    }

    val_lbl->data = lbl;

    /* Label is now referenced on more time */
    ++lbl->count;

    /*
    Decrement count because ljit_new_bytecode does an unecessery +1 in this
    case.
     */
    --val_lbl->count;

    /* Add the instruction to the instruction list of the current block */
    ljit_bytecode_list_add(&fun->current_blk->instrs, instr);

    return 0;
}

int ljit_inst_jump_if_not(ljit_function *fun, ljit_value val, ljit_label *lbl)
{
    ljit_bytecode *instr = NULL;
    ljit_value val_lbl = NULL;

    if ((val_lbl = ljit_new_value(LJIT_LABEL)) == NULL)
        return -1;

    if ((instr = _ljit_new_bytecode(JUMP_IF_NOT, val, val_lbl)) == NULL)
    {
        ljit_free_value(val_lbl);
        return -1;
    }

    val_lbl->data = lbl;

    /* Label is now referenced on more time */
    ++lbl->count;

    /*
    Decrement count because ljit_new_bytecode does an unecessery +1 in this
    case.
     */
    --val_lbl->count;

    /* Add the instruction to the instruction list of the current block */
    ljit_bytecode_list_add(&fun->current_blk->instrs, instr);

    return 0;
}

ljit_value ljit_inst_add(ljit_function *fun, ljit_value op1, ljit_value op2)
{
    return _ljit_build_operation(fun, op1, op2, ADD);
}

ljit_value ljit_inst_sub(ljit_function *fun, ljit_value op1, ljit_value op2)
{
    return _ljit_build_operation(fun, op1, op2, SUB);
}

ljit_value ljit_inst_mul(ljit_function *fun, ljit_value op1, ljit_value op2)
{
    return _ljit_build_operation(fun, op1, op2, MUL);
}

ljit_value ljit_inst_div(ljit_function *fun, ljit_value op1, ljit_value op2)
{
    return _ljit_build_operation(fun, op1, op2, DIV);
}
