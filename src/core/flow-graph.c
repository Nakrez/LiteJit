#include "flow-graph.h"

#define _LJIT_LABEL_FG_INIT(size)                       \
    _ljit_label_fg_node(1, 0, size, NULL, NULL)

#define _LJIT_LABEL_FG_FREE()                           \
    _ljit_label_fg_node(0, 1, 0, NULL, NULL)

#define _LJIT_LABEL_FG_GET(label, fun)                  \
    _ljit_label_fg_node(0, 0, 0, label, fun)

static int _ljit_fg_index()
{
    static int i = -1;

    ++i;

    return i;
}

static ljit_flow_graph *_ljit_label_fg_node(unsigned int init,
                                            unsigned int destroy,
                                            unsigned int number_tmp,
                                            ljit_label *l,
                                            ljit_function *fun)
{
    static unsigned int size = 0;
    static ljit_flow_graph ** fg = NULL;

    if (init)
    {
        /*
        ** Init the temporary table with the number of temporaries of the
        ** function
        */
        size = number_tmp;
        fg = calloc(1, size * sizeof(ljit_flow_graph *));

        return NULL;
    }
    else if (destroy)
    {
        /*
        ** We don't free every element of the table because they compose the final
        ** result of the flow graph
        */
        free(fg);
        return NULL;
    }
    else
    {
        unsigned int label_num = l->index;

        /* If the node does not exist for this label create it */
        if (!fg[label_num])
        {
            ljit_block *b = ljit_get_block_from_label(fun, l);

            /*
            ** The first instruction of each block is a label, this is why
            ** we use the first instruction of the block associated with the 
            ** label l
            */
            fg[label_num] = _ljit_new_flow_graph(b->instrs->head->instr);

            if (!fg[label_num])
                return NULL;
        }

        return fg[label_num];
    }
}

ljit_flow_graph *_ljit_new_flow_graph(ljit_bytecode *instr)
{
    ljit_flow_graph *fg = NULL;

    if ((fg = malloc(sizeof(ljit_flow_graph))) == NULL)
        return NULL;

    fg->instr = instr;
    fg->first_next = NULL;
    fg->second_next = NULL;
    fg->index = _ljit_fg_index();
    fg->marked = 0;

    return fg;
}

void _ljit_free_flow_graph(ljit_flow_graph *fg)
{
    if (!fg || fg->marked)
        return;

    /* Mark this node so it won't be free more than once */
    fg->marked = 1;

    /* Free the sons of the current node */
    _ljit_free_flow_graph(fg->first_next);
    _ljit_free_flow_graph(fg->second_next);

    /* Free the current node */
    free(fg);
}

static ljit_flow_graph *
_ljit_recurse_build_fg(ljit_block *blk,
                       struct _ljit_bytecode_list_element_s *tmp_instr,
                       ljit_function *fun)
{
    ljit_flow_graph *fg = NULL;
    ljit_flow_graph *second = NULL;

    if (!tmp_instr)
    {
        if (!blk->next)
            return NULL;
        else
            return _ljit_recurse_build_fg(blk->next, blk->next->instrs->head,
                                          fun);
    }

    switch (tmp_instr->instr->type)
    {
        case JUMP:
            {
                /* Build the jump node */
                ljit_label *l = tmp_instr->instr->op1->data;
                ljit_block *b = ljit_get_block_from_label(fun, l);

                if ((fg = _ljit_new_flow_graph(tmp_instr->instr)) == NULL)
                    goto error;

                fg->marked = 1;

                /* Link with the target of the jump */
                fg->first_next = _ljit_recurse_build_fg(b, b->instrs->head,
                                                        fun);

                return fg;
            }
            break;
        case JUMP_IF:
        case JUMP_IF_NOT:
            {
                /* Build the conditional jump node */
                ljit_label *l = tmp_instr->instr->op2->data;
                ljit_block *b = ljit_get_block_from_label(fun, l);

                if ((fg = _ljit_new_flow_graph(tmp_instr->instr)) == NULL)
                    goto error;

                fg->marked = 1;

                /*
                ** Set the second son of the current node to the target of the
                ** conditional jump
                */
                second = _ljit_recurse_build_fg(b, b->instrs->head, fun);
            }
            break;
        case LABEL:
            {
                ljit_label *l = tmp_instr->instr->op1->data;

                /*
                ** Get the node from the temporary table (if it does not exists
                ** the function will build a new one
                */
                fg = _LJIT_LABEL_FG_GET(l, fun);

                /* If it has been marked we don't build it again */
                if (fg->marked)
                    return fg;
            }
            break;
        default:
            /* Build a regular node */
            if ((fg = _ljit_new_flow_graph(tmp_instr->instr)) == NULL)
                goto error;

            break;
    }

    fg->marked = 1;

    /* Build and link the next node */
    fg->first_next = _ljit_recurse_build_fg(blk, tmp_instr->next, fun);

    /*
    ** Link with a conditional jump (if the current node is a conditional jump
    ** second will contained the address of target of the jump)
    */
    fg->second_next = second;

    return fg;

error:
    free(fg);
    return NULL;
}

