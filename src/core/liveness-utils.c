#include "liveness-utils.h"

inline _ljit_liveness_info *_ljit_liveness_info_new(int elt)
{
    _ljit_liveness_info *li = NULL;

    if ((li = malloc(sizeof(_ljit_liveness_info))) == NULL)
        return NULL;

    li->elt = elt;

    return li;
}

void _ljit_liveness_info_free(_ljit_liveness_info *li)
{
    _ljit_liveness_info *tmp = NULL;

    while (li)
    {
        tmp = li;
        li = li->next;
        free(tmp);
    }
}

void _ljit_liveness_info_minus(_ljit_liveness_info *li,
                               _ljit_liveness_info *rem)
{
    _ljit_liveness_info *to_remove = rem;
    _ljit_liveness_info *tmp = NULL;

    /* Try to remove all element on the rem list */
    while (to_remove)
    {
        tmp = li;

        /* Run through all the list to check if the element is in the list */
        while (tmp)
        {
            /* If the element to destroy is the current element destroy it */
            if (tmp->elt == to_remove->elt)
            {
                /* Destroy the element */
                free(tmp);

                /* The element should be only once in the list */
                break;
            }

            tmp = tmp->next;
        }

        to_remove = to_remove->next;
    }
}
