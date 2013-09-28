#include "regalloc.h"

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

    /* Free the flow graph because it is not needed anymore */
    _ljit_free_flow_graph(fg);

    /* Free the interference graph because it is not needed anymore */
    _ljit_interference_graph_free(ig);

    return 0;
}
