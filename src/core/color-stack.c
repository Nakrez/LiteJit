#include "color-stack.h"

_ljit_color_stack *_ljit_color_stack_new(unsigned int size)
{
    _ljit_color_stack *cs = NULL;

    if ((cs = malloc(sizeof (_ljit_color_stack))) == NULL)
        return NULL;

    if ((cs->edge_number = malloc(size * sizeof (int))) == NULL)
    {
        free(cs);
        return NULL;
    }

    if ((cs->node_vertex = malloc(size * sizeof (_ljit_liveness_info *))) ==
        NULL)
    {
        free(cs->edge_number);
        free(cs);
        return NULL;
    }

    cs->size = 0;

    return cs;
}

void _ljit_color_stack_free(_ljit_color_stack *cs)
{
    if (!cs)
        return;

    free(cs->node_vertex);
    free(cs->edge_number);
    free(cs);
}

void _ljit_color_stack_push(_ljit_color_stack *cs,
                            int num,
                            _ljit_liveness_info *edges)
{
    cs->edge_number[cs->size++] = num;
    cs->node_vertex[cs->size] = edges;
}
