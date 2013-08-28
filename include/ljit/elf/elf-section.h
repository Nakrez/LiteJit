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
**  @file   elf-section.h
**  @brief  Section management of ELF binary
**  @author Baptiste Covolato <b.covolato@gmail.com>
**  @date   28 August 2013
*/

#ifndef ELF_SECTION_H
# define ELF_SECTION_H

# include <ljit/elf.h>

# include <stdlib.h>

/**
**  @brief  Add a string into the section shstrtab
**  @param  elf The elf that contains the shstrtab where you want to add string
**  @param  str The string you want to add in the shstrtab section
**
**  @return 0 if everything went well, -1 if an allocation error occured
*/

int _ljit_shstrtab_add_string(ljit_elf *elf, const char *str);

/**
**  @brief  Add the shstrtab section on the ELF
**  @param  elf The ELF where you want to add the shstrtab section
*/

int _ljit_shstrtab_section(ljit_elf *elf);

/**
**  @brief  Create a new ELF section
**
**  @return The new section created, NULL otherwise
*/

ljit_elf_section *_ljit_new_elf_section(void);

/**
**  @brief  Free an ELF section
**  @param  section The section you want to free
*/

void _ljit_free_elf_section(ljit_elf_section *section);

/**
**  @brief  Add a section into the elf @a elf
**  @param  elf     The elf where you want to add the section
**  @param  name    The name of the section you want to add
*/

int ljit_elf_add_section(ljit_elf *elf, const char *name);

#endif /* !ELF_SECTION_H */
