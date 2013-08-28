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
**  @file   elf-defs.h
**  @brief  Type definition of all elf structure used by @a LiteJit
**  @author Baptiste Covolato <b.covolato@gmail.com>
**  @date   28 August 2013
*/

#ifndef ELF_DEFS_H
# define ELF_DEFS_H

# include <elf.h>

/* TODO : set elf structure according to the architecture compiled */

typedef Elf32_Ehdr ljit_elf_header;
typedef Elf32_Phdr ljit_program_header;
typedef Elf32_Shdr ljit_section_header;

typedef struct _ljit_elf_section_s
{
    ljit_section_header *header;

    void *data;

    unsigned int data_size;

    struct _ljit_elf_section_s *next;
} ljit_elf_section;

typedef struct
{
    ljit_elf_header *header;
    ljit_program_header **prog_header;
    ljit_elf_section *section;

    ljit_elf_section *shstrtab;
    unsigned int shstrtab_max_size;
} ljit_elf;

#endif /* !ELF_DEFS_H */
