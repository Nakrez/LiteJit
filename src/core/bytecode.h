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
**  @file   bytecode.h
**  @brief  Internal @a LiteJit bytecode
**  @author Baptiste Covolato <b.covolato@gmail.com>
**  @date   13 August 2013
*/

#ifndef BYTECODE_H
# define BYTECODE_H

# include "value.h"

/**
**  @brief  All bytecode instruction
*/

typedef enum ljit_bytecode_type_e
{
    /** 0 Operand instructions **/

    /** 1 Operand instructions **/

    /** 2 Operand instructions **/

    /** Special instructions **/

    /**
    **  @brief  Get the xth parameter
    */
    GET_PARAM,
} ljit_bytecode_type;

/**
**  @brief  @a LiteJit bytecode instructions that does not need operand
*/

typedef struct ljit_bytecode_s
{
    /**
    **  @brief  The type of the instruction
    */
    ljit_bytecode_type type;
} ljit_bytecode;

/**
**  @brief  @a LiteJit bytecode instructions that uses one operand
*/

typedef struct ljit_bytecode_one_s
{
    /**
    **  @brief  The type of the instruction
    */
    ljit_bytecode_type type;

    /**
    **  @brief  The first operand of the instruction
    */
    ljit_value *op1;
} ljit_bytecode_one;

/**
**  @brief  @a LiteJit bytecode instructions that uses two operands
*/

typedef struct ljit_bytecode_two_s
{
    /**
    **  @brief  The type of the instruction
    */
    ljit_bytecode_type type;

    /**
    **  @brief  The first operand of the instruction
    */
    ljit_value *op1;

    /**
    **  @brief  The second operand of the instruction
    */
    ljit_value *op2;
} ljit_bytecode_two;

#endif /* !BYTECODE_H */
