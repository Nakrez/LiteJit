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
**  @file   color-stack.h
**  @brief  Stack used in graph coloring
**  @author Baptiste Covolato <b.covolato@gmail.com>
**  @date   28 September 2013
*/

#ifndef COLOR_STACK_H
# define COLOR_STACK_H

# include "liveness-utils.h"

typedef struct _ljit_color_stack_s _ljit_color_stack;

/*
**  @brief  This structure is used in the interference graph coloring process
*/
struct _ljit_color_stack_s
{
    /*
    **  @brief  The vertex of the edges stored */
    _ljit_liveness_info **node_vertex;

    /*
    **  @brief  The edge number in the graph
    */
    int *edge_number;

    /*
    **  @brief  The size of the stack
    */
    unsigned int size;
};

/**
**  @brief  Allocate a new stack used for graph coloring process
**  @param  size    The maximum size of the stack
**
**  @return The new stack if everything went well, NULL otherwise
*/

_ljit_color_stack *_ljit_color_stack_new(unsigned int size);

/**
**  @brief  Destroy a color stack
**  @param  The color stack you want to free
*/

void _ljit_colot_stack_free(_ljit_color_stack *cs);

#endif /* !COLOR_STACK_H */
