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

/**
**  @brief  Represent an ELF header
*/
typedef Elf32_Ehdr ljit_elf_header;

/**
**  @brief  Represent a program header
*/

typedef Elf32_Phdr ljit_program_header;

/**
**  @brief  Represent a section header
*/

typedef Elf32_Shdr ljit_section_header;

/**
**  @brief  List of ELF section
*/

typedef struct _ljit_elf_section_s
{
    /**
    **  @brief  The header of the section
    */
    ljit_section_header *header;

    /**
    **  @brief  The data that contains the section
    */
    void *data;

    /**
    **  @brief  The size of the data held by the section
    */
    unsigned int data_size;

    /**
    **  @brief  The next section
    */
    struct _ljit_elf_section_s *next;
} ljit_elf_section;

/**
**  @brief  The structure that represent the ELF itself
*/

typedef struct
{
    /**
    **  @brief  The header of the elf
    */
    ljit_elf_header *header;

    /** UPDATED SOON **/
    ljit_program_header **prog_header;

    /**
    **  @brief  The sections contained in the ELF
    */
    ljit_elf_section *section;

    /**
    **  @brief  The special section @a shstrtab
    */
    ljit_elf_section *shstrtab;

    unsigned int shstrtab_max_size;
} ljit_elf;

#endif /* !ELF_DEFS_H */