ljit_flow_graph *_ljit_build_flow_graph(ljit_function *fun)
{
    ljit_flow_graph *fg = NULL;

    /*
    ** Create the temporary table that holds a flow node that
    ** represent a label
    */
    _LJIT_LABEL_FG_INIT(fun->lbl_index);

    /* Build the graph */
    fg = _ljit_recurse_build_fg(fun->start_blk,
                                fun->start_blk->instrs->head,
                                fun);

    /* Free the temporary table created to build the graph */
    _LJIT_LABEL_FG_FREE();

    /* Unmark all the graph */
    _ljit_unmark_flow_graph(fg);

    return fg;
}

void _ljit_unmark_flow_graph(ljit_flow_graph *fg)
{
    if (!fg || !fg->marked)
        return;

    fg->marked = 0;

    _ljit_unmark_flow_graph(fg->first_next);
    _ljit_unmark_flow_graph(fg->second_next);
}

static void _ljit_dot_write_label(FILE *f, ljit_flow_graph *fg)
{
    if (!fg || fg->marked)
        return;

    fg->marked = 1;

    /* Generate the name of the label */
    fprintf(f, "label%u [label = \"", fg->index);

    /* Dump instruction of the node */
    _ljit_dump_instr(f, fg->instr);
    fprintf(f, "\"];\n");

    _ljit_dot_write_label(f, fg->first_next);
    _ljit_dot_write_label(f, fg->second_next);
}

static void _ljit_dot_write_edges(FILE *f, ljit_flow_graph *fg)
{
    if (!fg || fg->marked)
        return;

    fg->marked = 1;

    /* Write association between the current node and it son(s) */
    if (fg->first_next)
    {
        fprintf(f, "label%u -> label%u;\n", fg->index, fg->first_next->index);
        _ljit_dot_write_edges(f, fg->first_next);
    }

    if (fg->second_next)
    {
        fprintf(f, "label%u -> label%u;\n", fg->index, fg->second_next->index);
        _ljit_dot_write_edges(f, fg->second_next);
    }
}

int _ljit_dot_flow_graph(ljit_flow_graph *fg, const char *name)
{
    FILE *f = NULL;

    if ((f = fopen(name, "w")) == NULL)
        return -1;

    fprintf(f, "digraph flow_graph {\n");

    /* Write all node content */
    _ljit_dot_write_label(f, fg);
    _ljit_unmark_flow_graph(fg);

    fprintf(f, "\n");

    /* Write the flow graph edges */
    _ljit_dot_write_edges(f, fg);
    _ljit_unmark_flow_graph(fg);

    fprintf(f, "}");

    fprintf(f, "\n");

    fclose(f);

    return 0;
}
