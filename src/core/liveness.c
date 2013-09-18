#include "liveness.h"

static void _ljit_add_value(_ljit_liveness_info **array,
                            ljit_value val,
                            int index)
{
    if (val && val->is_tmp)
    {
        _ljit_liveness_info *elem = NULL;
        elem = _ljit_liveness_info_new(val->index);
        _ljit_liveness_add_head(&array[index], elem);
    }
}

void _ljit_compute_def_use(ljit_flow_graph *fg,
                           _ljit_liveness_info **def,
                           _ljit_liveness_info **use)
{
    if (!fg)
        return;

    def[fg->index] = NULL;
    use[fg->index] = NULL;

    switch (fg->instr->type)
    {
        case GET_PARAM:
            _ljit_add_value(def, fg->instr->ret_val, fg->index);
            break;

        case RETURN:
        case JUMP:
            _ljit_add_value(use, fg->instr->op1, fg->index);
            break;

        case JUMP_IF:
        case JUMP_IF_NOT:
            _ljit_add_value(use, fg->instr->op1, fg->index);
            _ljit_add_value(use, fg->instr->op2, fg->index);
            break;

        case ADD:
        case SUB:
        case MUL:
        case DIV:
            _ljit_add_value(use, fg->instr->op1, fg->index);
            _ljit_add_value(use, fg->instr->op2, fg->index);
            _ljit_add_value(use, fg->instr->ret_val, fg->index);
            break;

        default: /* LABEL */
            break;
    }

    _ljit_compute_def_use(fg->first_next, def, use);
    _ljit_compute_def_use(fg->second_next, def, use);
}

void _ljit_compute_liveness(ljit_flow_graph *fg, int graph_size)
{
    _ljit_liveness_info **def = alloca(graph_size *
                                       sizeof(_ljit_liveness_info *));
    _ljit_liveness_info **use = alloca(graph_size *
                                       sizeof(_ljit_liveness_info *));

    _ljit_compute_def_use(fg, def, use);
}
