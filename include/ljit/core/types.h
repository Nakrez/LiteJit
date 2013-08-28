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
**  @file   types.h
**  @brief  Description of all types available in @a LiteJit
**  @author Baptiste Covolato <b.covolato@gmail.com>
**  @date   12 August 2013
*/

#ifndef TYPES_H
# define TYPES_H

# include <stdlib.h>

# include "typedef.h"

/**
**  @brief  Create a new @a LiteJit value of type @a type
**  @param  type    The type of the new value
**
**  @return The new value created or NULL if an allocation error happened
*/

ljit_value ljit_new_value(ljit_types type);

/**
**  @brief  Destroy a previous allocated value
**  @param  value   The value you want to free
*/

void ljit_free_value(ljit_value value);

/**
**  @brief  Create a new 8-bit unsigned integer constant
**  @param  value   The value of the new constant
**
**  @return The new constant or NULL if an allocation error happened
*/

ljit_value ljit_new_uchar_cst(ljit_uchar value);

/**
**  @brief  Get the size of a @a LiteJit type
**  param   type    The type you want to know the size
**
**  return  The size of the type @a type
*/

unsigned int ljit_type_get_size(ljit_types type);

#endif /* !TYPES_H */
