#include "flow-graph.h"

static int _ljit_add_edge(ljit_function *fun,
                          ljit_block *block,
                          ljit_label *lbl)
{
    ljit_block *target_block = ljit_get_block_from_label(fun, lbl);
    ljit_edge *edge = NULL;

    if (!target_block)
        return -1;

    if ((edge = _ljit_new_edge(target_block)) == NULL)
        return -1;

    /* Add the new edge at the beginning */
    edge->next = block->edges;
    block->edges = edge;

    return 0;
}

ljit_edge *_ljit_new_edge(ljit_block *block)
{
    ljit_edge *edge;

    if ((edge = malloc(sizeof(ljit_edge))) == NULL)
        return NULL;

    edge->block = block;
    edge->next = NULL;

    return edge;
}

void _ljit_free_edge(ljit_edge *edge)
{
    if (!edge)
        return;

    _ljit_free_edge(edge->next);
    free(edge);
}

int _ljit_build_flow_graph(ljit_function *fun)
{
    ljit_block *tmp = fun->start_blk;
    struct _ljit_bytecode_list_element_s *tmp_instr = NULL;

    /* Iterate over all the block */
    while (tmp)
    {
        tmp_instr = tmp->instrs->head;

        /* Iterate over all instructions to find jumps */
        while (tmp_instr)
        {
            switch (tmp_instr->instr->type)
            {
                case JUMP:
                    _ljit_add_edge(fun, tmp, tmp_instr->instr->op1->data);
                    break;
                case JUMP_IF:
                case JUMP_IF_NOT:
                    _ljit_add_edge(fun, tmp, tmp_instr->instr->op2->data);
                    break;
                default:
                    break;
            }

            tmp_instr = tmp_instr->next;
        }

        tmp = tmp->next;
    }

    return 0;
}

#ifdef LJIT_DEBUG
int _ljit_dot_flow_graph(ljit_function *fun, const char *name)
{
    return 0;
}
#endif /* LJIT_DEBUG */
