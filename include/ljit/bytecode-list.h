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
**  @file   bytecode-list.h
**  @brief  List of @a LiteJit bytecode instructions
**  @author Baptiste Covolato <b.covolato@gmail.com>
**  @date   13 August 2013
*/

#ifndef BYTECODE_LIST_H
# define BYTECODE_LIST_H

# include <stdlib.h>

# include "typedef.h"

/**
**  @brief  Create a new bytecode list
**
**  @return The new list created if everything went well.
**          NULL if an error occured
*/

ljit_bytecode_list *ljit_new_bytecode_list(void);

/**
**  @brief  Destroy a bytecode list
**  param   list    The list you want to destroy
*/

void ljit_free_bytecode_list(ljit_bytecode_list *list);

/**
**  @brief  Add an instruction to a bytecode list. The element is added at the
**          end of the list.
**  @param  list    The list where you want to add the instruction @a instr
**  @param  instr   The instruction you want to add to the list @a list
**
**  @return The created element if everything went well.
**          NULL if an allocation error occured
*/

struct _ljit_bytecode_list_element_s *
ljit_bytecode_list_add(ljit_bytecode_list **list, ljit_bytecode *instr);

#endif /* !BYTECODE_LIST_H */
