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

typedef struct _ljit_flow_graph_s ljit_flow_graph;

struct _ljit_flow_graph_s
{
    /**
    **  @brief  The instruction contained in the node of the flow graph.
    **          This field MUST NOT be free since it is held by a ljit_function
    */
    ljit_bytecode *instr;

    /**
    **  @brief  The next node in the flow graph.
    */
    ljit_flow_graph *first_next;

    /**
    **  @brief  The flow graph only can only contain 2 sucessors since
    **          no instruction can jump on three different destination
    */
    ljit_flow_graph *second_next;

    /**
    **  @brief  Unique index of a flow graph node
    */
    int index;

    /**
    **  @brief  Indicate if a node has been marked. Useful when doing
    **          recursive operation on the flow graph
    */
    int marked;
};

/**
**  @brief  Create a new flow graph node
**  @param  instr   The instruction held by the flow graph
**
**  @return The new node, NULL if something went wrong
*/

ljit_flow_graph *_ljit_new_flow_graph(ljit_bytecode *instr);

/**
**  @brief  Destroy a flow graph
**  @param  fg  The flow graph you want to destroy
*/

void _ljit_free_flow_graph(ljit_flow_graph *fg);

/**
**  @brief  Build flow graph of a function
**  @param  fun     The function from which you want to build the flow graph
**  @param  fg_size This variable will received the size of the flow graph
**
**  @return The flow graph if everything went well, NULL otherwise
*/

ljit_flow_graph *_ljit_build_flow_graph(ljit_function *fun, int *fg_size);

/**
**  @brief  Unmark a flow_graph
**  @param  fg  The flow graph you want to unmark
*/

void _ljit_unmark_flow_graph(ljit_flow_graph *fg);

/**
**  @brief  Print the flow graph in the dot format into a file
**  @param  fun     The function that contains the control flow graph you want
**                  to export
**  @param  name    The name of the file where to export the flow graph
**
**  @return 0 if everything went well, -1 otherwise
*/

int _ljit_dot_flow_graph(ljit_flow_graph *fg, const char *name);

#endif /* !FLOW_GRAPH_H */
