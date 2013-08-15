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
**  @file   defs.h
**  @brief  All @a LiteJit definition structures
**  @author Baptiste Covolato <b.covolato@gmail.com>
**  @date   15 August 2013
*/

#ifndef DEFS_H
# define DEFS_H

struct _ljit_instance_s
{
    /**
    **  The configured target architecture
    */
    ljit_arch_type target_arch;
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
    unsigned int is_cst : 1;

    /**
    **  @brief  Indicates if the value is a temporary value
    */
    unsigned int is_tmp : 1;

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

#endif /* !DEFS_H */
