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

/**
**  @brief  The enumeration of all built in type in @a LiteJit
*/
typedef enum ljit_types_e
{
    /**
    **  @brief  Void type with C meaning. Usable only as return type of a
    **          function.
    */
    LJIT_VOID,

    /**
    **  @brief  8-bit signed integer
    */
    LJIT_CHAR,

    /**
    **  @brief  8-bit unsigned integer
    */
    LJIT_UCHAR,

    /**
    **  @brief  16-bit signed integer
    */
    LJIT_SHORT,

    /**
    **  @brief  16-bit unsigned integer
    */
    LJIT_USHORT,

    /**
    **  @brief  32-bit signed integer
    */
    LJIT_INT,

    /**
    **  @brief  32-bit unsigned integer
    */
    LJIT_UINT,

    /**
    **  @brief  64-bit signed integer
    */
    LJIT_LONG,

    /**
    **  @brief  64-bit unsigned intger
    */
    LJIT_ULONG
} ljit_types;

/**
**  @brief  Base value of all @a LiteJit
*/

struct ljit_value_s
{
    /**
    **  @brief  The type of the value
    */
    ljit_types type;
};

/**
**  @brief  Pointer typedef to @a ljit_value_s
*/

typedef struct ljit_value_s * ljit_value;

/**
**  @brief  4 bit signed integer value
*/

struct ljit_int_s
{
    /**
    **  @brief  The type of the value
    */
    ljit_types type;

    /**
    **  @brief  The content of the signed integer value
    */
    int val;
};

/**
**  @brief  Pointer typedef to @a ljit_int_s
*/

typedef struct ljit_int_s * ljit_int;

/**
**  @brief  4 bit unsigned integer value
*/

struct ljit_uint_s
{
    /**
    **  @brief  The type of the value
    */
    ljit_types type;

    /**
    **  @brief  The content of the unsigned integer value
    */
    unsigned int val;
};

/**
**  @brief  Pointer typedef to @a ljit_uint_s
*/

typedef struct ljit_uint_s * ljit_uint;

#endif /* !TYPES_H */
