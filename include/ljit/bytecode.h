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
**  @brief  All function declaration to use @a LiteJit bytecode
**  @author Baptiste Covolato <b.covolato@gmail.com>
**  @date   14 August 2013
*/

#ifndef BYTECODE_H
# define BYTECODE_H

# include <stdio.h>

# include "typedef.h"

/**
**  @brief  Return the @a pos parameter of the function
**  @param  fun The function where you want to get the @a pos parameter
**  @param  pos The position of the parameter
**
**  @return The parameter if everything went well.
**          NULL if the @a pos index does not match the definition of the
**          function or there is an allocation problem.
*/

ljit_value ljit_inst_get_param(ljit_function *fun, ljit_uchar pos);

/**
**  @brief  Return from a function
**  @param  fun The function that hold the return instruction
**  @param  val The value returned by the function. Put NULL if the function
**              does not return a value
**  @return 0 if everything went well. -1 if an allocation error occured or a
**          type error
*/

int ljit_inst_return(ljit_function *fun, ljit_value val);

/**
**  @brief  Create an unconditional jump to a label
**  @param  fun The function that holds the jump
**  @param  lbl The label where you want to jump
**
**  @return 0 if everything went well, -1 if an allocation error happened
*/

int ljit_inst_jump(ljit_function *fun, ljit_label *lbl);

/**
**  @brief  Return the result of addition of @a op1 and @a op2
**  @param  fun The function where you want to the @a add instruction
**  @param  op1 The first operand of the addition
**  @param  op2 The second operand of the addition
**
**  @return The temporary that holds the result of the addition
**          NULL if an allocation error occured
*/

ljit_value ljit_inst_add(ljit_function *fun, ljit_value op1, ljit_value op2);

/**
**  @brief  Return the result of subtraction of @a op1 and @a op2
**  @param  fun The function where you want to the @a sub instruction
**  @param  op1 The first operand of the subtraction
**  @param  op2 The second operand of the subtraction
**
**  @return The temporary that holds the result of the subtraction
**          NULL if an allocation error occured
*/

ljit_value ljit_inst_sub(ljit_function *fun, ljit_value op1, ljit_value op2);

/**
**  @brief  Return the result of multiplication of @a op1 and @a op2
**  @param  fun The function where you want to the @a mul instruction
**  @param  op1 The first operand of the multiplication
**  @param  op2 The second operand of the multiplication
**
**  @return The temporary that holds the result of the multiplication.
**          NULL if an allocation error occured
*/

ljit_value ljit_inst_mul(ljit_function *fun, ljit_value op1, ljit_value op2);

/**
**  @brief  Return the result of division of @a op1 and @a op2
**  @param  fun The function where you want to the @a div instruction
**  @param  op1 The first operand of the division
**  @param  op2 The second operand of the division
**
**  @return The temporary that holds the result of the division.
**          NULL if an allocation error occured
*/

ljit_value ljit_inst_div(ljit_function *fun, ljit_value op1, ljit_value op2);

/**
**  @brief  Dump bytecode into the file @a f
**  @param  f   The file where you want to dump the function @a fun
**  @param  fun The function you want to dump
*/

void ljit_bytecode_dumper(FILE *f, ljit_function *fun);

#endif /* !BYTECODE_H */
