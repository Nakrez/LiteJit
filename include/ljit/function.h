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
**  @date   12 August 2013
*/

#ifndef FUNCTION_H
# define FUNCTION_H

# include <stdlib.h>
# include <string.h>

# include "typedef.h"

/**
**  @brief  Create a new function definition
**  @return The new function created if everything went well, NULL otherwise
*/

ljit_function *ljit_new_function(ljit_instance *instance);

/**
**  @brief  Free the memory allocated for a function (The function won't be
**          accessible to be called or compiled or any other things)
**  @param  fun The Function you want to free
*/

void ljit_free_function(ljit_function *fun);

/**
**  @brief  Create the signature of a function
**  @param  fun             The function to which you want to add the signature
**  @param  ret_type        The return type of the function
**  @param  param_number    The number of parameter of the signature
**  @param  param_types     An array that represent the type of each parameter
**
**  @return 0 if everythin went well
**          -1 if they were a allocation problem
**          -2 if fun is NULL
*/

int ljit_new_signature(ljit_function *fun,
                       ljit_types ret_type,
                       int param_number,
                       ljit_types *param_types);


#endif /* !FUNCTION_H */
