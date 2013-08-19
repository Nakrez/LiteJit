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

# include <ljit/typedef.h>

struct _ljit_instance_s
{
    /**
    **  The configured target architecture
    */
    ljit_arch_type target_arch;

    /**
    **  The number of usable register available on the plateform
    */
    unsigned int usable_regs;
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
    **  @brief  Counter for deallocation
    */
    unsigned int count;

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
    **  @brief  The start block of the function
    */
    ljit_block *start_blk;

    /**
    **  @brief  The last block of the function
    */
    ljit_block *last_blk;

    /**
    **  @brief  The current block that is constructed
    */
    ljit_block *current_blk;

    /**
    **  @brief  Unique index for temporary value old by the function
    */
    unsigned short uniq_index;

    /**
    **  @brief  Unique index for label
    */
    unsigned short lbl_index;
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
**  @brief  Bytecode list element
*/

struct _ljit_bytecode_list_element_s
{
    /**
    **  @brief  The content of the element
    */
    ljit_bytecode *instr;

    /**
    **  @brief  The next element of the list
    */
    struct _ljit_bytecode_list_element_s *next;
};

struct _ljit_bytecode_list_s
{
    /**
    **  @brief  The head of the list
    */
    struct _ljit_bytecode_list_element_s *head;

    /**
    **  @brief  The tail of the list
    */
    struct _ljit_bytecode_list_element_s *tail;

    /**
    **  @brief  The size of the list
    */
    unsigned int size;
};

struct _ljit_block_s
{
    /**
    ** @brief   The label that target this block
    */
    ljit_label *label;

    /**
    **  @brief  The instruction list related to the block
    */
    ljit_bytecode_list *instrs;

    /**
    **  @brief  The previous block
    */
    struct _ljit_block_s *previous;

    /**
    **  @brief  The next block
    */
    struct _ljit_block_s *next;
};

struct _ljit_label_s
{
    /**
    **  @brief  The instruction where the label pointed
    */
    struct _ljit_bytecode_list_element_s *instr;

    /**
    **  @brief  The next label that belong to the same block
    */
    struct _ljit_label_s *next_lbl;

    /**
    **  @brief  The index of the label
    */
    unsigned int index;

    /**
    **  @brief  Reference counting for memory management
    */
    unsigned int count;
};

#endif /* !DEFS_H */
