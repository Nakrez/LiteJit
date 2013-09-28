#include "regalloc.h"

static void _ljit_update_temporary(ljit_value val, ljit_interference_graph *ig)
{
    if (!val->is_tmp)
        return;

    val->index = ig->colors[val->index];
}

static void _ljit_update_temporaries(ljit_function *fun,
                                     ljit_interference_graph *ig)
{
    ljit_block *blk = fun->start_blk;
    struct _ljit_bytecode_list_element_s *instrs = NULL;

    while (blk)
    {
        instrs = blk->instrs->head;

        while (instrs)
        {
            switch (instrs->instr->type)
            {
                case GET_PARAM:
                    _ljit_update_temporary(instrs->instr->ret_val, ig);
                    break;
                case RETURN:
                case JUMP:
                    _ljit_update_temporary(instrs->instr->op1, ig);
                    break;
                case JUMP_IF:
                case JUMP_IF_NOT:
                    _ljit_update_temporary(instrs->instr->op2, ig);
                    break;
                case ADD:
                case SUB:
                case MUL:
                case DIV:
                    _ljit_update_temporary(instrs->instr->op1, ig);
                    _ljit_update_temporary(instrs->instr->op2, ig);
                    _ljit_update_temporary(instrs->instr->ret_val, ig);
                    break;
                default:
                    break;
            }

            instrs = instrs->next;
        }

        blk = blk->next;
    }
}

int _ljit_regalloc(ljit_function *fun)
{
    ljit_flow_graph *fg = NULL;
    ljit_interference_graph *ig = NULL;
    int flow_graph_size = 0;

    /* Build the flow graph */
    if ((fg = _ljit_build_flow_graph(fun, &flow_graph_size)) == NULL)
        return -1;

    /* If debug options are on export the flow graph to dot format */
#ifdef LJIT_DEBUG
    _ljit_dot_flow_graph(fg, "ljit_flow_graph.dot");
#endif /* LJIT_DEBUG */

    /* Compute the liveness informations and build the interference graph */
    ig = _ljit_compute_liveness(fg, flow_graph_size, fun->uniq_index);

    /* Color the interference graph */
    _ljit_color_graph(ig);

    /* If debug options are on export the interference graph to dot format */
#ifdef LJIT_DEBUG
    _ljit_interference_graph_debug(ig, "ljit_interference_graph.dot");
#endif /* LJIT_DEBUG */

    /* Update temporary numbers */
    _ljit_update_temporaries(fun, ig);

    /* Free the flow graph because it is not needed anymore */
    _ljit_free_flow_graph(fg);

    /* Free the interference graph because it is not needed anymore */
    _ljit_interference_graph_free(ig);

    return 0;
}
