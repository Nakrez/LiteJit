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

# include <ljit/ljit.h>

struct _ljit_instance_s
{
    /**
    **  The configured target architecture
    */
    ljit_arch_type target_arch;
};

enum _ljit_types_e
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
};

/**
**  @brief  Base value of all @a LiteJit
*/

struct ljit_value_s
{
    /**
    **  @brief  The type of the value
    */
    ljit_types type;

    /**
    **  @brief  Indicates if the value is a constant
    */
    unsigned char is_cst : 1;

    /**
    **  @brief  Indicates if the value is a temporary value
    */
    unsigned char is_tmp : 1;

    /**
    **  @brief  Unique identifier used to identified temporaries/registers
    */
    unsigned short index;

    /**
    **  @brief  The data holed by the value
    */
    void *data;
};

struct _ljit_signature_s
{
    /**
    **  @brief  The return type of the function
    */
    ljit_types ret_type;

    /**
    **  @brief  An array containing the type of each parameter
    */
    ljit_types *params_type;
};

struct _ljit_function_s
{
    /**
    **  @brief  The instance the function is using
    */
    ljit_instance *instance;

    /**
    **  @brief  The signature of the function
    */
    ljit_signature *signature;

    /**
    **  @brief  The bytecode representing the function
    */
    ljit_bytecode_list *bytecode;

    /**
    **  @brief  Unique index for temporary value old by the function
    */
    unsigned short uniq_index;

    /**
    **  @brief  The size of the temporary table
    */
    unsigned short tmp_table_size;

    /**
    **  @brief  The temporary table hold by the function
    */
    ljit_value *temporary_table;
};

enum _ljit_bytecode_type_e
{
    /** 0 Operand instructions **/

    /** 1 Operand instructions **/

    /** 2 Operand instructions **/

    /** Special instructions **/

    /**
    **  @brief  Get the xth parameter
    */
    GET_PARAM
};

struct _ljit_bytecode_s
{
    /**
    **  @brief  The type of the instruction
    */
    ljit_bytecode_type type;

    /**
    **  @brief  The first operand of the instruction
    */
    ljit_value op1;

    /**
    **  @brief  The second operand of the instruction
    */
    ljit_value op2;

    /**
    **  @brief  The value returned by this instruction
    */
    ljit_value  ret_val;
};

/**
**  @brief  Create a new temporary value
**  @param  fun     The function that contains the temporary value
**  @param  type    The type of the new temporary value
*/

ljit_value _ljit_new_temporary(ljit_function *fun, ljit_types type);

/**
**  @brief  Delete a bytecode instruction
**  @param  instr   The instruction to delete
*/
void _ljit_free_bytecode(ljit_bytecode *instr);

#endif /* !INTERNAL_H */
