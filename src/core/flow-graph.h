/*
    Copyright (C) 2013 Baptiste COVOLATO <b.covolato@gmail.com>

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to
    deal in the Software without restriction, including without limitation the
    rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
    sell copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

/**
**  @file   flow-graph.h
**  @brief  Flow graph related operations
**  @author Baptiste Covolato <b.covolato@gmail.com>
**  @date   31 August 2013
*/

#ifndef FLOW_GRAPH_H
# define FLOW_GRAPH_H

# include "internal.h"

/**
**  @brief  Create a new edge
**  @param  block   The block you want the edge pointed on
**
**  @return The new edge, NULL if something went wrong
*/

ljit_edge *_ljit_new_edge(ljit_block *block);

/**
**  @brief  Destroy an edge
**  @param  edge    The edge you want to destroy
*/

void _ljit_free_edge(ljit_edge *edge);

/**
**  @brief  Build flow graph of a function
**  @param  fun The function of which you want to build the flow graph
**
**  @return 0 if everything went well, -1 otherwise
*/

int _ljit_build_flow_graph(ljit_function *fun);

# ifdef LJIT_DEBUG
/**
**  @brief  Print the flow graph in the dot format into a file
**  @param  fun     The function that contains the control flow graph you want
**                  to export
**  @param  name    The name of the file where to export the flow graph
**
**  @return 0 if everything went well, -1 otherwise
*/

int _ljit_dot_flow_graph(ljit_function *fun, const char *name);
# endif /* LJIT_DEBUG */

#endif /* !FLOW_GRAPH_H */
