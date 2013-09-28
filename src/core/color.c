#include "color.h"

static int find_candidate(_ljit_color_stack *cs,
                          ljit_interference_graph *ig)
{
    for (int i = 0; i < ig->size; ++i)
    {
        if (!_ljit_color_stack_is_present(cs, i) &&
            _ljit_liveness_info_size(ig->graph[i]) < LJIT_USABLE_REGS)
            return i;
    }

    return -1;
}

static void remove_all_vertex(ljit_interference_graph *ig, int candidate)
{
    _ljit_liveness_info *li = ig->graph[candidate];

    while (li)
    {
        ig->graph[li->elt] = _ljit_liveness_info_remove(ig->graph[li->elt],
                                                        candidate);

        li = li->next;
    }
}

static void _ljit_fill_stack(_ljit_color_stack *cs,
                             ljit_interference_graph *ig)
{
    int ig_virtual_size = ig->size;
    int candidate = 0;

    while (ig_virtual_size)
    {
        /*
        ** Find a node with less than K node.
        ** Where K is the number of registers)
        */
        if ((candidate = find_candidate(cs, ig)) == -1)
            assert(0 && "This function needs spill. Not implemented yet");

        /* Remove all vertex from this node */
        remove_all_vertex(ig, candidate);

        /* Push this node on the stack */
        _ljit_color_stack_push(cs, candidate, ig->graph[candidate]);
        ig->graph[candidate] = NULL;

        --ig_virtual_size;
    }
}

static int is_in(unsigned char elt, unsigned char *array, unsigned int size)
{
    for (unsigned int i = 0; i < size; ++i)
    {
        if (array[i] == elt)
            return 1;
    }

    return 0;
}

static unsigned char get_color_for_node(ljit_interference_graph *ig,
                                        _ljit_liveness_info *vertex)
{
    unsigned char color = 0;
    unsigned int size = _ljit_liveness_info_size(vertex);
    unsigned int tmp = 0;
    unsigned char *forbidden_colors = alloca(size);

    while (vertex)
    {
        forbidden_colors[tmp++] = ig->colors[vertex->elt];
        vertex = vertex->next;
    }

    while (is_in(color, forbidden_colors, size))
        ++color;

    return color;
}

static void restore_vertex(_ljit_liveness_info *vertex,
                           int edge,
                           ljit_interference_graph *ig)
{
    _ljit_liveness_info *tmp = NULL;
    ig->graph[edge] = vertex;

    while (vertex)
    {
        tmp = _ljit_liveness_info_new(edge);
        ig->graph[vertex->elt] = _ljit_liveness_add_head(ig->graph[vertex->elt],
                                                         tmp);

        vertex = vertex->next;
    }
}

void _ljit_color_graph(ljit_interference_graph *ig)
{
    _ljit_color_stack *cs = NULL;
    int number = 0;
    _ljit_liveness_info *vertex = NULL;

    cs = _ljit_color_stack_new(ig->size);

    _ljit_fill_stack(cs, ig);

    while (!_ljit_color_stack_is_empty(cs))
    {
        vertex = _ljit_color_stack_pop(cs, &number);
        ig->colors[number] = get_color_for_node(ig, vertex);
        restore_vertex(vertex, number, ig);
    }

    _ljit_color_stack_free(cs);
}
