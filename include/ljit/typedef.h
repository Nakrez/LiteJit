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
**  @file   typedef.h
**  @brief  All @a LiteJit type definition
**  @author Baptiste Covolato <b.covolato@gmail.com>
**  @date   15 August 2013
*/

#ifndef TYPEDEF_H
# define TYPEDEF_H

/**
** Keep all configuration informations
*/

typedef struct _ljit_instance_s ljit_instance;

/**
**  @brief  Signature of a function
*/

typedef struct _ljit_signature_s ljit_signature;

/**
**  @brief  The content of a @a LiteJit function. It contains all information
**          that allows you to create and use a function
*/

typedef struct _ljit_function_s ljit_function;

/**
**  @brief  The enumeration of all built in type in @a LiteJit
*/

typedef enum _ljit_types_e
{
    /**
    **  @brief  Label
    */
    LJIT_LABEL,

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
**  @brief  16-bit integer value
*/

typedef short ljit_short;

/**
**  @brief  16-bit unsigned integer value
*/

typedef unsigned short ljit_ushort;

/**
**  @brief  32-bit signed integer value
*/

typedef int ljit_int;

/**
**  @brief  32-bit unsigned integer value
*/

typedef unsigned int ljit_uint;

/**
**  @brief  64-bit integer value
*/

typedef long ljit_long;

/**
** @brief   64-bit unsigned integer value
*/

typedef unsigned long ljit_ulong;

/**
**  @brief  All bytecode instruction
*/

typedef enum _ljit_bytecode_type_e
{
    /** 0 Operand instructions **/

    /** 1 Operand instructions **/

    GET_PARAM,
    RETURN,
    LABEL,
    JUMP,

    /** 2 Operand instructions **/

    JUMP_IF,
    JUMP_IF_NOT,
    ADD,
    SUB,
    MUL,
    DIV
} ljit_bytecode_type;

/**
**  @brief  @a LiteJit bytecode instructions that does not need operand
*/

typedef struct _ljit_bytecode_s ljit_bytecode;

/**
**  @brief  Bytecode list container
*/

typedef struct _ljit_bytecode_list_s ljit_bytecode_list;

/**
**  @brief  Block type definition
*/

typedef struct _ljit_block_s ljit_block;

/**
**  @brief  The label type definition
*/

typedef struct _ljit_label_s ljit_label;

/**
**  @brief  The generated code structure
*/

typedef struct _ljit_codegen ljit_codegen;

#endif /* !TYPEDEF_H */
