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

# include "function.h"
# include "bytecode-def.h"

/**
**  @brief  Return the @a pos parameter of the function
**  @param  fun The function where you want to get the @a pos parameter
**  @param  pos The position of the parameter
**
**  @return The parameter if everything went well
**          NULL if the @pos index does not match the definition of the
**          function
*/

ljit_value ljit_inst_get_param(ljit_function *fun, unsigned char pos);

#endif /* !BYTECODE_H */
