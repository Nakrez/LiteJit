#include "liveness-utils.h"

inline _ljit_liveness_info *_ljit_liveness_info_new(unsigned short elt)
{
    _ljit_liveness_info *li = NULL;

    if ((li = malloc(sizeof(_ljit_liveness_info))) == NULL)
        return NULL;

    li->elt = elt;
    li->next = NULL;

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

_ljit_liveness_info *_ljit_liveness_info_minus(_ljit_liveness_info *li,
                                               _ljit_liveness_info *rem)
{
    _ljit_liveness_info *to_remove = rem;
    _ljit_liveness_info *tmp = NULL;
    _ljit_liveness_info *guard = NULL;

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
                if (tmp == li)
                    li = tmp->next;
                else
                    guard->next = tmp->next;

                /* Destroy the element */
                free(tmp);

                /* The element should be only once in the list */
                break;
            }

            guard = tmp;
            tmp = tmp->next;
        }

        to_remove = to_remove->next;
    }

    return li;
}

inline _ljit_liveness_info *_ljit_liveness_add_head(_ljit_liveness_info *list,
                                                    _ljit_liveness_info *elem)
{
    if (list)
        elem->next = list;

    return elem;
}

int _ljit_liveness_info_elt_exists(_ljit_liveness_info *li,
                                   unsigned short elt)
{
    while (li)
    {
        if (li->elt == elt)
            return 1;

        li = li->next;
    }

    return 0;
}

inline _ljit_liveness_info *_ljit_copy_list(_ljit_liveness_info *origin,
                                            _ljit_liveness_info *result,
                                            int force)
{
    _ljit_liveness_info *tmp = origin;
    _ljit_liveness_info *new_elem = NULL;
    int copy = result != NULL;

    if (force)
        copy = 1;

    while (tmp)
    {
        /*
        ** If the element already exists in the list don't copy it
        ** If the result list was NULL don't perform this check since we assume
        ** that elements are unique in the first place.
        */
        if (_ljit_liveness_info_elt_exists(result, tmp->elt))
        {
            tmp = tmp->next;
            continue;
        }

        if (!copy)
        {
            _ljit_liveness_info *l = tmp;
            tmp = tmp->next;
            result = _ljit_liveness_add_head(result, l);
            continue;
        }

        /* Duplicate element */
        if ((new_elem = _ljit_liveness_info_new(tmp->elt)) == NULL)
            goto error;

        /*
        ** The order don't really matter so we add the new element in head
        ** for better performances
        */
        result = _ljit_liveness_add_head(result, new_elem);

        tmp = tmp->next;
    }

    return result;

error:
    _ljit_liveness_info_free(result);
    return NULL;
}

_ljit_liveness_info *_ljit_liveness_info_merge(_ljit_liveness_info *li1,
                                               _ljit_liveness_info *li2)
{
    _ljit_liveness_info *ret = NULL;

    ret = _ljit_copy_list(li1, ret, LJIT_NO_FORCE_COPY);
    if (!ret)
        ret = _ljit_copy_list(li2, ret, LJIT_FORCE_COPY);
    else
        ret = _ljit_copy_list(li2, ret, LJIT_NO_FORCE_COPY);

    return ret;
}

void _ljit_liveness_info_dump(_ljit_liveness_info *li, char *sep)
{
    _ljit_liveness_info *tmp = li;

    while (tmp)
    {
        if (tmp != li)
            printf("%s", sep);

        printf("%u", tmp->elt);

        tmp = tmp->next;
    }
}

int _ljit_liveness_info_equals(_ljit_liveness_info *li1,
                               _ljit_liveness_info *li2)
{
    while (li1)
    {
        if (!_ljit_liveness_info_elt_exists(li2, li1->elt))
            return 0;

        li1 = li1->next;
    }

    return 1;
}
