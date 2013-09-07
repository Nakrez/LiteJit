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
                    if (_ljit_add_edge(fun, tmp, tmp_instr->instr->op1->data))
                        return -1;
                    break;
                case JUMP_IF:
                case JUMP_IF_NOT:
                    if (_ljit_add_edge(fun, tmp, tmp_instr->instr->op2->data))
                        return -1;
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
static void _ljit_dot_write_label(FILE *f, ljit_block *b)
{
    struct _ljit_bytecode_list_element_s *tmp;

    /* Run all block to generate it corresponding label */
    while (b)
    {
        tmp = b->instrs->head;

        /* Generate the name of the label */
        fprintf(f, "label%u [label = \"", b->id);

        /* Dump all instructions that are in the block */
        while (tmp)
        {
            _ljit_dump_instr(f, tmp->instr);
            fprintf(f, "\\n");
            tmp = tmp->next;
        }

        fprintf(f, "\"];\n");
        b = b->next;
    }
}

static void _ljit_dot_write_edges(FILE *f, ljit_function *fun)
{
    ljit_block *blocks = fun->start_blk;
    ljit_edge *edges = NULL;

    /* Run every block to write all edges */
    while (blocks)
    {
        edges = blocks->edges;

        /* Link the block with all edges */
        while (edges)
        {
            fprintf(f, "label%u -> label%u;\n", blocks->id, edges->block->id);
            edges = edges->next;
        }

        blocks = blocks->next;
    }
}

int _ljit_dot_flow_graph(ljit_function *fun, const char *name)
{
    FILE *f = NULL;

    if ((f = fopen(name, "w")) == NULL)
        return -1;

    fprintf(f, "digraph flow_graph {\n");

    /* Write all node content */
    _ljit_dot_write_label(f, fun->start_blk);

    fprintf(f, "\n");

    /* Write the flow graph edges */
    _ljit_dot_write_edges(f, fun);

    fprintf(f, "}");

    fprintf(f, "\n");

    fclose(f);

    return 0;
}
#endif /* LJIT_DEBUG */
