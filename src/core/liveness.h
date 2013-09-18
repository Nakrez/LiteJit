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
**  @file   liveness.h
**  @brief  Liveness computation algorithm
**  @author Baptiste Covolato <b.covolato@gmail.com>
**  @date   14 September 2013
*/

#ifndef LIVENESS_H
# define LIVENESS_H

# include <alloca.h>

# include "flow-graph.h"
# include "liveness-utils.h"

/**
**  @brief  Compute liveness information on a control flow graph.
**  @oaram  fg          The flow graph on which you want to compute liveness
**                      analysis.
**  @param  graph_size  The number of node of the control flow graph.
*/

void _ljit_compute_liveness(ljit_flow_graph *fg, int graph_size);

#endif /* !LIVENESS_H */
