#include "interference.h"

ljit_interference_graph *_ljit_interference_graph_new(int size)
{
    ljit_interference_graph *ig = NULL;

    if ((ig = malloc(sizeof (ljit_interference_graph))) == NULL)
        return NULL;

    if ((ig->graph = calloc(1, size * sizeof (_ljit_liveness_info *))) == NULL)
    {
        free(ig);
        return NULL;
    }

    ig->size = size;

    return ig;
}

void _ljit_interference_graph(ljit_interference_graph *ig)
{
    for (int i = 0; i < ig->size; ++i)
        _ljit_liveness_info_free(ig->graph[i]);

    free(ig->graph);
    free(ig);
}
