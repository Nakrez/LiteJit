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
**  @file   elf-debug.h
**  @brief  Debug functions for ELF
**  @author Baptiste Covolato <b.covolato@gmail.com>
**  @date   29 August 2013
*/

#ifndef ELF_DEBUG_H
# define ELF_DEBUG_H

# include <ljit/core/typedef.h>
# include <ljit/core/defs.h>
# include <ljit/elf.h>

/**
**  @brief  Create an ELF that contains the function @a fun
**  @param  fun     The function you want to add to the elf
**  @param  file    The name of the ELF you want to create
**
**  @return 0 if everything went well, -1 otherwise
*/

int ljit_elf_debug_function(ljit_function *fun, const char *file);

#endif /* !ELF_DEBUG_H */
