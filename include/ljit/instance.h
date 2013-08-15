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
**  @file   instance.h
**  @brief  Instance is one of the main component of @a LiteJit. It keeps all
**          the configuration of the library
**  @author Baptiste Covolato <b.covolato@gmail.com>
**  @date   11 August 2013
*/

#ifndef INSTANCE_H
# define INSTANCE_H

# include <stdlib.h>

# include "arch.h"

/**
** Keep all configuration informations
*/

typedef struct _ljit_instance_s ljit_instance;

/**
**  @brief  Create a new instance.
**  @return The new instance allocated or NULL if something went wrong
*/

ljit_instance *ljit_new_instance(void);

/**
**  @brief  Destroy an instance and free all associated functions, ...
**  @param  instance    The instance you want to destroy
*/

void ljit_free_instance(ljit_instance *instance);

/**
**  @brief  Set the target architecture
**  @param  instance    The instance in which you want to set architecture
**  @param  arch        The target architecture
*/

void ljit_set_arch(ljit_instance *instance, ljit_arch_type arch);

#endif /* !INSTANCE_H */
