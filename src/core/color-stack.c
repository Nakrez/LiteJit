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

int _ljit_color_stack_is_empty(_ljit_color_stack *cs)
{
    if (!cs)
        return 1;

    return cs->size == 0;
}

void _ljit_color_stack_push(_ljit_color_stack *cs,
                            int num,
                            _ljit_liveness_info *edges)
{
    if (!cs)
        return;

    cs->edge_number[cs->size++] = num;
    cs->node_vertex[cs->size] = edges;
}

_ljit_liveness_info *_ljit_color_stack_pop(_ljit_color_stack *cs, int *num)
{
    if (!cs || cs->size == 0)
        return NULL;

    *num = cs->edge_number[--cs->size];

    return cs->node_vertex[cs->size];
}

int _ljit_color_stack_is_present(_ljit_color_stack *cs, int num)
{
    if (!cs)
        return 0;

    for (unsigned int i = 0; i < cs->size; ++i)
    {
        if (cs->edge_number[i] == num)
            return 1;
    }

    return 0;
}
