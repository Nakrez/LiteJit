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
**  @file   interference.h
**  @brief  Interference graph representation and manipulation function
**  @author Baptiste Covolato <b.covolato@gmail.com>
**  @date   21 September 2013
*/

#ifndef INTERFERENCE_H
# define INTERFERENCE_H

# include <stdlib.h>

# include "liveness-utils.h"

typedef struct _ljit_interference_graph_s ljit_interference_graph;

/**
**  @brief  This data structure represents the interference graph
*/

struct _ljit_interference_graph_s
{
    /**
    **  @brief  The size of the interference graph
    */
    int size;

    /**
    **  @brief  The edges of the interference graph
    */
    _ljit_liveness_info **graph;
};

/**
**  @brief  Create an empty new interference graph
**  @param  The size of the interference graph
**
**  @return The new interference graph if everything went well, NULL otherwise
*/

ljit_interference_graph *_ljit_interference_graph_new(int size);

#endif /* !INTERFERENCE_H */