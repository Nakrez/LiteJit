#include "liveness.h"

static void _ljit_dump_liveness_array(_ljit_liveness_info **array,
                                      int size)
{
    for (int i = 0; i < size; ++i)
    {
        printf("%i : ", i);
        _ljit_liveness_info_dump(array[i], ", ");
        printf("\n");
    }
}

static void _ljit_add_value(_ljit_liveness_info **array,
                            ljit_value val,
                            int index)
{
    if (val && val->is_tmp &&
        !_ljit_liveness_info_elt_exists(array[index], val->index))
    {
        _ljit_liveness_info *elem = NULL;
        elem = _ljit_liveness_info_new(val->index);
        array[index] = _ljit_liveness_add_head(array[index], elem);
    }
}

void _ljit_compute_def_use(ljit_flow_graph *fg,
                           _ljit_liveness_info **def,
                           _ljit_liveness_info **use)
{
    if (!fg || fg->marked)
        return;

    fg->marked = 1;

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
            _ljit_add_value(def, fg->instr->ret_val, fg->index);
            break;

        default: /* LABEL */
            break;
    }

    _ljit_compute_def_use(fg->first_next, def, use);
    _ljit_compute_def_use(fg->second_next, def, use);
}

static void _ljit_flow_graph_array(ljit_flow_graph *fg,
                                   ljit_flow_graph **graph)
{
    if (!fg || fg->marked)
        return;

    fg->marked = 1;

    graph[fg->index] = fg;

    _ljit_flow_graph_array(fg->first_next, graph);
    _ljit_flow_graph_array(fg->second_next, graph);
}

static void _ljit_compute_in_out(_ljit_liveness_info **def,
                                 _ljit_liveness_info **use,
                                 _ljit_liveness_info **in,
                                 _ljit_liveness_info **out,
                                 ljit_flow_graph **graph,
                                 int graph_size)
{
    _ljit_liveness_info *in_backup = NULL;
    _ljit_liveness_info *out_backup = NULL;
    int tmp = 1;

    while (tmp)
    {
        tmp = 0;

        for (int i = 0; i < graph_size; ++i)
        {
            in_backup = _ljit_copy_list(in[i], in_backup, LJIT_FORCE_COPY);
            out_backup = _ljit_copy_list(out[i], out_backup, LJIT_FORCE_COPY);

            /* in[i] := use[i] U (out[i] - def[i]) */
            out[i] = _ljit_liveness_info_minus(out[i], def[i]);
            in[i] = _ljit_liveness_info_merge(out[i], use[i]);

            out[i] = NULL;

            /* out[i] := U {in[s] | s in succ[i]} */
            if (graph[i]->first_next)
                out[i] = _ljit_copy_list(in[graph[i]->first_next->index],
                                         out[i], LJIT_FORCE_COPY);
            if (graph[i]->second_next)
                out[i] = _ljit_liveness_info_merge(out[i],
                                                   in[graph[i]->second_next->index]);

            /* Check if in[i] == in_backup[i] and out[i] == out_backup[i] */
            if (!_ljit_liveness_info_equals(in[i], in_backup) ||
                !_ljit_liveness_info_equals(out[i], out_backup))
                tmp = 1;

            /* _ljit_liveness_info_free(in_backup); */
            /* _ljit_liveness_info_free(out_backup); */
        }
    }
}

void _ljit_free_liveness_array(_ljit_liveness_info **array, int array_size)
{
    for (int i = 0; i < array_size; ++i)
        _ljit_liveness_info_free(array[i]);
}

void _ljit_compute_liveness(ljit_flow_graph *fg, int graph_size)
{
    _ljit_liveness_info **def = alloca(graph_size *
                                       sizeof(_ljit_liveness_info *));
    _ljit_liveness_info **use = alloca(graph_size *
                                       sizeof(_ljit_liveness_info *));
    _ljit_liveness_info **in = alloca(graph_size *
                                      sizeof(_ljit_liveness_info *));
    _ljit_liveness_info **out = alloca(graph_size *
                                       sizeof(_ljit_liveness_info *));
    ljit_flow_graph **graph = alloca(graph_size *
                                     sizeof(ljit_flow_graph *));

    memset(in, 0, graph_size * sizeof(_ljit_liveness_info *));
    memset(out, 0, graph_size* sizeof(_ljit_liveness_info *));

    _ljit_compute_def_use(fg, def, use);
    _ljit_unmark_flow_graph(fg);

    _ljit_flow_graph_array(fg, graph);
    _ljit_unmark_flow_graph(fg);

    _ljit_compute_in_out(def, use, in, out, graph, graph_size);


#ifdef LJIT_DEBUG
    printf("---- Def array ----\n");
    _ljit_dump_liveness_array(def, graph_size);
    printf("----           ----\n\n");

    printf("---- Use array ----\n");
    _ljit_dump_liveness_array(use, graph_size);
    printf("----           ----\n");

    printf("---- In array ----\n");
    _ljit_dump_liveness_array(in, graph_size);
    printf("----           ----\n\n");

    printf("---- Out array ----\n");
    _ljit_dump_liveness_array(out, graph_size);
    printf("----           ----\n\n");
#endif /* LJIT_DEBUG */

    /* Release memory */
    _ljit_free_liveness_array(def, graph_size);
    _ljit_free_liveness_array(use, graph_size);
    _ljit_free_liveness_array(in, graph_size);
    _ljit_free_liveness_array(out, graph_size);
}
