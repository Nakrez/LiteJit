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
**  @file   x86-arch.h
**  @brief  All x86 architecture related functions
**  @author Baptiste Covolato <b.covolato@gmail.com>
**  @date   19 August 2013
*/

#ifndef X86_ARCH_H
# define X86_ARCH_H

# include "typedef.h"

# define LJIT_X86_USABLE_REGS 4

typedef enum
{
    X86_EAX = 0,
    X86_ECX = 1,
    X86_EDX = 2,
    X86_EBX = 3,
    X86_ESP = 4,
    X86_EBP = 5,
    X86_ESI = 6,
    X86_EDI = 7
} ljit_x86_register;

#define ljit_x86_push_reg(code, reg) \
    *(code++) = 0x50 + reg;

#define ljit_x86_pop_reg(code, reg) \
    *(code++) = 0x58 + reg;

#define ljit_x86_ret(code) \
    *(code++) = 0xC3;

#define ljit_x86_mov_reg_reg(code, dest, src) \
    *(code++) = 0x89; \
    *(code++) = (0x3 << 6) | (src << 3) | dest;
/**
**  @brief  Setup a @a ljit_instance with x86 properties
**  @param  instance    The instance you want to set as x86 instance
*/

void ljit_setup_platform(ljit_instance *instance);

/**
**  @brief  Compile @a LiteJit bytecode instruction to x86 instruction
**  @param  cg      The code generated informations
**  @param  instr   The instruction you want to compile
**
**  @return 0 if everything went well, -1 otherwise
*/

int ljit_compile_instr(ljit_codegen *cg, ljit_bytecode *instr);

/**
**  @brief  Generate the prologue for a x86 function
**
**  @param  cg      The code generated informations
*/

void ljit_gen_prolog(ljit_codegen *cg);

#endif /* !X86_ARCH_H */
