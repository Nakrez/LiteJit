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
**  @file   elf-write.h
**  @brief  Write the ELF into the disk
**  @author Baptiste Covolato <b.covolato@gmail.com>
**  @date   28 August 2013
*/

#ifndef ELF_WRITE_H
# define ELF_WRITE_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>

# include <ljit/elf/elf-defs.h>
# include <ljit/elf/elf-section.h>

/**
**  @brief  Write an ELF on the disk
**  @param  elf     The elf you want to write
**  @param  file    The file were you want to write the elf
**
**  @return 0 if everything went well, -1 if an error happened with the file.
*/

int ljit_write_elf(ljit_elf *elf, const char *file);

#endif /* !ELF_WRITE_H */
