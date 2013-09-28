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
**  @file   color.h
**  @brief  Color the interference graph
**  @author Baptiste Covolato <b.covolato@gmail.com>
**  @date   28 September 2013
*/

#ifndef COLOR_H
# define COLOR_H

# include <assert.h>
# include <alloca.h>

# include <ljit/core/arch.h>

# include "interference.h"
# include "color-stack.h"

/**
**  @brief  Color an interference graph
**  @param  ig  The interference graph you want to color
*/

void _ljit_color_graph(ljit_interference_graph *ig);

#endif /* !COLOR_H */
