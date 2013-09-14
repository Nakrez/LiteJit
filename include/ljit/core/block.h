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
**  @file   block.h
**  @brief  Block management related functions
**  @author Baptiste Covolato <b.covolato@gmail.com>
**  @date   16 August 2013
*/

#ifndef BLOCK_H
# define BLOCK_H

# include "typedef.h"

/**
**  @brief  Create a new basic block if there is a possibility. If there is no
**          possibility to create a new basic block, @a lbl is added to the
**          label list that points on the current block
**  @param  fun     The function that hold the basic block
**  @param  lbl     The label that starts the new block
**
**  @return 1 if a new block was created, 0 if nothing happened, -1 if an
**          allocation error happened
*/

int _ljit_create_block_if_needed(ljit_function *fun, ljit_label *lbl);

/**
**  @brief  Create a new block
**  @param  fun The function the block is in
**  @param  l   The label associated with the new block
**
**  @return The new block created or NULL if an error occured
*/

ljit_block *ljit_new_block(ljit_function *fun, ljit_label *l);

/**
**  @brief  Delete a block
**  @param  block   The block you want to delete
*/

void ljit_free_block(ljit_block *block);

/**
**  @brief  Get a block that match a label
**  @param  fun The function where you want to find a block
**  @param  l   The label that starts the block you want to find
**
**  @return The block that starts with the label @a l, NULL if not found
*/

ljit_block *ljit_get_block_from_label(ljit_function *fun, ljit_label *l);

/**
**  @brief  Get a block that match a label number
**  @param  fun The function where you want to find a block
**  @param  n   The number of the label
**
**  @return The block that starts with the label number @a n, NULL if not found
*/

ljit_block *ljit_get_block_from_label_num(ljit_function *fun, unsigned int n);

#endif /* !BLOCK_H */
