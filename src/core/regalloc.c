#include "regalloc.h"

int _ljit_regalloc(ljit_function *fun)
{
    ljit_flow_graph *fg = NULL;

    if ((fg = _ljit_build_flow_graph(fun)) == NULL)
        return -1;

#ifdef LJIT_DEBUG
    _ljit_dot_flow_graph(fg, "ljit_flow_graph.dot");
#endif /* LJIT_DEBUG */

    _ljit_free_flow_graph(fg);

    return 0;
}
