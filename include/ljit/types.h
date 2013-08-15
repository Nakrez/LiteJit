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

/**
**  @brief  The enumeration of all built in type in @a LiteJit
*/

typedef enum _ljit_types_e ljit_types;

/**
**  @brief  Pointer typedef to @a ljit_value_s
*/

typedef struct ljit_value_s * ljit_value;

/**
**  @brief  8-bit signed integer value
*/

typedef char ljit_char;

/**
**  @brief  8-bit unsigned integer value
*/

typedef unsigned char ljit_uchar;

/**
**  @brief  32-bit signed integer value
*/

typedef int ljit_int;

/**
**  @brief  32-bit unsigned integer value
*/

typedef unsigned int ljit_uint;

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

#endif /* !TYPES_H */
