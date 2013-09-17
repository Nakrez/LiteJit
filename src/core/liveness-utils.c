#include "liveness-utils.h"

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
