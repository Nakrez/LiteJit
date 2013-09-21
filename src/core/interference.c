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

void _ljit_interference_graph_free(ljit_interference_graph *ig)
{
    for (int i = 0; i < ig->size; ++i)
        _ljit_liveness_info_free(ig->graph[i]);

    free(ig->graph);
    free(ig);
}

int _ljit_interference_graph_edge_exists(ljit_interference_graph *ig,
                                         unsigned short v1,
                                         unsigned short v2)
{
    _ljit_liveness_info *tmp = ig->graph[v1];

    while (tmp)
    {
        if (tmp->elt == v2)
            return 1;

        tmp = tmp->next;
    }

    return 0;
}

void _ljit_interference_graph_add_edge(ljit_interference_graph *ig,
                                       unsigned short v1,
                                       unsigned short v2)
{
    /* If the edge exists nothing to do */
    if (_ljit_interference_graph_edge_exists(ig, v1, v2))
        return;

    _ljit_liveness_info *e1 = _ljit_liveness_info_new(v1);
    _ljit_liveness_info *e2 = _ljit_liveness_info_new(v2);


    ig->graph[v1] = _ljit_liveness_add_head(ig->graph[v1], e2);
    ig->graph[v2] = _ljit_liveness_add_head(ig->graph[v2], e1);
}

ljit_interference_graph *
_ljit_interference_graph_build_from_out(_ljit_liveness_info **out,
                                        int graph_size)
{
    ljit_interference_graph *ig = NULL;
    _ljit_liveness_info *tmp = NULL;
    _ljit_liveness_info *ref = NULL;

    if ((ig = _ljit_interference_graph_new(graph_size)) == NULL)
        return NULL;

    /* Run through every data of the out data */
    for (int i = 0; i < graph_size; ++i)
    {
        ref = out[i];

        while (ref)
        {
            tmp = out[i];

            while (tmp)
            {
                /*
                 **  If the value is the same as the current one don't create a loop
                 **  edge
                 */
                if (tmp->elt == ref->elt)
                {
                    tmp = tmp->next;
                    continue;
                }

                /* Add the edge to the interference graph */
                _ljit_interference_graph_add_edge(ig, ref->elt, tmp->elt);

                tmp = tmp->next;
            }

            ref = ref->next;
        }
    }

    return ig;
}

void _ljit_interference_graph_debug(ljit_interference_graph *ig, char *file)
{
    FILE *f = NULL;
    _ljit_liveness_info *tmp = NULL;

    if ((f = fopen(file, "w")) == NULL)
        return;

    fprintf(f, "graph interference_graph {\n");

    for (int i = 0; i < ig->size; ++i)
    {
        tmp = ig->graph[i];

        while (tmp)
        {
            fprintf(f, "%u -- %u\n", i, tmp->elt);
            tmp = tmp->next;
        }
    }

    fprintf(f, "}\n");
}
