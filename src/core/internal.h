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
**  @file   internal.h
**  @brief  Internal functions that should not be used externally
**  @author Baptiste Covolato <b.covolato@gmail.com>
**  @date   15 August 2013
*/

#ifndef INTERNAL_H
# define INTERNAL_H

# include <ljit/types.h>
# include <ljit/function.h>

/**
**  @brief  Create a new temporary value
**  @param  fun     The function that contains the temporary value
**  @param  type    The type of the new temporary value
*/

ljit_value _ljit_new_temporary(ljit_function *fun, ljit_types type);

#endif /* !INTERNAL_H */
