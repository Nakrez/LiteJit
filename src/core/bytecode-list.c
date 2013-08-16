#include <ljit/bytecode-list.h>
#include "internal.h"

ljit_bytecode_list *ljit_new_bytecode_list(void)
{
    ljit_bytecode_list *list = NULL;

    if ((list = malloc(sizeof(ljit_bytecode_list))) == NULL)
        return NULL;

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

void ljit_free_bytecode_list(ljit_bytecode_list *list)
{
    struct _ljit_bytecode_list_element_s *l;
    struct _ljit_bytecode_list_element_s *tmp;

    if (!list)
        return;

    l = list->head;

    while (l)
    {
        tmp = l->next;

        _ljit_free_bytecode(l->instr);
        free(l);

        l = tmp;
    }

    free(list);
}

struct _ljit_bytecode_list_element_s *
ljit_bytecode_list_add(ljit_bytecode_list **list, ljit_bytecode *instr)
{
    ljit_bytecode_list *inner_list = *list;
    struct _ljit_bytecode_list_element_s *elem = NULL;

    if ((elem = malloc(sizeof(struct _ljit_bytecode_list_element_s))) == NULL)
        return NULL;

    elem->instr = instr;
    elem->next = NULL;

    /* If list is empty set this element as head and tail */
    if (!inner_list->size)
    {
        inner_list->head = elem;
        inner_list->tail = elem;
    }
    else /* Else add this element at the end of the list */
    {
        inner_list->tail->next = elem;
        inner_list->tail = elem;
    }

    /* Increment the size of the list */
    ++inner_list->size;

    return elem;
}
