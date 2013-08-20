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

# define LJIT_X86_USABLE_REGS 4

/**
**  @brief  Setup a @a ljit_instance with x86 properties
**  @param  instance    The instance you want to set as x86 instance
*/

void setup_x86_platform(ljit_instance *instance);

/**
**  @brief  Compile @a LiteJit bytecode to x86 native code
**  @param  fun The function you want to compile
**
**  @return 0 if everything went well, -1 otherwise
*/

int x86_compile_instr(ljit_function *fun);

#endif /* !X86_ARCH_H */
