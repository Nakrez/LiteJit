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
**  @file   label.h
**  @brief  Label management related functions
**  @author Baptiste Covolato <b.covolato@gmail.com>
**  @date   16 August 2013
*/

#ifndef LABEL_H
# define LABEL_H

# include <ljit/core/typedef.h>

/**
**  @brief  Create a new label
**  @param  fun The function that hold the label
**
**  @return The new label created, or NULL if an error occured
*/

ljit_label *ljit_new_label(ljit_function *fun);

/**
**  @brief  Free a label
**  @param  lbl The label you want to free
*/

void ljit_free_label(ljit_label *lbl);

#endif /* !LABEL_H */
