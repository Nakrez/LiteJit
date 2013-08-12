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
**  @file   function.h
**  @brief  Interface for function creation
**  @author Baptiste Covolato <b.covolato@gmail.com>
*/

#ifndef FUNCTION_H
# define FUNCTION_H

# include <stdlib.h>

typedef struct ljit_function_s
{

} ljit_function;

/**
**  @brief  Create a new function definition
**  @return The new function created if everything went well, NULL otherwise
*/

ljit_function *ljit_new_function(void);

/**
**  @brief  Free the memory allocated for a function (The function won't be
**          accessible to be called or compiled or any other things)
**  @param  fun The Function you want to free
*/

void ljit_free_function(ljit_function *fun);

#endif /* !FUNCTION_H */
