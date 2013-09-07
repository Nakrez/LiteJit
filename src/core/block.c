#include "internal.h"
#include "flow-graph.h"

ljit_block *ljit_new_block(ljit_function *fun, ljit_label *l)
{
    ljit_block *block = NULL;

    if ((block = malloc(sizeof(ljit_block))) == NULL)
        return NULL;

    block->next = NULL;
    block->previous = NULL;
    block->edges = NULL;
    block->id = fun->block_id++;
    block->label = l;

    if ((block->instrs = ljit_new_bytecode_list()) == NULL)
    {
        free(block);
        return NULL;
    }

    return block;
}

void ljit_free_block(ljit_block *block)
{
    if (!block)
        return;

    ljit_free_bytecode_list(block->instrs);
    _ljit_free_edge(block->edges);

    free(block);
}

int _ljit_create_block_if_needed(ljit_function *fun, ljit_label *lbl)
{
    ljit_bytecode_type itype = 0;
    ljit_block *new_block = NULL;

    /* If there is no instruction on the current block nothing to do */
    if (!fun->current_blk->instrs->tail)
        return 0;

    itype = fun->current_blk->instrs->tail->instr->type;

    /*
    If the last instruction in the current block is not an instruction that
    terminates a basic block then nothing to do
    */

    if ((itype < JUMP || itype > JUMP_IF_NOT) && itype != RETURN)
    {
        if (lbl)
        {
            /*
            FIXME : Add the label to the label list that points on the current
            block
            */
        }

        return 0;
    }

    /*
    If the last instruction was a conditional jump add an unconditional jump to
    lbl
    */

    if (itype == JUMP_IF || itype == JUMP_IF_NOT)
    {
        if (ljit_inst_jump(fun, lbl))
            return -1;
    }

    /* If label does not exist create one and bind it */
    if (!lbl)
    {
        if ((lbl = ljit_new_label(fun)) == NULL)
            return -1;

        return ljit_bind_label(fun, lbl);
    }

    if ((new_block = ljit_new_block(fun, lbl)) == NULL)
        return -1;

    fun->last_blk->next = new_block;
    fun->last_blk = new_block;
    fun->current_blk = new_block;

    return 1;
}

ljit_block *ljit_get_block_from_label(ljit_function *fun, ljit_label *l)
{
    ljit_block *b = fun->start_blk;

    while (b)
    {
        if (b->label->index == l->index)
            return b;

        b = b->next;
    }

    return NULL;
}
