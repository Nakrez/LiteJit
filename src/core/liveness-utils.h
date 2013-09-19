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
**  @file   liveness-utils.h
**  @brief  Data structure management useful for liveness analysis
**  @author Baptiste Covolato <b.covolato@gmail.com>
**  @date   15 September 2013
*/

#ifndef LIVENESS_UTILS_H
# define LIVENESS_UTILS_H

# include <stdio.h>
# include <stdlib.h>

# define LJIT_FORCE_COPY 1
# define LJIT_NO_FORCE_COPY 0

typedef struct _ljit_liveness_info_s _ljit_liveness_info;

struct _ljit_liveness_info_s
{
    /*
    **  @brief  The information represent the number of a temporary
    */
    unsigned short elt;

    /*
    **  @brief  The next element in the list
    */
    _ljit_liveness_info *next;
};

/**
**  @brief  Create a new element of an liveness info list
**  @param  elt The element contained in the new liveness info element
**
**  @return The new element if everything went well, NULL otherwise
*/

_ljit_liveness_info *_ljit_liveness_info_new(unsigned short elt);

/**
**  @brief  Free a liveness information list
**  @param  li  The list you want to free
*/

void _ljit_liveness_info_free(_ljit_liveness_info *li);

/**
**  @brief  Represent the minus operation of two lists
**  @param  li  The list where you want to remove the elements
**  @param  rem The elements to remove
**
**  @return The new head of the list
*/

_ljit_liveness_info *_ljit_liveness_info_minus(_ljit_liveness_info *li,
                                               _ljit_liveness_info *rem);

/**
**  @brief  Add @a elem as the head element of list @a list
**  @param  list    The list where you want to add @a elem as the head of the
**                  list
**  @param  elem    The element you want to add as head of the list @a list
*/

_ljit_liveness_info *_ljit_liveness_add_head(_ljit_liveness_info *list,
                                             _ljit_liveness_info *elem);

/**
**  @brief  Test if an element is already in a liveness info list
**  @param  li  The list where you want to test if @a elt exists
**  @param  elt The element you want to check if it exists in @a li
**
**  @return 1 if the element is in the list, 0 otherwise
*/

int _ljit_liveness_info_elt_exists(_ljit_liveness_info *li,
                                   unsigned short elt);
/**
**  @brief  Copy the list @a origin at the beginning of @a result in reverse
**          order. This order does not mean anything in case of liveness
**          information. So this implementation is main to win some time.
**  @param  origin  The list you want to copy into @a result
**  @param  result  The list where you want to copy @a origin
**  @param  force   Force the list to be copied even if the result list is NULL
**
**  @return The new head of the list if everything went well, NULL otherwise
*/

_ljit_liveness_info *_ljit_copy_list(_ljit_liveness_info *origin,
                                     _ljit_liveness_info *result,
                                     int force);

/**
**  @brief  Merge two list and return the new one. If you want to merge a list
**          and don't want to duplicate @a li1 just use _ljit_copy_list()
**  @param  li1 The first list to merge
**  @param  li2 The second list to merge
**
**  @return The result of the merge of li1 and li2, NULL if something wrong
**          happened.
*/

_ljit_liveness_info *_ljit_liveness_info_merge(_ljit_liveness_info *li1,
                                               _ljit_liveness_info *li2);

/**
**  @brief  Dump a liveness info list on STDOUT
**  @param  li  The list you want to dump on STDOUT
**  @param  sep The string that separates elements on the dump
*/

void _ljit_liveness_info_dump(_ljit_liveness_info *li, char *sep);

/**
**  @brief  Test if two liveness info lists are equals
**  @param  li1 The first list to compare
**  @param  li2 The second list to compare
**
**  @return 1 if the lists are equals, 0 otherwise
*/

int _ljit_liveness_info_equals(_ljit_liveness_info *li1,
                               _ljit_liveness_info *li2);
#endif /* !LIVENESS_UTILS_H */
