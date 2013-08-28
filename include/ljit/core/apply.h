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
**  @file   apply.h
**  @brief  Call function from address without C prototype
**  @author Baptiste Covolato <b.covolato@gmail.com>
**  @date   24 August 2013
*/

#ifndef APPLY_H
# define APPLY_H

/**
**  @brief  Call a function compile by @a LiteJit
**  @param  fun     The function you want to call
**  @param  param   The parameters you want to pass to this function. Leave
**                  NULL if no parameter
**  @param  ret_val The place where the return value will be stored. Set NULL
**                  if you don't want the return value
*/

void ljit_call_function(ljit_function *fun, void **params, void *ret_val);

#endif /* !APPLY_H */
