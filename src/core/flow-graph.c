#include "flow-graph.h"

int _ljit_build_flow_graph(ljit_function *fun)
{
    return 0;
}

#ifdef LJIT_DEBUG
int _ljit_dot_flow_graph(ljit_function *fun, const char *name)
{
    return 0;
}
#endif /* LJIT_DEBUG */
